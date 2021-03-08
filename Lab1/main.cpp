#include <iostream>
#include <cmath>
using namespace std;
#include <fstream>
#include <string>


int readMatrixSizeFromFile(){
    ifstream fin("C:\\Computational_Math\\Lab1\\size.txt");
    int data;
    fin >> data;
    cout << "The size of matrix equals: ";
    cout << data << endl;
    return data;
}

double readAccuracyFromFile(double accuracy){
    ifstream fin("C:\\Computational_Math\\Lab1\\accuracy.txt");
    double data;
    fin >> data;
    return data;
}

int readMatrixFromFile(double matrix[20][20], int n){
    ifstream fin("C:\\Computational_Math\\Lab1\\matrix.txt");
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            fin >> matrix[i][k];
        }
    }
}

int readBFromFile(double b[20], int n){
    ifstream fin("C:\\Computational_Math\\Lab1\\b.txt");
    for (int i = 0; i < n; ++i) {
        fin >> b[i];
        cout << "В[" << i + 1 << "] = ";
        cout << b[i];
    }
}

bool compareMainDiagonal(int n, double matrix[20][20]){
    double neighbors;
    double compared;
    int status = 1;
    for (int i = 0; i < n; ++i) {
        neighbors = 0;
        compared = matrix[i][i];
        for (int j = 0; j < n; ++j) {
            neighbors = neighbors + matrix[i][j];
        }
        neighbors = neighbors - compared;

        if(compared > neighbors){
            status = 1;
            cout << compared << " bigger than neighbors " << endl;
        }else{
            status = 0;
            cout << compared << " less than neighbors " << endl;
        }
    }

    return (status == 1);
}

// Условие окончания
bool limitingAccuracy(double currentValues[20], double lastValues[20], int n, double accuracy)
{
    double delta = 0;
    for (int i = 0; i < n; i++)
        delta += (currentValues[i] - lastValues[i]) * (currentValues[i] - lastValues[i]);
    return (sqrt(delta) < accuracy);
}

double settingAccuracy(double rounded, double accuracy)
{
    int i = 0;
    double newaccuracy = accuracy;
    while (newaccuracy < 1)
    {
        i++;
        newaccuracy *= 10;
    }
    int okr = pow(double(20), i);
    rounded = int(rounded * okr + 0.5) / double(okr);

    return rounded;
}


int main()
{
    int choice;
    double accuracy;
    double matrix[20][20];
    double b[20], x[20], p[20];
    int n, i, j, m = 0;
    int method;

    //Entering Size
    cout << "Enter the size of the square matrix: " << endl;
    cout << "   If you want to enter from file, print 1. Else print any number: " << endl;
    cin >> choice;
    if(choice == 1){
        n = readMatrixSizeFromFile();
    }else{
        cin >> n;
        cout << "The size of matrix equals: ";
        cout << n << endl;
    }

    //Entering Accuracy
    cout << "Enter the calculation precision: " << endl;
    cout << "   If you want to enter from file, print 1. Else print any number: " << endl;
    cin >> choice;
    if(choice == 1){
        accuracy = readAccuracyFromFile(accuracy);
        cout << "The accuracy equals: ";
        cout << accuracy << endl;
    }else{
        cin >> accuracy;
        cout << "The accuracy equals: ";
        cout << accuracy << endl;
    }

    //Entering Matrix
    cout << "Fill in matrix A: " << endl << endl;
    cout << "   If you want to enter from file, print 1. Else print any number: " << endl;
    cin >> choice;
    if(choice == 1){
        readMatrixFromFile(matrix, n);
    }else{
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
            {
                cout << "A[" << i << "][" << j << "] = ";
                cin >> matrix[i][j];
            }
        cout << endl << endl;
    }
    cout << "Your matrix A: " << endl << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }

    cout << endl;

    //Entering B
    cout << "Fill in the free members column: " << endl << endl;
    cout << "   If you want to enter from file, print 1. Else print any number: " << endl;
    cin >> choice;
    if(choice == 1){
        readBFromFile(b, n);
    }else{
        for (i = 0; i < n; i++)
        {
            cout << "В[" << i + 1 << "] = ";
            cin >> b[i];
        }
    }

    cout << endl << endl;

    for (int i = 0; i < n; i++)
        x[i] = 1;
    cout << "Diagonal dominance: " << endl;
    if (compareMainDiagonal(n, matrix)) {
        do
        {
            for (int i = 0; i < n; i++)
                p[i] = x[i];
            for (int i = 0; i < n; i++)
            {
                double var = 0;
                for (int j = 0; j < i; j++)
                    var += (matrix[i][j] * x[j]);
                for (int j = i + 1; j < n; j++)
                    var += (matrix[i][j] * p[j]);
                x[i] = (b[i] - var) / matrix[i][i];
            }
            m++;
        } while (!limitingAccuracy(x, p, n, accuracy));

        for (int k = 0; k < n; ++k) {
            cout << "Vector: ";
            cout << "x";
            cout << k+1 << endl;
            cout << "|";
            cout << x[k];
            cout << " - ";
            cout << p[k];
            cout << "|";
            cout << "=";
            cout << x[k] - p[k] << endl;
        }
        cout << "System solution:" << endl;
        for (i = 0; i < n; i++) cout << "x" << i << " = " << settingAccuracy(x[i], accuracy) << "" << endl;
        cout << "Iterations: " << m << endl;
    }
    else {
        cout << "Dominance of diagonals is not fulfilled" << endl;
    }


    system("pause");
    return 0;
}