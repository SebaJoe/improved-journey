#include "MathLibrary.h"
#include <iostream>
#include <cmath>

using namespace MathLibrary;
using namespace std;



//these are all the matrix functions that are used for transform
float sigmoid(float z){
    return 1/(1+exp(-1*z));
}

float square(float z){
    return z*z;
}

float sigmoidPrime(float z){
    return exp(-1*z)/(square(1 + exp(-1*z)));
}

float relu(float z){
    return (z > 0) ? z: 0;
}

float reluPrime(float z){
    return (z > 0) ? 1: 0;
}

class Neural_Net{
    public:
        //This is the constructor for the neural net: 
        //This class only acommadate 3 three layers: number of nodes on each layer is specifiable
        //randomly initializes all the weights and biases
        Neural_Net(int in, int hid, int out, float (*activ)(float), float (*prime)(float)){
            inputSize = in;
            hiddenSize = hid;
            outputSize = out;
            activation = activ;
            activationPrime = prime;
            W1.create(inputSize, hiddenSize);
            W1.randomFill();
            W2.create(hiddenSize, outputSize);
            W2.randomFill();
            b1.create(1, hiddenSize);
            //b1.randomFill(); //comment out if you don't want to add biases yet
            b2.create(1, outputSize);
            //b2.randomFill();
        }

        //This is the feedforward propagation algorithm
        //However the way the network is set up the variables are separated into columns as opposed to rows
        //the number of columns in matrix X has to match inputSize; the rows represent the number of data points
        //a static sigmoid function is used. However, the activation function is designed to be highly modular
        matrix propagate(matrix X){
               matrix eb1 = expand(b1, X.getRow(), hiddenSize);
               matrix eb2 = expand(b2, X.getRow(), outputSize);
               //cout << "W1:" << endl;
               //W1.print();
               //cout << "W2:" << endl;
               //W2.print();
               z2 = X.multiply(W1).add(eb1);
               //cout << "z2:" << endl;
               //z2.print();
               a2 = z2.transform(activation);
               //cout << "a2:" << endl;
               //a2.print();
               z3 = a2.multiply(W2).add(eb2);
               //cout << "z3:" << endl;
               //z3.print();
               matrix yHat = z3.transform(activation);
               return yHat;
        }
        //The cost function for the network is based on the squared error function
        float cost(matrix X, matrix y){
            matrix yHat = propagate(X);
            matrix costs = y.add(yHat.multiply(-1)).transform(square);
            float total_cost = 0;
            for(int i = 0; i < costs.getRow(); i++){
                total_cost += costs.get(i, 0);
            }
            return total_cost;
        }
        //finding the gradient of the cost function based on 4 matrices: W1, W2, b1, b2
        //from now on cost is referred as C
        void costPrime(matrix X, matrix y){  
            //first propagate: updates all the inbetweens 
            matrix yHat = propagate(X);
            //cout << "Breakpoint 1:" << endl;
            //cout << y.getRow() << " " << y.getCol() << " " << z3.getRow() << " " << z3.getCol() << endl;
            matrix delta3 = y.add(yHat.multiply(-1)).multiply(2).hadamard(z3.transform(activationPrime));
            //cout << "Breakpoint 2:" << endl;
            matrix dCdW2 =  a2.transpose().multiply(delta3);
            //cout << "Breakpoint 3:" << endl;
            matrix delta2 = delta3.multiply(W2.transpose()).hadamard(z2.transform(activationPrime));
            //cout << "Breakpoint 4:" << endl;
            matrix dCdW1 = X.transpose().multiply(delta2);
            //cout << "Breakpoint 5:" << endl;
            gradients[0] = dCdW1; gradients[1] = dCdW2;
        }
        //I guess the gradient decsent will be based on a sort of BFGS algorithm, as I got it from
        //the wikipedia page (more info here: https://en.wikipedia.org/wiki/Broyden%E2%80%93Fletcher%E2%80%93Goldfarb%E2%80%93Shanno_algorithm).
        float train(matrix X, matrix y, float rounds) {
            W1.print();
            W2.print();
            for(int i = 0; i < rounds; i++){
                costPrime(X, y);
                W1 = W1.add(gradients[0]);
                W2 = W2.add(gradients[1]);
            }
            return cost(X, y);
        }

    private:
        int inputSize;
        int hiddenSize;
        int outputSize;
        float (*activation)(float);
        float (*activationPrime)(float);
        matrix W1;
        matrix W2;
        matrix z2;
        matrix a2;
        matrix z3;
        matrix b1;
        matrix b2;
        matrix gradients[4];
        matrix expand(matrix mat, int X_size, int otherSize){
            matrix result1(X_size, otherSize);
            for(int i = 0; i < X_size; i++){
                for(int j = 0; j < otherSize; j++){
                    result1.set(i, j, mat.get(0, j));
                }
            }
            return result1;
        }
};


int main() {
 /*   matrix m(5, 5);
    for(int i = 0; i < m.getRow(); i++){
        for(int j = 0; j < m.getCol(); j++){
            m.set(i , j, i + j);
        }
    }
    m.print();
    matrix m2(5, 1);
    for(int i = 0; i < m2.getRow(); i++){
        m2.set(i, 0, 2);
    }
    m2.print();
    //cout << m2.getCol() << endl;
    matrix m3 = m.multiply(m2);
    m3.print();
*/
 //   matrix ar[100];
    
   // for(int i = 0; i < 100; i++){
     //   ar[i].create(100, 100);
   // }
    
   // matrix ar2[50];

    //for(int i = 0; i < 50; i++){
      //  ar2[i] = ar[i].multiply(ar[i+50]);
    //}
    Neural_Net n1(2, 3, 1, sigmoid, sigmoidPrime);//Neural Net with 2 input nodes, 3 hidden nodes, and 1 output node.
    
    cout << "Sigmoid Value (input 10): " << sigmoid(10) << endl;

    matrix x_vals(3, 2);
    matrix y_vals(3, 1);
    float dataX[] = {3, 5, 5, 1, 10, 2};
    float dataY[] = {0.75, 0.82, 0.93};
    x_vals.inputs(dataX);
    x_vals.standardizeByCol();
    y_vals.inputs(dataY);
    cout << "X_vals:" << endl;
    x_vals.print();
    cout << "Y_vals:" << endl;
    y_vals.print();
    //x_vals.print();
    matrix sigs = x_vals.transform(sigmoid);
    matrix test_1 = x_vals.transform(sigmoidPrime);
    cout << "sigmoidPrime through transform" << endl;
    test_1.print();
    matrix ones(sigs.getRow(), sigs.getCol(), 1);
    matrix test_2 = sigs.hadamard(ones.add(sigs.multiply(-1)));
    cout << "sigmoidPrime through rho(1-rho)" << endl;
    test_2.print();
    
    matrix output = n1.propagate(x_vals);
    cout << "Output: " << endl;
    output.print();
    //float initialCost = n1.cost(x_vals, y_vals);
    //n1.costPrime(x_vals, y_vals);
    for(int i = 0; i < 4; i++){
    float initialCost = n1.cost(x_vals, y_vals);
    float finalCost = n1.train(x_vals, y_vals, 60000);
    cout << "Initial Cost: " << initialCost <<  " The final cost: " << finalCost << endl;
    cout << "Cost decreased by: " << initialCost - finalCost << endl;
    output = n1.propagate(x_vals);
    cout << "Trained Output: " << endl;
    output.print();
    }
    
}
