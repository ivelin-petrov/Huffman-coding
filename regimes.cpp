#include "regimes.h"

void Regime::compressRegime(){
    std::cout << "Enter the name of input file." << std::endl;
    std::string input, output; // file names
    std::cin.ignore();

    std::getline(std::cin, input);
    std::ifstream i(input);

    std::string line1, line2;

    if(!i.is_open()){
        std::cout << "Nonexistent file." << std::endl;
    }else{
        while(i){
            char c;
            i.get(c);
            if(c != '\n'){
                line1.push_back(c);
            }
        }

        line1.pop_back();

        if(line1.empty()){
            std::cout << "Insufficient data from input file." << std::endl;
        }else{
            HuffmanTree tree(line1);

            std::cout << "Enter the name of the output file." << std::endl;
            std::getline(std::cin, output);
            std::ofstream o(output);

            line2 = tree.compress(line1);

            o << tree.serialize() << '\n';
            o << line2;

            tree.degreeOfCompression(line1, line2);
        }
    }
}

void Regime::decompressRegime(){
    std::cout << "Enter the name of input file." << std::endl;
    std::string input, output; // file names
    std::cin.ignore();
    std::getline(std::cin, input);
    std::ifstream i(input);

    std::string line1, line2;
    std::getline(i, line1);
    std::getline(i, line2);


    if(!i.is_open()){
        std::cout << "Nonexistent file." << std::endl;
    }else{
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
