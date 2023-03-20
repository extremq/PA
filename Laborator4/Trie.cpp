#include <iostream>
#include <string>

class Trie {
    struct Node {
        bool is_word = false;
        Node* links[26] = {nullptr};    
    };

    void recurse_insert(Node* node, std::string word, int index) {
        if (node->links[word[index] - 'a'] == nullptr) {
            node->links[word[index] - 'a'] = new Node;
        }

        if (index == word.length() - 1) {
            node->links[word[index] - 'a']->is_word = true;
        }
        else {
            recurse_insert(node->links[word[index] - 'a'], word, index + 1);
        }
    }

    public:
    Node* root = nullptr;

    void insert(std::string word) {
        recurse_insert(root, word, 0);
    }

    bool find(std::string word) {
        Node* iterator = root;
        for (int i = 0; i < word.length(); ++i) {
            if (iterator->links[word[i] - 'a'] == nullptr) {
                return false;
            }

            iterator = iterator->links[word[i] - 'a'];
        }

        return iterator->is_word;
    }

    Trie() {
        root = new Node;
    }
};

int main() {
    Trie trie;

    trie.insert("caine");
    trie.insert("cal");
    trie.insert("carte");
    trie.insert("copil");
    trie.insert("lopata");

    std::cout << trie.find("caine") << " " << trie.find("cain");
}
