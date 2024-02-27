#include <iostream>
#include <sstream>
#include <string>

#include <cstdio>
#include <sstream>
#include <algorithm>
#include <cstdlib> // for strtol
int main()
{
std::string str = "1";
char* endptr;
long value = strtol(str.c_str(), &endptr, 10);

if (endptr == str.c_str()) {
    std :: cout << endptr << std ::endl;
    // Conversion failed (no digits converted)
    std::cerr << "Error: Invalid numerical string." << std::endl;
} else {
    // Conversion successful, value stores the converted number
    std::cout << "Converted value: " << value << std::endl;
    // You can also check the remaining string using endptr:
    std::cout << "Remaining string: " << endptr << std::endl;
}
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