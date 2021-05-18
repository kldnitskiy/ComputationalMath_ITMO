#include <iostream>
#include <cmath>
using namespace std;
double alpha0=2; double alpha1=-2.5; double Ac=0;
double beta0=3; double beta1=-3.4; double Bc=5;
double a0=0.1; double b0=1.3;
int n=4;
double p(double x){
    return exp(x);
}

double q(double x){
    return 2*x;
}

double f(double x){
    return pow(x,3);
}

void InputMode(){
    //INPUT
    cout << "Enter b from [a,b]" << endl;
    cin >> b0;

    cout << "Enter a from [a,b]" << endl;
    cin >> a0;

    cout << "Enter n" << endl;
    cin >> n;

    cout << "Enter alpha0" << endl;
    cin >> alpha0;

    cout << "Enter alpha1" << endl;
    cin >> alpha1;

    cout << "Enter beta0" << endl;
    cin >> beta0;

    cout << "Enter beta1" << endl;
    cin >> beta1;

    cout << "Enter number for the first equation" << endl;
    cin >> Ac;

    cout << "Enter number for the second equation" << endl;
    cin >> Bc;
}


void gauss(double** A, double* B, double* X, int n);

void Progonka(double **A, double h, double *X, double *B){
    for(int i=0; i<=n-2; i++){
        A[i][i]=h*h*q(X[i])-h*p(X[i])+1;
        A[i][i+1]=h*p(X[i])-2;
        A[i][i+2]=1;
        B[i]=h*h*f(X[i]);
    }
    A[n-1][0]=alpha0*h-alpha1;
    A[n-1][1]=alpha1;
    A[n][n-1]=-beta1;
    A[n][n]=beta0*h+beta1;
    B[n-1]=h*Ac;
    B[n]=h*Bc;
}

void RenderMatrix(double **A, double *B){
    //print A
    for(int i=0; i<=n; i++){
        for(int j=0; j<=n; j++){
            cout << "A["<<i<<"]"<<"["<<j<<"]="<<A[i][j] <<" ";
            if(j==n)
                cout << endl;
        }
        cout << endl;
    }

    cout << endl;
    //print B
    for(int i=0; i<=n; i++){
        cout << "B["<<i<<"]="<<B[i] <<" ";
    }
    cout << endl;
    cout << endl;
}

int main() {
    int mode = 0;

    cout << "Do you want to use custom data? Print 1, or print anything else to continue with basic set." << endl;
    cin >> mode;

    if(mode == 1)
        InputMode();
    else{
        cout << "y'' + e^xy' + 2xy = x^3" << endl;
        cout << "on [0,1;1,3], n = 4" << endl << endl;
        cout << "Starting conditions: " << endl;
        cout << "2y(0,1) - 2.5y'(0,1) = 0 " << endl;
        cout << "3y(1,3) - 3.4y'(1,3) = 5 " << endl << endl;
        cout << "p(x) = e^x, q(x) = 2x, f(x) = 3x^3 " << endl;
        cout << "alpha0 = 2, alpha1 = -2.5, A = 0 " << endl;
        cout << "beta0 = 3, beta1 = -3.4, B = 5 " << endl << endl;
    }


    //matrix A[n+1][n+1]
    double **A = new double*[n+1];
    for(int i=0; i<n+1; i++){
        A[i]=new double[n+1];
    }

    double *B = new double[n+1]; //vector B[n+1]
    double *X = new double[n+1]; //vector X[n+1]

    //Grid
    double h=(b0-a0)/n;
    for(int i=0; i<=n; i++){
        X[i]=a0+i*h;
        //cout << X[i] << endl;
    }

    cout << "h=" << h << endl;
    //calculate matrix A, B

    Progonka(A, h, X, B);
    RenderMatrix(A,B);


    //solve A*X1=B
    double *X1 = new double[n+1]; //vector X1[n+1]
    gauss(A,B,X1,n+1); //solve
    //print X1
    for(int i=0; i<=n; i++){
        cout << "X1[" << i << "]=" << X1[i] << " ";
    }

    return 0;
}




void gauss(double** A, double* B, double* X, int n){
    int m=n+1;
    //create C[n][n+1]
    double **C = new double*[n];
    for(int i=0; i<n; i++){
        C[i]=new double[n+1];
    }
    //===
    //split A and B to C
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            C[i][j]=A[i][j];
        }
        C[i][n]=B[i];
    }
    //forward
    for (int k=0; k<n-1; k++){
        for (int i=k+1;i<n;i++){
            for (int j=m-1; j>=k; j--){
                C[i][j]=C[i][j]-C[i][k]*C[k][j]/C[k][k];
            }
        }
    }
    //reverse
    X[n-1]=A[n-1][m-2]/A[n-1][m-2];

    for (int i=n-2; i>=0; i--){
        double s=0;
        for (int j=i+1;j<m-1;j++){
            s=s+C[i][j]*X[j];
        }
        X[i]=(C[i][m-1] - s)/C[i][i];
    }

}