#include "huffmantree.h"

HuffmanTree::Node::Node(char _symbol, unsigned _freq, Node *_left, Node *_right) : symbol(_symbol), freq(_freq), left(_left), right(_right) { }

bool HuffmanTree::Compare::operator()(typename HuffmanTree::Node *n1, typename HuffmanTree::Node *n2){
    return n1->freq >= n2->freq;
}

void HuffmanTree::clearNode(typename HuffmanTree::Node *node){
    if(!node){
        return;
    }

    clearNode(node->left);
    clearNode(node->right);
    delete node;
}

void HuffmanTree::clearTree(){
    clearNode(root);
    root = nullptr;
}

typename HuffmanTree::Node* HuffmanTree::copyNode(Node *node){
    if(!node){
        return nullptr;
    }

    Node *result = new Node(node->symbol, node->freq, copyNode(node->left), copyNode(node->right));

    return result;
}

void HuffmanTree::copyTree(const HuffmanTree& other){
    root = copyNode(other.root);
}

HuffmanTree::HuffmanTree(const std::string &text) : root(nullptr) {
    buildHuffmanTree(text);
    encodingSymbols(root, "");
}

HuffmanTree::HuffmanTree(const std::string &text, size_t &index) : root(nullptr) {
    root = deserialize(text, index);
    encodingSymbols(root, "");
}

HuffmanTree::HuffmanTree(const HuffmanTree& other) : root(nullptr), codes(other.codes){
    copyTree(other);
}

HuffmanTree& HuffmanTree::operator= (const HuffmanTree& other) {
    if(this != &other){
        clearTree();
        copyTree(other);
        this->codes = other.codes;
    }
    return *this;
}

HuffmanTree::~HuffmanTree(){
    clearTree();
}

bool HuffmanTree::isLeaf(typename HuffmanTree::Node *node){
    return node->left == nullptr && node->right == nullptr;
}

std::string HuffmanTree::binToDec(const std::string &text){
    std::stringstream strToUnsigned(text);

    unsigned number = 0;
    strToUnsigned >> number;

    unsigned result = 0;
    unsigned base = 1;
    
    while(number){
        unsigned lastDigit = number % 10;
        number /= 10;
        result += lastDigit * base;
        base *= 2;
    }

    std::stringstream unsignedToStr;
    unsignedToStr << result;

    return unsignedToStr.str();
}

void HuffmanTree::buildHuffmanTree(const std::string &text){
    if(text.empty()){
        root = nullptr;
    }

    std::unordered_map<char, unsigned> symbolFrequency;
    for(char symbol : text){
        ++symbolFrequency[symbol];
    }

    std::priority_queue<Node*, std::vector<Node*>, Compare> tree;

    for(std::pair<char, unsigned> pair : symbolFrequency){
        tree.push(new Node(pair.first, pair.second, nullptr, nullptr));
    }

    Node *left = nullptr, *right = nullptr, *top = nullptr;

    while(tree.size() != 1){
        left = tree.top(); tree.pop();
        right = tree.top(); tree.pop();

        top = new Node('\n', left->freq + right->freq, left, right);
        tree.push(top);
    }

    root = tree.top();
}

void HuffmanTree::encodingSymbols(typename HuffmanTree::Node *_root, std::string result){
    if(!_root){
        return;
    }

    if(isLeaf(_root)){
        if(result.empty()){ // empty string => only 1 symbol in the tree (no branches)
            codes[_root->symbol] = '0'; // encoding it with '0' and keeping in mind that no branches exist, only the root node
        }else{
            codes[_root->symbol] = result;
        }
    }

    encodingSymbols(_root->left, result + '0');
    encodingSymbols(_root->right, result + '1');
}

std::string HuffmanTree::compress(const std::string &text){
    std::string result;
    
    for(char elem : text){
        result += codes[elem];
    }

    return result;
}

void HuffmanTree::decompressRec(typename HuffmanTree::Node * _root, std::string &result, const std::string &text, size_t &index){
    if(!_root){
        return;
    }

    if(isLeaf(_root)){
        result += _root->symbol;
        return;
    }

    ++index;

    if(text[index - 1] == '0'){
        decompressRec(_root->left, result, text, index);
    }else if(text[index - 1] == '1'){
        decompressRec(_root->right, result, text, index);
    }
}

std::string HuffmanTree::decompress(const std::string &compressedText){
    std::string result;

    if(isLeaf(root)){ // only 1 sumbol in the tree
        size_t count = root->freq;
        while(count > 0){ 
            result += root->symbol;
            --count;
        }
        return result;
    }

    size_t i = 0;
    while(i < compressedText.size()){
        decompressRec(root, result, compressedText, i); // starting from tree root
    }

    return result;
}

std::string HuffmanTree::debug(const std::string &compressedText){
    std::string result;

    int size = compressedText.size();
    size_t index = 0;

    while(size >= 8){
        result += binToDec(compressedText.substr(index, 8));
        result += " "; // for convenience
        index += 8;
        size -= 8;
    }

    if(size){ // there are 'size' number of bits left (between 1 and 7)
        result += binToDec(compressedText.substr(index)); // take all elements left
    }

    return result;
}

void HuffmanTree::degreeOfCompression(const std::string &text, const std::string &compressedText){
    double compressedTextSize = compressedText.size(); // bits
    double textSize = text.size() * 8; // from bytes to bits

    std::cout << "Degree of compression: " << (int)(compressedTextSize / textSize * 100 + 0.5) << "%" << std::endl;
}

void HuffmanTree::serializeHelper(typename HuffmanTree::Node *node, std::string &result){
    if(isLeaf(node)){
        result += '1';
        result += node->symbol;
    }else{
        result += '0';
        serializeHelper(node->left, result);
        serializeHelper(node->right, result);
    }
}

std::string HuffmanTree::serialize(){
    std::string result;
    serializeHelper(getRoot(), result);
    return result;
}

typename HuffmanTree::Node* HuffmanTree::deserialize(const std::string &result, size_t &i){
    if(result[i] == '1'){
        ++i;
        return new Node(result[i], 0, nullptr, nullptr);
    }else{
        ++i;
        Node *left = deserialize(result, i);
        ++i;
        Node *right = deserialize(result, i);
        return new Node('\n', 0, left, right);
    }
}