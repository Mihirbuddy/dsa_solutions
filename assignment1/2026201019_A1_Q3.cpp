#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Query {
    int type;
    long long left;
    long long right;
    long long height;
};

class SegmentTree {
private:
    struct Node {
        long long minimum;
        long long secondMinimum;
        int minimumCount;

        Node() {
            minimum = 0;
            secondMinimum = LLONG_MAX;
            minimumCount = 0;
        }
    };

    int size;
    vector<Node> tree;

    void mergeNode(int index) {
        Node& current = tree[index];
        Node& leftChild = tree[2 * index];
        Node& rightChild = tree[2 * index + 1];

        current.minimum = min(
            leftChild.minimum,
            rightChild.minimum
        );

        current.minimumCount = 0;
        current.secondMinimum = LLONG_MAX;

        if (leftChild.minimum == current.minimum) {
            current.minimumCount += leftChild.minimumCount;
            current.secondMinimum = min(
                current.secondMinimum,
                leftChild.secondMinimum
            );
        }
        else {
            current.secondMinimum = min(
                current.secondMinimum,
                leftChild.minimum
            );
        }

        if (rightChild.minimum == current.minimum) {
            current.minimumCount += rightChild.minimumCount;
            current.secondMinimum = min(
                current.secondMinimum,
                rightChild.secondMinimum
            );
        }
        else {
            current.secondMinimum = min(
                current.secondMinimum,
                rightChild.minimum
            );
        }
    }

    void applyMaximum(int index, long long value) {
        if (value > tree[index].minimum) {
            tree[index].minimum = value;
        }
    }

    void pushDown(int index) {
        long long parentMinimum = tree[index].minimum;

        if (tree[2 * index].minimum < parentMinimum) {
            applyMaximum(2 * index, parentMinimum);
        }

        if (tree[2 * index + 1].minimum < parentMinimum) {
            applyMaximum(2 * index + 1, parentMinimum);
        }
    }

    void build(int index, int left, int right) {
        tree[index].minimum = 0;
        tree[index].secondMinimum = LLONG_MAX;
        tree[index].minimumCount = right - left + 1;

        if (left == right) {
            return;
        }

        int middle = left + (right - left) / 2;

        build(2 * index, left, middle);
        build(2 * index + 1, middle + 1, right);

        mergeNode(index);
    }

    void rangeMaximum(
        int index,
        int segmentLeft,
        int segmentRight,
        int queryLeft,
        int queryRight,
        long long value
    ) {
        if (segmentRight < queryLeft ||
            queryRight < segmentLeft ||
            value <= tree[index].minimum) {
            return;
        }

        /*
         * Only the elements having the minimum value need to
         * be changed. Segment Tree Beats allows us to update
         * the entire node without descending further.
         */
        if (queryLeft <= segmentLeft &&
            segmentRight <= queryRight &&
            value < tree[index].secondMinimum) {
            applyMaximum(index, value);
            return;
        }

        pushDown(index);

        int middle = segmentLeft +
                     (segmentRight - segmentLeft) / 2;

        rangeMaximum(
            2 * index,
            segmentLeft,
            middle,
            queryLeft,
            queryRight,
            value
        );

        rangeMaximum(
            2 * index + 1,
            middle + 1,
            segmentRight,
            queryLeft,
            queryRight,
            value
        );

        mergeNode(index);
    }

    void collectHeights(
        int index,
        int left,
        int right,
        vector<long long>& heights
    ) {
        if (left == right) {
            heights[left] = tree[index].minimum;
            return;
        }

        pushDown(index);

        int middle = left + (right - left) / 2;

        collectHeights(
            2 * index,
            left,
            middle,
            heights
        );

        collectHeights(
            2 * index + 1,
            middle + 1,
            right,
            heights
        );
    }

public:
    SegmentTree(int numberOfIntervals) {
        size = numberOfIntervals;

        if (size > 0) {
            tree.resize(4 * size);
            build(1, 0, size - 1);
        }
    }

    void update(int left, int right, long long height) {
        if (size == 0 || left > right) {
            return;
        }

        rangeMaximum(
            1,
            0,
            size - 1,
            left,
            right,
            height
        );
    }

    vector<long long> getHeights() {
        vector<long long> heights(size);

        if (size > 0) {
            collectHeights(1, 0, size - 1, heights);
        }

        return heights;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    vector<Query> queries;
    vector<long long> coordinates;

    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;

        if (type == 0) {
            long long left, right, height;
            cin >> left >> right >> height;

            queries.push_back({
                type,
                left,
                right,
                height
            });

            coordinates.push_back(left);
            coordinates.push_back(right);
        }
        else {
            queries.push_back({
                type,
                0,
                0,
                0
            });
        }
    }

    // Coordinate compression
    sort(coordinates.begin(), coordinates.end());

    coordinates.erase(
        unique(coordinates.begin(), coordinates.end()),
        coordinates.end()
    );

    /*
     * If there are m coordinates, there are m - 1 intervals:
     *
     * [coordinates[0], coordinates[1])
     * [coordinates[1], coordinates[2])
     * ...
     */
    int numberOfIntervals =
        max(0, static_cast<int>(coordinates.size()) - 1);

    SegmentTree segmentTree(numberOfIntervals);

    for (const Query& query : queries) {
        if (query.type == 0) {
            int leftIndex = lower_bound(
                coordinates.begin(),
                coordinates.end(),
                query.left
            ) - coordinates.begin();

            int rightIndex = lower_bound(
                coordinates.begin(),
                coordinates.end(),
                query.right
            ) - coordinates.begin();

            /*
             * Banner [left, right) covers compressed intervals
             * leftIndex through rightIndex - 1.
             */
            segmentTree.update(
                leftIndex,
                rightIndex - 1,
                query.height
            );
        }
        else {
            vector<long long> heights =
                segmentTree.getHeights();

            if (heights.empty()) {
                continue;
            }

            long long previousHeight = 0;

            for (int i = 0; i < numberOfIntervals; i++) {
                if (heights[i] != previousHeight) {
                    cout << coordinates[i] << ' '
                         << heights[i] << '\n';

                    previousHeight = heights[i];
                }
            }

            // At the final coordinate, the skyline returns to zero.
            if (previousHeight != 0) {
                cout << coordinates.back() << " 0\n";
            }
        }
    }

    return 0;
}