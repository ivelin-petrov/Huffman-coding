#include "regimes.h"

void Regime::compressRegime(){
    std::cout << "Enter the name of input file." << std::endl;
    std::string input, output;
    std::cin.ignore();

    std::getline(std::cin, input);
    std::ifstream i(input);
    input.clear();

    while(i){
        std::string tmp;
        std::getline(i, tmp);

        input += tmp;
    }

    if(input.empty()){
        std::cout << "Insufficient data from input file." << std::endl;
    }else{
        HuffmanTree tree(input);

        std::cout << "Enter the name of the output file." << std::endl;
        std::getline(std::cin, output);
        std::ofstream o(output);

        output = tree.compress(input);

        o << tree.serialize() << '\n';
        o << output;

        tree.degreeOfCompression(input, output);
    }
}

void Regime::decompressRegime(){
    std::cout << "Enter the name of input file." << std::endl;
    std::string input, output;
    std::cin.ignore();
    std::getline(std::cin, input);
    std::ifstream i(input);

    std::string line1, line2;
    std::getline(i, line1);
    std::getline(i, line2);

    if(line1.empty() || line2.empty()){
        std::cout << "Insufficient data from input file." << std::endl;
    }else{
        std::cout << "Enter 'a' for a[lternative] decompress regime (debug regime)." << std::endl;
        std::cout << "Enter 'n' for n[ormal] decompress regime in an output file." << std::endl;
        char choice;
        std::cin >> choice;

        if(choice == 'a'){
            size_t index = 0;
            HuffmanTree tree(line1, index);

            std::cout << tree.debug(line2) << std::endl;
        }else if(choice == 'n'){
            std::cout << "Enter the name of the output file." << std::endl;
            std::cin.ignore();
            std::getline(std::cin, output);
            std::ofstream o(output);

            size_t index = 0;
            HuffmanTree tree(line1, index);
            
            o << tree.decompress(line2);
        }else{
            std::cout << "Unknown command entered." << std::endl;
        }
    }
}

void Regime::visualRegime(){
    std::string text;
    std::cout << "Write down a text you want to encode & decode." << std::endl;
    std::cin.ignore();
    std::getline(std::cin, text);

    if(text.empty()){ // need symbols to work with
        std::cout << "No string of symbols entered." << std::endl;
        return;
    }

    HuffmanTree tree(text);
    std::string compressedText = tree.compress(text);
    std::cout << "The compressed text: " << compressedText << std::endl;
    std::cout << "The decompressed text: " << tree.decompress(compressedText) << std::endl;
    std::cout << "The text in debug regime: " << tree.debug(compressedText) << std::endl;
    tree.degreeOfCompression(text, compressedText);
}