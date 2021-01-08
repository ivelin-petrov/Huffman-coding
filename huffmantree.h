#ifndef _HUFFMANTREE_H_
#define _HUFFMANTREE_H_

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <sstream>

class HuffmanTree{
  private:
    struct Node{
        unsigned freq;
        char symbol;
        Node *left, *right;

        Node(char _symbol, unsigned _freq, Node *_left, Node *_right);
    };

    // sorting the tree by comparing the frequencies of the characters
    // can be used as a parameter to construct hashset or hashtree
    struct Compare{
        bool operator()(Node *n1, Node *n2);
    };

    Node *root;
    std::unordered_map<char, std::string> codes;

    bool isLeaf(Node *node);
    void buildHuffmanTree(const std::string &text);
    void encodingSymbols(Node *_root, std::string result);
    void decompressRec(Node *_root, std::string &result, const std::string &text, size_t &index);
    std::string binToDec(const std::string &text);

    void serializeHelper(Node *node, std::string &result);
    Node* deserialize(const std::string &result, size_t &index);

    void clearNode(Node *node);
    void clearTree();
    Node* copyNode(Node *node);
    void copyTree(const HuffmanTree& other);
    
  public:
    HuffmanTree(const std::string &text);
    HuffmanTree(const std::string &text, size_t &index);
    HuffmanTree(const HuffmanTree& other);
    HuffmanTree& operator= (const HuffmanTree& other);
    ~HuffmanTree();

    Node* getRoot() { return root; }
    std::unordered_map<char, std::string>& getCodes() { return codes; }

    std::string compress(const std::string &text);
    std::string decompress(const std::string &compressedText);
    // compressed text with numbers [0;255] (compressed data divided into blocks of 8 bits)
    std::string debug(const std::string &compressedText);
    void degreeOfCompression(const std::string &text, const std::string &compressedText);

    std::string serialize();
};

#endif // _HUFFMANTREE_H_