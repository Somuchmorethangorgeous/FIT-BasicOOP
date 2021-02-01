#include <iostream>
#include <tuple>
#include <fstream>
#include "CSVParser.h"
#include "tuple_print.h"


int main() {
    std::ifstream file("file.csv");
    CSVParser<int, float, double, std::string> parser(file, 0 /*skip first lines count*/);
    for (const std::tuple<int, float, double, std::string>& res : parser){
        std::cout << res << std::endl;
    }
    return 0;
}