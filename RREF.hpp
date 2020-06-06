#ifndef RREF
#define RREF
#include <string>
using std::string;

//adds row1 * coeff to row2 of matrix with m columns, the first row is 0
void add_row(float * matrix, int m, int row1, int row2, float coeff){
    for(int a=0; a<m; a++){
        *(matrix + m*row2 + a) += *(matrix + m*row1 + a) * coeff;
    }
}

//scales row in matrix by scale
void scale_row(float * matrix, int m, int row, float scale){
    for(int a=0; a<m; a++){
        *(matrix + row * m + a) *= scale;
    }
}

//swap row1 with row2 in a matrix with m columns
void swap_row(float * matrix, int m, int row1, int row2){
    for(int a=0; a<m; a++){
        float temp = *(matrix + row1*m + a);
        *(matrix + row1*m + a) = *(matrix + row2*m + a);
        *(matrix + row2*m + a) = temp;
    }
}

//print matrix with n rows and m columns
void print_matrix(float * matrix, int n, int m){
    std::cout.precision(6); //floats only have ~7 signifigant figures
    for(int a=0; a<n; a++){
        for(int b=0; b<m; b++){
            string s = string(std::to_string(matrix[a*m+b]), 0, 5);
            if(s.length() < 5)s.append(5 - s.length(), '0');
            std::cout<< s << " ";
        }
        std::cout<< std::endl;  
    }
    std::cout<< std::endl;
}

//Reduces matrix with n rows and m columns to RREF
float* to_rref(float * matrix, int n, int m){
    int size = n;
    if(m < n)size = m;
    //so pivots don't have to be "refound"
    int pivots[size * 2];
    for(int a=0; a<size*2; a++) pivots[a] = -1;
    int p_index = 0;
    int level = 0;
    for(int a=0; a<m; a++){
        bool skip = false;
        int swp = level+1;
        while(*(matrix +level*m + a) == 0){
            if(swp == n){
                skip = true; 
                break;
            }
            swap_row(matrix, m, level, swp);
            swp += 1;
        }
        if(!skip){
            scale_row(matrix, m, level, 1/ *(matrix + level*m + a));
            for(int b=level+1; b<n; b++){
                add_row(matrix, m, level, b, -*(matrix + b*m + a));
            }
            pivots[p_index] = level;
            pivots[p_index + 1] = a;
            p_index += 2;
            level += 1;
        }
        if(level == n){
            break;
        }
    }
    //remove values above pivots
    for(int a=size*2 - 1; a > 0; a -= 2){
        if(pivots[a] != -1){
            for(int b=pivots[a-1] - 1; b >= 0; b--){
                add_row(matrix, m, pivots[a-1], b, -*(matrix + b*m + pivots[a]));
            }
        }
    }
}

#endif