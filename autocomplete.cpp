// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <string>
// using namespace std;

// // Maximum number of children (a-z)
// const int ALPHABET_SIZE = 26;

// // Simple Trie Node
// struct TrieNode
// {
//     TrieNode *children[ALPHABET_SIZE] = {nullptr};
//     bool isEnd = false;
// };

// TrieNode *root = new TrieNode();

// // Insert a word into the trie
// void insert(string word)
// {
//     TrieNode *node = root;
//     for (char c : word)
//     {
//         c = tolower(c);
//         int index = c - 'a';
//         if (index < 0 || index >= 26)
//             continue; 
//         if (!node->children[index])
//             node->children[index] = new TrieNode();
//         node = node->children[index];
//     }
//     node->isEnd = true;
// }

// // Collect up to 5 words with a given prefix
// void collect(TrieNode *node, string prefix, vector<string> &results)
// {
//     if (!node || results.size() >= 5)
//         return;
//     if (node->isEnd)
//         results.push_back(prefix);
//     for (int i = 0; i < ALPHABET_SIZE; ++i)
//     {
//         if (node->children[i])
//         {
//             collect(node->children[i], prefix + char('a' + i), results);
//         }
//     }
// }

// // Get autocomplete suggestions
// vector<string> getSuggestions(string prefix)
// {
//     TrieNode *node = root;
//     for (char c : prefix)
//     {
//         c = tolower(c);
//         int index = c - 'a';
//         if (index < 0 || index >= 26 || !node->children[index])
//             return {};
//         node = node->children[index];
//     }
//     vector<string> results;
//     collect(node, prefix, results);
//     return results;
// }

// // Load words from a file
// void loadWords(string filename)
// {
//     ifstream file(filename);
//     string word;
//     while (getline(file, word))
//     {
//         if (!word.empty())
//             insert(word);
//     }
//     file.close();
// }

// int main(int argc, char *argv[])
// {
//     loadWords("words.txt");

//     if (argc != 2)
//     {
//         cout << "Usage: " << argv[0] << " <query>" << endl;
//         return 1;
//     }

//     string query = argv[1];
//     vector<string> suggestions = getSuggestions(query);

//     for (string word : suggestions)
//         cout << word << endl;

//     return 0;
// }











#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// -------------------- BST Node --------------------
struct BSTNode {
    string word;
    BSTNode *left;
    BSTNode *right;
    BSTNode(string w) : word(w), left(nullptr), right(nullptr) {}
};

BSTNode *root = nullptr;

// -------------------- Insert into BST --------------------
BSTNode* insert(BSTNode* node, string word) {
    if (!node)
        return new BSTNode(word);

    if (word < node->word)
        node->left = insert(node->left, word);
    else if (word > node->word)
        node->right = insert(node->right, word);
    // ignore duplicate
    return node;
}


// -------------------- Search words by prefix --------------------
void collectByPrefix(BSTNode* node, const string& prefix, vector<string>& results) {
    if (!node || results.size() >= 5)
        return;

    // Check if node's word starts with prefix
    if (node->word.rfind(prefix, 0) == 0)  // rfind(prefix, 0) == 0 → starts with prefix
        results.push_back(node->word);

    // BST traversal: check both subtrees
    if (prefix < node->word)
        collectByPrefix(node->left, prefix, results);
    if (prefix > node->word || node->word.rfind(prefix, 0) == 0)
        collectByPrefix(node->right, prefix, results);
}


// -------------------- Load words from file --------------------
void loadWords(const string& filename) {
    ifstream file(filename);
    string word;
    while (getline(file, word)) {
        if (!word.empty()) {
            for (char &c : word) c = tolower(c); // make lowercase
            root = insert(root, word);
        }
    }
    file.close();
}


// -------------------- Get suggestions --------------------
vector<string> getSuggestions(const string& prefix) {
    vector<string> results;
    collectByPrefix(root, prefix, results);
    return results;
}

// -------------------- Main --------------------
int main(int argc, char* argv[]) {
    loadWords("shuffled_words.txt");

    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <query>" << endl;
        return 1;
    }

    string query = argv[1];
    for (char &c : query) c = tolower(c);

    vector<string> suggestions = getSuggestions(query);

    if (suggestions.empty())
        cout << "No suggestions found." << endl;
    else
        for (const string& word : suggestions)
            cout << word << endl;

    return 0;
}
