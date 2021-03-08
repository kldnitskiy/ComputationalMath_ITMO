//
// Created by firem on 09.03.2021.
//
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
int readMatrix(){
    int choice;
    cin >> choice;
    if(choice==1){
        ifstream fin("C:\\Computational_Math\\Lab1\\matrix.txt");
        for (int i = 0; i < 3; ++i) {
            for (int k = 0; k < 3; ++k) {
                double val;
                fin >> val;
                cout << val;
            }
        }
    }else{
        cout << "DDDD";
    }
}
int main(){
//    ifstream fin("C:\\Computational_Math\\Lab1\\accuracy.txt");
//    double d;
//    fin >> d;
//    cout << d << std::endl;

    readMatrix();
}

