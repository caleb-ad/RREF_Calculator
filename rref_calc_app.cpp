#include <iostream>
#include <string>
#include <sstream>
#include "RREF.hpp"

using std::string;

int main(){
    //read matrix in form: columns,rows,entries..., "\n"
    char text[50];
    int columns;
    int rows;

    std::cin.get(text, 50, ',');
    columns = std::stoi(string(text));
    std::cin.ignore();

    std::cin.get(text, 50, ',');
    rows = std::stoi(string(text, 0, std::cin.gcount()));
    std::cin.ignore();

    float matrix[columns * rows];
    int idx = 0;
    while(std::cin.peek() != '\n'){
        std::cin.get(text, 50, ',');
        matrix[idx] = std::stof(string(text, 0, std::cin.gcount()));
        std::cin.ignore();
        idx += 1;
    }

    to_rref(matrix, rows, columns);
    
    std::cout.precision(6);
    for(int a=0; a<rows*columns; a++){
        std::cout << (float)matrix[a] << ',';
    }
    std::cout << std::endl;
}