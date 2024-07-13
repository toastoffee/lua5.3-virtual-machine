#include <iostream>
#include <string>

int main() {
    std::cout << "Hello, World!" << std::endl;

    char* s = (char*)malloc(4);
    snprintf(s, 4, "%x", 12);

    std::string str = s;
    delete[] s;

    printf("%x", true);

    return 0;
}
