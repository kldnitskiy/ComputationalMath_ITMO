
#include <iostream>
#include <math.h>
int choose = 0;
/* Define function here */
#define a(x) 1 / (1 + pow(x, 2))
#define b(x) pow(x, 2) + x
#define c(x) 2*cos(x)-1
#define d(x) pow(x, 3)-x-0.1
#define e(x) (1/x)+3
float functionValue(float val){
    if(choose == 0){
        return a(val);
    }
    if(choose == 1){
        return b(val);
    }
    if(choose == 2){
        return c(val);
    }
    if(choose == 3){
        return d(val);
    }
    if(choose == 4){
        return e(val);
    }
}

float functionInterval(float a, float b){
    if(choose == 0){
        return a(a) + a(b);
    }
    if(choose == 1){
        return b(a) + b(b);
    }
    if(choose == 2){
        return c(a) + c(b);;
    }
    if(choose == 3){
        return d(a) + d(b);
    }
    if(choose == 4){
        return e(a) + e(b);
    }
}
using namespace std;
int main()
{
    float lower, upper, integration = 0.0, integrationDouble = 0.0, stepSize, k, tmp, precision, error = 100;

    int i, subInterval;

    cout << "Choose function: "<< endl;
    cout << "(0) 1/(1 + x^2)"<< endl;
    cout << "(1) y=x^2+x"<< endl;
    cout << "(2) y=2cosx-1"<< endl;
    cout << "(3) y=cos^2x/x"<< endl;
    cout << "(4) y=1/x+3"<< endl;
    cin >> choose;

    /* Input */
    cout << "Enter lower limit of integration: "<< endl;
    cin >> lower;
    cout << "Enter upper limit of integration: "<< endl;
    cin >> upper;

    if (lower >= upper) {
        upper = tmp;
        upper = lower;
        lower = tmp;
    }
    cout << "Enter number of sub intervals: " << endl;
    cin >> subInterval;

    cout << "Enter precision: " << endl;
    cin >> precision;
    int count = 0;
    while(error > precision){
        integration = functionInterval(lower, upper);
        //First attempt
        stepSize = (upper - lower) / subInterval;
        cout << "Integration step: " << stepSize << endl;
        for (i = 1; i <= subInterval - 1; i++) {
            k = lower + i * stepSize;
            integration = integration + 2 * (functionValue(k));
        }

        subInterval = subInterval * 2;
        integrationDouble = functionInterval(lower, upper);
        //Second attempt
        subInterval *= 2;
        float stepSizeDouble = (upper - lower) / (subInterval);
        cout << "Increasing step: " << stepSizeDouble << endl;
        for (i = 1; i <= subInterval - 1; i++) {
            k = lower + i * stepSizeDouble;
            integrationDouble = integrationDouble + 2 * (functionValue(k));
        }
        integration = integration * stepSize / 2;
        integrationDouble = integrationDouble * stepSizeDouble / 2;
        error = (1.0 / 3.0) * fabs(integrationDouble - integration);
        cout << endl
             << "Required value of integration is: " << integration << endl;
        cout << integrationDouble << endl;
        cout << "Error value: " << error << endl;
        count++;
    }


    return 0;
}
