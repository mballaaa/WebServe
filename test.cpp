#include <iostream>
#include <string>
#include "dirent.h"
#include <unistd.h>

int main() {
    const char *ptr = "/var/www/html/test";

    // Print effective user and group IDs
    std::cout << "Effective User ID: " << geteuid() << std::endl;
    std::cout << "Effective Group ID: " << getegid() << std::endl;

    // Check if the program has read and execute permissions for the directory
    if (access(ptr, R_OK | X_OK) == 0) {
        // The program has the necessary permissions
        DIR *dir = opendir(ptr);
        if (dir) {
            std::cout << "Successfully opened the directory\n";
            closedir(dir);
        } else {
            std::cerr << "Failed to open the directory: ";
            perror("opendir");
        }
    } else {
        // The program does not have the necessary permissions
        std::cerr << "Insufficient permissions to access the directory\n";
    }

    return 0;
}
