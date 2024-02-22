#include <iostream>
#include <sstream>
#include <string>

#include <cstdio>
#include <sstream>
#include <algorithm>
int main()
{
    std ::string tes="sss dvf";
    std ::string ::iterator end=std::remove(tes.begin(), tes.end(), '\r');
     for (std::string::iterator it = tes.begin(); it != end; ++it) {
        std::cout << *it;
    }
    // function
    void split()
}

// int main() {
//     std::string inputString = "   Hello,  \r  World!    ";
//     std::istringstream inputStream(inputString);
    
//     std::string word1, word2;
    
//     // Extraction with std::ws
//     inputStream >> std::ws >> word1;
//     inputStream >> std::ws >> word2;
    
//     std::cout << "With std::ws:" << std::endl;
//     std::cout << "Word 1: " << word1 << std::endl;
//     std::cout << "Word 2: " << word2 << std::endl;
    
//     // Reset the stream state
//     inputStream.clear();
//     inputStream.seekg(0);
    
//     // Extraction without std::ws
//     inputStream >> word1;
//     inputStream >> word2;
    
//     std::cout << "Without std::ws:" << std::endl;
//     std::cout << "Word 1: " << word1 << std::endl;
//     std::cout << "Word 2: " << word2 << std::endl;
    
//     return 0;
// }