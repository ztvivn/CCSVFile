#include <iostream>
#include <fstream>
#include <vector>
#include "real.h"


int main() {
    CCSVFile file("info");

    file.Seek("Ivan");
    std::cout << file.Read(4) << "\n";
    file.Write("6, Anton, 23, 56");
    file.Write("7, Anton, 26, 55");
    std::cout << file.Read(6) << "\n";

    CBinFile file1("Br");
    file1.Write(3, 22, 179);

    file1.Read(0);

    return 0;
}