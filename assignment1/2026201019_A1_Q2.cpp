#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Trie {
private:
    struct TrieNode {
        TrieNode* children[26];
        bool isEndOfWord;

        TrieNode() {
            isEndOfWord = false;

            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
        }
    };

    TrieNode* root;

    // Collects every word below the given node.
    void collectWords(
        TrieNode* node,
        string& currentWord,
        vector<string>& answers
    ) {
        if (node->isEndOfWord) {
            answers.push_back(currentWord);
        }

        // Visiting children from 'a' to 'z' gives lexicographical order.
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                currentWord.push_back(char('a' + i));

                collectWords(
                    node->children[i],
                    currentWord,
                    answers
                );

                currentWord.pop_back();
            }
        }
    }

    void findCorrections(
        TrieNode* node,
        char trieCharacter,
        const string& input,
        const vector<int>& previousRow,
        string& currentWord,
        vector<string>& answers
    ) {
        int inputLength = input.size();
        vector<int> currentRow(inputLength + 1);

        /*
         * currentRow[0] represents converting the current Trie prefix
         * into an empty input string.
         */
        currentRow[0] = previousRow[0] + 1;

        for (int column = 1; column <= inputLength; column++) {
            int insertionCost = currentRow[column - 1] + 1;
            int deletionCost = previousRow[column] + 1;

            int replacementCost = previousRow[column - 1];

            if (input[column - 1] != trieCharacter) {
                replacementCost++;
            }

            currentRow[column] = min({
                insertionCost,
                deletionCost,
                replacementCost
            });
        }

        currentWord.push_back(trieCharacter);

        /*
         * The last cell is the edit distance between the current
         * Trie word and the complete input string.
         */
        if (node->isEndOfWord && currentRow[inputLength] <= 3) {
            answers.push_back(currentWord);
        }

        /*
         * If the smallest value is greater than 3, extending this
         * Trie prefix cannot produce a valid answer.
         */
        int minimumValue = *min_element(
            currentRow.begin(),
            currentRow.end()
        );

        if (minimumValue <= 3) {
            for (int i = 0; i < 26; i++) {
                if (node->children[i] != nullptr) {
                    findCorrections(
                        node->children[i],
                        char('a' + i),
                        input,
                        currentRow,
                        currentWord,
                        answers
                    );
                }
            }
        }

        currentWord.pop_back();
    }

    void deleteTrie(TrieNode* node) {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < 26; i++) {
            deleteTrie(node->children[i]);
        }

        delete node;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        deleteTrie(root);
    }

    void insert(const string& word) {
        TrieNode* current = root;

        for (char character : word) {
            int index = character - 'a';

            if (current->children[index] == nullptr) {
                current->children[index] = new TrieNode();
            }

            current = current->children[index];
        }

        current->isEndOfWord = true;
    }

    bool spellCheck(const string& word) {
        TrieNode* current = root;

        for (char character : word) {
            int index = character - 'a';

            if (current->children[index] == nullptr) {
                return false;
            }

            current = current->children[index];
        }

        return current->isEndOfWord;
    }

    vector<string> autocomplete(const string& prefix) {
        TrieNode* current = root;
        vector<string> answers;

        for (char character : prefix) {
            int index = character - 'a';

            if (current->children[index] == nullptr) {
                return answers;
            }

            current = current->children[index];
        }

        string currentWord = prefix;
        collectWords(current, currentWord, answers);

        return answers;
    }

    vector<string> autocorrect(const string& input) {
        vector<string> answers;

        
        vector<int> initialRow(input.size() + 1);

        for (int i = 0; i <= static_cast<int>(input.size()); i++) {
            initialRow[i] = i;
        }

        string currentWord;

        for (int i = 0; i < 26; i++) {
            if (root->children[i] != nullptr) {
                findCorrections(
                    root->children[i],
                    char('a' + i),
                    input,
                    initialRow,
                    currentWord,
                    answers
                );
            }
        }

        return answers;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    Trie dictionary;

    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        dictionary.insert(word);
    }

    while (q--) {
        int operation;
        string input;

        cin >> operation >> input;

        if (operation == 1) {
            cout << dictionary.spellCheck(input) << '\n';
        }
        else if (operation == 2) {
            vector<string> answers = dictionary.autocomplete(input);

            cout << answers.size() << '\n';

            for (const string& word : answers) {
                cout << word << '\n';
            }
        }
        else if (operation == 3) {
            vector<string> answers = dictionary.autocorrect(input);

            cout << answers.size() << '\n';

            for (const string& word : answers) {
                cout << word << '\n';
            }
        }
    }

    return 0;
}