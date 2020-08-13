#include <iostream>

using namespace std;

float func1(int n){
    cout << "func1 is called" << endl;
    return n;
}

void func2(float (*func)(int)){
    func(1);
}

int main(){
    func2(func1);
    return 0;
}
