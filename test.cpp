#include <iostream>
#include <ios>
//#include <ctime>
#include "RREF.hpp"

int main(){

    float matrix[] = {2.0, -1.0, 3.0, 1.0, 0.0, 2.0, 3.0, -1.0, 5.0};
    //correct rref: 1, 0, 2, 0, 1, 1, 0, 0, 0
    float * mp = matrix;
    to_rref(mp, 3, 3);
    print_matrix(matrix, 3, 3);

    float matrix1[] = {1, -4, 12, 2, -10, 36, 1, -4, 15};
    //correct rref: I
    to_rref(matrix1, 3, 3);
    print_matrix(mp, 3, 3);

    float matrix2[] = {1, 2, 3, 3, 6, 9, -2, -4, -6};
    //correct rref: 1, 2, 3, 0...
    to_rref(matrix2, 3, 3);
    print_matrix(matrix2, 3, 3);

    float matrix3[] = {1, -2, 2, -4};
    //correct rref: 1, -2, 0...
    to_rref(matrix3, 2, 2);
    print_matrix(matrix3, 2, 2);

    float matrix4[] = {2, 8, 2, 11};
    //correct rref: I
    to_rref(matrix4, 2, 2);
    print_matrix(matrix4, 2, 2);

    float matrix5[] = {-19, 0, -5, 0, 4, 0, 1, 0, -31, 0, -7, 0};
    //correct rref: 1 0 0 0, 0 0 1 0, 0 0 0 0
    to_rref(matrix5, 3, 4);
    print_matrix(matrix5, 3, 4);

    float matrix6[] = {-5, -3, 1, -15, 12, 7, -2, 35, -6, -3, 1, -15};
    //correct rref: 1 0 0 0, 0 1 0 5, 0 0 1 0
    to_rref(matrix6, 3, 4);
    print_matrix(matrix6, 3, 4);

}