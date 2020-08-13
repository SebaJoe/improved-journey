#include <iostream>

using namespace std;


namespace MathLibrary{
    class matrix
    {
        private:
            float mat[200][200];
            int row {0};
            int col{0};
        public:
            matrix(){}
            matrix(int x, int y){
                create(x, y);
            }
            matrix(int x, int y, float num){
                create(x, y, num);
            }
            void create(int x, int y){
                row = x;
                col = y;
            }

            void create(int x, int y, float num){
                row = x;
                col = y;
                for(int i = 0; i < row; i++){
                    for(int j = 0; j < col; j++){
                        mat[i][j] = num;
                    }
                }
            }

            void inputs(float ar[]){
                for(int i = 0; i < row; i++){
                    for(int j = 0; j < col; j++){
                        mat[i][j] = ar[j + col*i];
                    }
                }
            }
            void randomFill();
            float get(int x, int y) {
                return mat[x][y];
            }
            void set(int x, int y, float val){
                mat[x][y] = val;
            }
            int getCol(){
                return col;
            }
            int getRow(){
                return row;
            }
            float* rowArr(int rowQ){
                return mat[rowQ];
            }
            float* colArr(int colQ){
                //static float sir[row];
                float *sir = new float[row]; //dynamically allocated array; needs to be deleted.
                for(int i = 0; i < row; i++){
                    sir[i] = mat[i][colQ];
                    //cout << sir[i] << endl;
                }
                return sir;
            }
            matrix multiply(matrix other);
            matrix transpose();
            matrix add(matrix other);
            matrix multiply(float scalar);
            matrix transform(float (*func)(float)){
                matrix result(this->getRow(), this->getCol());
              //  cout << "Transform Test (input 10): " << func(10) << endl; 
                for(int i = 0; i < getRow(); i++){
                    for(int j = 0; j < getCol(); j++){
                        result.set(i, j, func(this->get(i, j)));
                //        cout << "Function: " << func(this->get(i, j));
                  //      cout << "Before: " << this->get(i, j) << " After: " << result.get(i, j) << endl;
                    }
                }
                return result;
            }
            void standardizeByCol() {
                for(int i = 0; i < col; i++){
                    float max_num = this->get(0, i);
                    for(int j = 1; j < row; j++){
                        if(max_num < this->get(j, i)){
                            max_num = this->get(j, i);
                        }
                    }
                    for(int j = 0; j < row; j++){
                        float cur_num = this->get(j, i);
                        this->set(j, i, cur_num/max_num);
                    }
                }
            }
            void standardizeByRow() {
                for(int i = 0; i < row; i++){
                    float max_num = this->get(i, 0);
                    for(int j = 1; j < col; j++){
                        if(max_num < this->get(i, j)){
                            max_num = this->get(i, j);
                        }
                    }
                    for(int j = 0; j < col; j++){
                        float cur_num = this->get(i, j);
                        this->set(i, j, cur_num/max_num);
                    }
                }
            }
            void print();
            void copy(matrix other){
                row = other.getRow();
                col = other.getCol();
                for(int i = 0; i < row; i++){
                    for(int j = 0; j < col; j++){
                        this->set(i, j, other.get(i, j));
                    }
                }
            }
            matrix hadamard(matrix other){
                matrix result(other.getRow(), other.getCol());
                for(int i = 0; i < row; i++){
                    for(int j = 0; j < col; j++){
                        result.set(i, j, this->get(i, j)*other.get(i, j));
                    }
                }
                return result;
            }
    };
}
