#include "MathLibrary.h"
#include <iostream>
#include <cstdlib>


using namespace MathLibrary;
using namespace std;

void matrix::randomFill(){
    srand(time(0));
    for(int i = 0; i < getRow(); i++){
        for(int j = 0; j < getCol(); j++){
            float val = (float) rand()/RAND_MAX;
            val = val*2 - 1;
            set(i, j, val);
        }
    }
}

float dot(float* a, float* b, int n){
    float sum = 0;
    for(int i = 0; i < n; i++){
        sum += a[i]*b[i];
        //cout << sum << " " << a[i] << " " << b[i] << endl;
    }
    return sum;
}

matrix matrix::multiply(matrix other){
    if(other.getRow() != this->getCol()){
        cout << "Multiply: Error dimensions do not match" << endl;
        matrix result(0, 0);
        return result;
    }
    matrix result(this->getRow(), other.getCol());
    //this->print();
    //other.print();
    //cout << other.getCol() << endl;
    //float* col_ar = other.colArr(0);
    //for(int i = 0; i < other.getRow(); i++){
        //cout << col_ar[i] << endl;
    //}
    for(int i = 0; i < this->getRow(); i++){
        for(int j = 0; j < other.getCol(); j++){
            float *col_arr = other.colArr(j);
            result.set(i, j, dot(col_arr, this->rowArr(i), other.getRow()));
            delete col_arr;
        }
    }
    //float a_ar[] = {0, 1, 2, 3, 4, 5};
   // float b_ar[] = {2, 2, 2, 2, 2, 2};
    //cout << dot(a_ar, b_ar, 6) << endl;
 //   cout << "Deleted Yet?" << endl;
    return result;
}

matrix matrix::multiply(float scalar){
    matrix result(this->getRow(), this->getCol());
    for(int i = 0; i < this->getRow(); i++){
        for(int j = 0; j < this->getCol(); j++){
            result.set(i, j, this->get(i, j)*scalar);
        }
    }
    return result;
}

matrix matrix::add(matrix other){
    if(other.getCol() != this->getCol() || other.getRow() != this->getRow()){
        cout << "Add: Error: dimensions do not match" << endl;
        matrix null;
        return null;
    }
    matrix result(this->getRow(), this->getCol());
    for(int i = 0; i < this->getRow(); i++){
        for(int j = 0; j < this->getCol(); j++){
            result.set(i, j, this->get(i, j) + other.get(i, j));
        }
    }
    return result;
}

matrix matrix::transpose(){
    matrix result(this->getCol(), this->getRow());
    for(int i = 0; i < this->getRow(); i++){
        for(int j = 0; j < this->getCol(); j++){
            result.set(j, i, this->get(i, j));
        }
    }
    return result;
}

void matrix::print(){
    for(int i = 0; i < getRow(); i++){
        for(int j = 0; j < getCol(); j++){
            cout << get(i , j) << " ";
        }
        cout << endl;
    }
} 





