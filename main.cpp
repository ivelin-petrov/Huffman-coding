#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "huffmantree.h"
#include "regimes.h"

TEST_CASE("Correct construction of Huffman Tree")
{
    HuffmanTree tree("ABRACADABRA");

    CHECK(tree.getRoot()->symbol == '\n'); // empty node
    CHECK(tree.getRoot()->freq == 11);

    CHECK(tree.getRoot()->left->symbol == 'A');
    CHECK(tree.getRoot()->left->freq ==  5);
    CHECK(tree.getRoot()->left->left == nullptr);
    CHECK(tree.getRoot()->left->right == nullptr);

    CHECK(tree.getRoot()->right->symbol == '\n'); // empty node
    CHECK(tree.getRoot()->right->freq == 6);

    CHECK(tree.getRoot()->right->left->symbol == 'R');
    CHECK(tree.getRoot()->right->left->freq == 2);
    CHECK(tree.getRoot()->right->left->left == nullptr);
    CHECK(tree.getRoot()->right->left->right == nullptr);

    CHECK(tree.getRoot()->right->right->symbol == '\n'); // empty node
    CHECK(tree.getRoot()->right->right->freq == 4); 

    CHECK(tree.getRoot()->right->right->right->symbol == 'B');
    CHECK(tree.getRoot()->right->right->right->freq == 2);
    CHECK(tree.getRoot()->right->right->right->left == nullptr);
    CHECK(tree.getRoot()->right->right->right->right == nullptr);

    CHECK(tree.getRoot()->right->right->left->right->symbol == 'C');
    CHECK(tree.getRoot()->right->right->left->right->freq == 1);
    CHECK(tree.getRoot()->right->right->left->right->left == nullptr);
    CHECK(tree.getRoot()->right->right->left->right->right == nullptr);

    CHECK(tree.getRoot()->right->right->left->left->symbol == 'D');
    CHECK(tree.getRoot()->right->right->left->left->freq == 1);
    CHECK(tree.getRoot()->right->right->left->left->left == nullptr);
    CHECK(tree.getRoot()->right->right->left->left->right == nullptr);
}

TEST_CASE("Correct encoding of symbols")
{
    HuffmanTree tree("ABRACADABRA");

    CHECK(tree.getCodes()['A'] == "0");
    CHECK(tree.getCodes()['R'] == "10");
    CHECK(tree.getCodes()['B'] == "111");
    CHECK(tree.getCodes()['D'] == "1100");
    CHECK(tree.getCodes()['C'] == "1101");
}

TEST_CASE("Testing compressed/decompressed text correction")
{
    HuffmanTree tree("ABRACADABRA");
    std::string compressedText = tree.compress("ABRACADABRA"); // compressed text

    CHECK(compressedText == "01111001101011000111100");
    //          "0 111 10 0 1101 0 1100 0 111 10 0"
    //           A B   R  A C    A D    A B   R  A

    std::string decompressedText = tree.decompress(compressedText);

    CHECK(decompressedText == "ABRACADABRA");
                                                        // compressed text with numbers [0;255] 
    std::string debugText = tree.debug(compressedText); // (compressed data divided into blocks of 8 bits)

    CHECK(debugText == "121 172 60");
}

TEST_CASE("Correct serialization")
{
    std::string input, output;
    std::ifstream i("test.txt");

    std::getline(i, input);

    HuffmanTree tree1(input);

    output = tree1.compress(input);

    std::ofstream o("test.txt");
    std::string tmp = tree1.serialize();

    o << tmp << '\n';
    o << output;

    CHECK(tmp == "00001s1n1t1 00001i1h1l01o0001:1f01m1I001D1;1p000001v1d1u001-1j01k1y01r01.1w01e1a");
}

TEST_CASE("Correct deserialization")
{
    std::ifstream i("test.txt");
    std::string line1, line2;

    std::getline(i, line1);
    std::getline(i, line2);
    size_t index = 0;
    HuffmanTree tree2(line1, index);
    
    line1.clear();

    std::ofstream o("test.txt");
    
    line1 = tree2.decompress(line2);
    o << line1;

    CHECK(line1 == "Death is just another path - one that we all must take. I will not say: do not weep; for not all tears are an evil.");
}

int main()
{
    // g++ main.cpp huffmantree.cpp regimes.cpp -o main.exe

    // all printable symbols
    // !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~

    // some non-printable symbols
    // € ‰ œ ® © µ ¤ ¥ § ¼ ½ ¾ æ Ø • ™ ª¿ × ð¦ « ° … ‡† » ♔
    
    // testing with doctest
    doctest::Context().run();

    char regime;
    std::cout << "The program is waiting for commands." << std::endl;
    std::cout << "Enter 'c' to use the c[ompress] regime."<< std::endl; 
    std::cout << "Enter 'd' to user the d[ecompress] regime." << std::endl;
    std::cout << "Enter 'v' for v[isual] representation of the program's possibilities." << std::endl;
    std::cin >> regime;

    if(regime == 'c'){
        Regime::compressRegime();
    }else if(regime == 'd'){
        Regime::decompressRegime();
    }else if(regime == 'v'){
        Regime::visualRegime();
    }else{
        std::cout << "Unknown command entered. Exiting..." << std::endl;
    }

    return 0;
}
