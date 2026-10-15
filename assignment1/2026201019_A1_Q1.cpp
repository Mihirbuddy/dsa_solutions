#include <opencv2/opencv.hpp>
#include <cstdio>
#include <climits>
#include <ctime>

const int CHANNELS = 3;
const int ENERGY_BAND = 2;

int smaller(int a, int b)
{
  return (a < b) ? a : b;
}

int larger(int a, int b)
{
  return (a > b) ? a : b;
}

int pixelStart(int row, int column, int width)
{
  return (row * width + column) * CHANNELS;
}

int matrixIndex(int row, int column, int width)
{
  return row * width + column;
}

int calculatePixelEnergy(
    const unsigned char *image,
    int row,
    int column,
    int height,
    int width)
{
  int leftColumn = (column > 0) ? column - 1 : column;
  int rightColumn = (column + 1 < width) ? column + 1 : column;
  int upperRow = (row > 0) ? row - 1 : row;
  int lowerRow = (row + 1 < height) ? row + 1 : row;

  int leftIndex = pixelStart(row, leftColumn, width);
  int rightIndex = pixelStart(row, rightColumn, width);
  int upperIndex = pixelStart(upperRow, column, width);
  int lowerIndex = pixelStart(lowerRow, column, width);

  int energy = 0;

  for (int channel = 0; channel < CHANNELS; channel++)
  {
    int horizontalDifference =
        static_cast<int>(image[rightIndex + channel]) -
        static_cast<int>(image[leftIndex + channel]);

    int verticalDifference =
        static_cast<int>(image[lowerIndex + channel]) -
        static_cast<int>(image[upperIndex + channel]);

    energy += horizontalDifference * horizontalDifference;
    energy += verticalDifference * verticalDifference;
  }

  return energy;
}

void calculateCompleteEnergy(
    const unsigned char *image,
    int *energy,
    int height,
    int width)
{
  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {
      energy[matrixIndex(row, column, width)] =
          calculatePixelEnergy(image, row, column, height, width);
    }
  }
}

void findVerticalSeam(
    const int *energy,
    int height,
    int width,
    long long *previousCost,
    long long *currentCost,
    signed char *parent,
    int *seam)
{
  for (int column = 0; column < width; column++)
  {
    previousCost[column] = energy[column];
  }

  for (int row = 1; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {
      long long bestCost = previousCost[column];
      signed char bestDirection = 0;

      if (column > 0 && previousCost[column - 1] < bestCost)
      {
        bestCost = previousCost[column - 1];
        bestDirection = -1;
      }

      if (column + 1 < width &&
          previousCost[column + 1] < bestCost)
      {
        bestCost = previousCost[column + 1];
        bestDirection = 1;
      }

      currentCost[column] =
          bestCost + energy[matrixIndex(row, column, width)];

      parent[matrixIndex(row, column, width)] = bestDirection;
    }

    long long *temporary = previousCost;
    previousCost = currentCost;
    currentCost = temporary;
  }

  int minimumColumn = 0;

  for (int column = 1; column < width; column++)
  {
    if (previousCost[column] < previousCost[minimumColumn])
    {
      minimumColumn = column;
    }
  }

  seam[height - 1] = minimumColumn;

  for (int row = height - 1; row > 0; row--)
  {
    minimumColumn +=
        parent[matrixIndex(row, minimumColumn, width)];
    seam[row - 1] = minimumColumn;
  }
}

void findHorizontalSeam(
    const int *energy,
    int height,
    int width,
    long long *previousCost,
    long long *currentCost,
    signed char *parent,
    int *seam)
{
  for (int row = 0; row < height; row++)
  {
    previousCost[row] = energy[matrixIndex(row, 0, width)];
  }

  for (int column = 1; column < width; column++)
  {
    for (int row = 0; row < height; row++)
    {
      long long bestCost = previousCost[row];
      signed char bestDirection = 0;

      if (row > 0 && previousCost[row - 1] < bestCost)
      {
        bestCost = previousCost[row - 1];
        bestDirection = -1;
      }

      if (row + 1 < height && previousCost[row + 1] < bestCost)
      {
        bestCost = previousCost[row + 1];
        bestDirection = 1;
      }

      currentCost[row] =
          bestCost + energy[matrixIndex(row, column, width)];

      parent[matrixIndex(row, column, width)] = bestDirection;
    }

    long long *temporary = previousCost;
    previousCost = currentCost;
    currentCost = temporary;
  }

  int minimumRow = 0;

  for (int row = 1; row < height; row++)
  {
    if (previousCost[row] < previousCost[minimumRow])
    {
      minimumRow = row;
    }
  }

  seam[width - 1] = minimumRow;

  for (int column = width - 1; column > 0; column--)
  {
    minimumRow += parent[matrixIndex(minimumRow, column, width)];
    seam[column - 1] = minimumRow;
  }
}

void removeVerticalSeamInPlace(
    unsigned char *image,
    int *energy,
    int height,
    int oldWidth,
    const int *seam)
{
  int writePixel = 0;

  for (int row = 0; row < height; row++)
  {
    for (int oldColumn = 0; oldColumn < oldWidth; oldColumn++)
    {
      if (oldColumn == seam[row])
      {
        continue;
      }

      int readPixel = matrixIndex(row, oldColumn, oldWidth);
      int readIndex = readPixel * CHANNELS;
      int writeIndex = writePixel * CHANNELS;

      for (int channel = 0; channel < CHANNELS; channel++)
      {
        image[writeIndex + channel] = image[readIndex + channel];
      }

      energy[writePixel] = energy[readPixel];
      writePixel++;
    }
  }
}

void removeHorizontalSeamInPlace(
    unsigned char *image,
    int *energy,
    int oldHeight,
    int width,
    const int *seam)
{
  for (int oldRow = 0; oldRow < oldHeight; oldRow++)
  {
    for (int column = 0; column < width; column++)
    {
      if (oldRow == seam[column])
      {
        continue;
      }

      int newRow =
          (oldRow < seam[column]) ? oldRow : oldRow - 1;

      int readPixel = matrixIndex(oldRow, column, width);
      int writePixel = matrixIndex(newRow, column, width);
      int readIndex = readPixel * CHANNELS;
      int writeIndex = writePixel * CHANNELS;

      for (int channel = 0; channel < CHANNELS; channel++)
      {
        image[writeIndex + channel] = image[readIndex + channel];
      }

      energy[writePixel] = energy[readPixel];
    }
  }
}

void updateEnergyAfterVerticalRemoval(
    const unsigned char *image,
    int *energy,
    int height,
    int newWidth,
    const int *seam)
{
  for (int row = 0; row < height; row++)
  {
    int joinColumn = seam[row];

    if (joinColumn >= newWidth)
    {
      joinColumn = newWidth - 1;
    }

    int startColumn = larger(0, joinColumn - ENERGY_BAND);
    int endColumn = smaller(newWidth - 1, joinColumn + ENERGY_BAND);

    for (int column = startColumn;
         column <= endColumn;
         column++)
    {
      energy[matrixIndex(row, column, newWidth)] =
          calculatePixelEnergy(
              image, row, column, height, newWidth);
    }
  }
}

void updateEnergyAfterHorizontalRemoval(
    const unsigned char *image,
    int *energy,
    int newHeight,
    int width,
    const int *seam)
{
  for (int column = 0; column < width; column++)
  {
    int joinRow = seam[column];

    if (joinRow >= newHeight)
    {
      joinRow = newHeight - 1;
    }

    int startRow = larger(0, joinRow - ENERGY_BAND);
    int endRow = smaller(newHeight - 1, joinRow + ENERGY_BAND);

    for (int row = startRow; row <= endRow; row++)
    {
      energy[matrixIndex(row, column, width)] =
          calculatePixelEnergy(
              image, row, column, newHeight, width);
    }
  }
}

void copyFromOpenCV(
    const cv::Mat &source,
    unsigned char *image)
{
  int height = source.rows;
  int width = source.cols;

  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {
      cv::Vec3b pixel = source.at<cv::Vec3b>(row, column);
      int index = pixelStart(row, column, width);

      // OpenCV stores a color image in BGR order.
      image[index] = pixel[0];
      image[index + 1] = pixel[1];
      image[index + 2] = pixel[2];
    }
  }
}

void copyToOpenCV(
    const unsigned char *image,
    cv::Mat &destination,
    int height,
    int width)
{
  for (int row = 0; row < height; row++)
  {
    for (int column = 0; column < width; column++)
    {
      int index = pixelStart(row, column, width);
      cv::Vec3b &pixel = destination.at<cv::Vec3b>(row, column);

      pixel[0] = image[index];
      pixel[1] = image[index + 1];
      pixel[2] = image[index + 2];
    }
  }
}

int main()
{
  char inputPath[1024];
  char outputPath[1024];
  int targetHeight;
  int targetWidth;

  std::printf("Enter input image path: ");
  if (std::scanf("%1023s", inputPath) != 1)
  {
    std::printf("Error: invalid input path.\n");
    return 1;
  }

  cv::Mat input = cv::imread(inputPath, cv::IMREAD_COLOR);

  if (input.empty())
  {
    std::printf("Error: could not load the input image.\n");
    return 1;
  }

  int originalHeight = input.rows;
  int originalWidth = input.cols;

  std::printf("Original dimensions: %d x %d\n",
              originalHeight, originalWidth);

  std::printf("Enter target height: ");
  if (std::scanf("%d", &targetHeight) != 1)
  {
    std::printf("Error: invalid target height.\n");
    return 1;
  }

  std::printf("Enter target width: ");
  if (std::scanf("%d", &targetWidth) != 1)
  {
    std::printf("Error: invalid target width.\n");
    return 1;
  }

  if (targetHeight < 1 || targetHeight > originalHeight ||
      targetWidth < 1 || targetWidth > originalWidth)
  {
    std::printf(
        "Error: target dimensions must be positive and cannot "
        "exceed the original dimensions.\n");
    return 1;
  }

  std::printf("Enter output image path: ");
  if (std::scanf("%1023s", outputPath) != 1)
  {
    std::printf("Error: invalid output path.\n");
    return 1;
  }

  long long maximumPixels =
      static_cast<long long>(originalHeight) * originalWidth;

  unsigned char *image =
      new unsigned char[maximumPixels * CHANNELS];
  int *energy = new int[maximumPixels];
  signed char *parent = new signed char[maximumPixels];

  int maximumDimension = larger(originalHeight, originalWidth);
  long long *previousCost = new long long[maximumDimension];
  long long *currentCost = new long long[maximumDimension];
  int *seam = new int[maximumDimension];

  copyFromOpenCV(input, image);

  int currentHeight = originalHeight;
  int currentWidth = originalWidth;

  calculateCompleteEnergy(
      image, energy, currentHeight, currentWidth);

  std::clock_t startTime = std::clock();

  while (currentWidth > targetWidth)
  {
    findVerticalSeam(
        energy,
        currentHeight,
        currentWidth,
        previousCost,
        currentCost,
        parent,
        seam);

    int oldWidth = currentWidth;

    removeVerticalSeamInPlace(
        image, energy, currentHeight, oldWidth, seam);

    currentWidth = oldWidth - 1;

    updateEnergyAfterVerticalRemoval(
        image, energy, currentHeight, currentWidth, seam);
  }

  while (currentHeight > targetHeight)
  {
    findHorizontalSeam(
        energy,
        currentHeight,
        currentWidth,
        previousCost,
        currentCost,
        parent,
        seam);

    int oldHeight = currentHeight;

    removeHorizontalSeamInPlace(
        image, energy, oldHeight, currentWidth, seam);

    currentHeight = oldHeight - 1;

    updateEnergyAfterHorizontalRemoval(
        image, energy, currentHeight, currentWidth, seam);
  }

  double elapsedSeconds =
      static_cast<double>(std::clock() - startTime) / CLOCKS_PER_SEC;

  cv::Mat output(currentHeight, currentWidth, CV_8UC3);
  copyToOpenCV(image, output, currentHeight, currentWidth);

  bool saved = cv::imwrite(outputPath, output);

  delete[] seam;
  delete[] currentCost;
  delete[] previousCost;
  delete[] parent;
  delete[] energy;
  delete[] image;

  if (!saved)
  {
    std::printf("Error: could not save the output image.\n");
    return 1;
  }

  std::printf("Resized image saved successfully.\n");
  std::printf("Final dimensions: %d x %d\n",
              currentHeight, currentWidth);
  std::printf("Seam-carving CPU time: %.3f seconds\n",
              elapsedSeconds);

  return 0;
}
