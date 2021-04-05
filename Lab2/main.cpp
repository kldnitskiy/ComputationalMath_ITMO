#include <iostream>
#include <math.h>
#include<iomanip>
#include<stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include<conio.h>
#include <windows.h>

#include <math.h>
using namespace std;
std::vector<std::string> expressions = {};

static double func1(double x);
static double func2(double x);
static double func3(double x);

void IterationMethodSystem(int task){
    int step=1, n;
    float leftBorder;
    float rightBorder;
    double x0=0,y0=0,x,y,d1,d2,e=0.0001;
    cout<< setprecision(6)<< fixed;
    cout<<"Enter precision: ";
    cin>>e;

    cout<<"Enter maximum iteration: ";
    cin>>n;

    setlocale(LC_ALL, "Russian");
    do
    {
        if(task == 1){
            x=sin(y0+2)-15;
            y=0.5-cos(x0-2);
            d1=sin(y+2)-x-15;
            x0=x;
            y0=y;
        }else if(task == 2){
            x=pow(y0,2) + 4;
            y=4-sqrt(x0);
            d1=pow(y,2) + 4 - x;
            x0=x;
            y0=y;
        }
        step++;
    }while(abs(d1)>e && step < n);
    cout<<"x="<<x<<endl;
    getch();

}

void IterationMethod(double func(double)){
    cout << "Iteration Method" << endl;
    int step=1, n;
    double b;
    double x0, x1, e;
    double leftBorder = 0;
    double rightBorder = 0;
    cout<< setprecision(6)<< fixed;
    cout<<"Enter left border: ";
    cin>>leftBorder;
    cout<<"Enter right border: ";
    cin>>rightBorder;
    x1 = (leftBorder + rightBorder)/2.0;
    cout<<"Enter precision: ";
    cin>>e;

    cout<<"Enter maximum iteration: ";
    cin>>n;
    do {
        x0 = x1;
        x1 = func1(x0);
        cout << x0 << ":" << x1 << endl;
        b = fabs(x0-x1);
        step++;
    }while (b<e && n>step);
    cout << "Root x0 =" << x0 << "\n";
    cout<<"Iterations n= "<<step<<"\n";
    getch();
}

void ChordMethod(double func(double)){
    cout << "Chord Method" << endl;
    double start;
    double end;
    double p;
    int steps = 0;
    int n = 0;
    cout << "Enter beginning of interval: ";
    cin >> start;
    cout << "Enter end of interval: ";
    cin >> end;
    cout << "Enter precision of method: ";
    cin >> p;
    cout << "Enter steps: ";
    cin >> n;
    if (func(start) * func(end) > 0.0f)
    {
        cout << "Function has same signs at ends of interval";
    }
    double x = (start * func(end) - end * func(start)) / (func(end) - func(start));
    while (abs(func(x)) > p && steps < n) {
        steps++;
        cout << "X: " << x << " f(x): " << func(x) << endl;
        if (func(start) * func(x) < 0) {
            x = (x * func(start) - start * func(x)) / (func(start) - func(x));
        }
        else {
            x = (x * func(end) - end * func(x)) / (func(end) - func(x));
        }
    }
}


const int NUM = 70; // количество точек
LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
double **x; // массив данных
// Задание исходных данных для графика
// (двумерный массив, может содержать несколько рядов данных)
double ** getData(int n)
{
    double **f;
    f = new double*[2];
    f[0] = new double[n];
    f[1] = new double[n];
    for (int i = 0; i<n; i++)
    {
        double x = (double)i * 0.1;
        f[0][i] = x;
        f[1][i] = 3*cos(x)-4*sin(x);
    }
    return f;
}

double ** renderFunc1(int n)
{
    double **f;
    f = new double*[2];
    f[0] = new double[n];
    f[1] = new double[n];
    for (int i = 0; i<n; i++)
    {
        double x = (double)i * 0.1;
        f[0][i] = x;
        f[1][i] = 2*pow(x,3)+3*pow(x,2)+5;
    }
    return f;
}

double ** renderFunc2(int n)
{
    double **f;
    f = new double*[2];
    f[0] = new double[n];
    f[1] = new double[n];
    for (int i = 0; i<n; i++)
    {
        double x = (double)i * 0.1;
        f[0][i] = x;
        f[1][i] = 3*cos(x)-4*sin(x);
    }
    return f;
}

double ** renderFunc3(int n)
{
    double **f;
    f = new double*[2];
    f[0] = new double[n];
    f[1] = new double[n];
    for (int i = 0; i<n; i++)
    {
        double x = (double)i * 0.1;
        f[0][i] = x;
        f[1][i] = pow(sin(x),2)-0.5;
    }
    return f;
}
// Функция рисования графика
void DrawGraph(HDC hdc, RECT rectClient,
               double **x, // массив данных
               int n, // количество точек
               int numrow = 1) // количество рядов данных (по умолчанию 1)
{
    double OffsetY, OffsetX;
    double MAX_X, MAX_Y;
    double ScaleX, ScaleY;
    double min, max;
    int height, width;
    int X, Y; // координаты в окне (в px)
    HPEN hpen;
    height = rectClient.bottom - rectClient.top;
    width = rectClient.right - rectClient.left;
    // Область допустимых значений X
    min = x[0][0];
    max = x[0][0];
    for (int i = 0; i<n; i++)
    {
        if (x[0][i] < min) min = x[0][i];
        if (x[0][i] > max) max = x[0][i];
    }
    double temp = max - min;
    MAX_X = max - min;
    OffsetX = min*width / MAX_X; // смещение X
    ScaleX = (double)width / MAX_X; // масштабный коэффициент X
    // Область допустимых значений Y
    min = x[1][0];
    max = x[1][0];
    for (int i = 0; i<n; i++)
    {
        for (int j = 1; j <= numrow; j++)
        {
            if (x[j][i] < min) min = x[j][i];
            if (x[j][i] > max) max = x[j][i];
        }
    }

    MAX_Y = max - min;
    OffsetY = max*height / (MAX_Y); // смещение Y
    ScaleY = (double)height / MAX_Y; // масштабный коэффициент Y
    // Отрисовка осей координат
    hpen = CreatePen(PS_SOLID, 0, 0); // черное перо 1px
    SelectObject(hdc, hpen);
    MoveToEx(hdc, 0, OffsetY, 0); // перемещение в точку (0;OffsetY)
    LineTo(hdc, width, OffsetY); // рисование горизонтальной оси
    MoveToEx(hdc, OffsetX, 0, 0); // перемещение в точку (OffsetX;0)
    LineTo(hdc, OffsetX, height); // рисование вертикальной оси (не видна)
    DeleteObject(hpen); // удаление черного пера
    // Отрисовка графика функции
    int color = 0xFF; // красное перо для первого ряда данных
    for (int j = 1; j <= numrow; j++)
    {
        hpen = CreatePen(PS_SOLID, 2, color); // формирование пера 2px
        SelectObject(hdc, hpen);
        X = (int)(OffsetX + x[0][0] * ScaleX); // начальная точка графика
        Y = (int)(OffsetY - x[j][0] * ScaleY);
        MoveToEx(hdc, X, Y, 0); // перемещение в начальную точку
        for (int i = 0; i<n; i++)
        {
            X = OffsetX + x[0][i] * ScaleX;
            Y = OffsetY - x[j][i] * ScaleY;
            LineTo(hdc, X, Y);
        }
        color = color << 8; // изменение цвета пера для следующего ряда
        DeleteObject(hpen); // удаление текущего пера
    }
}

void RenderGraph(HINSTANCE hInstance,
                 HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow, double ** points){
    HWND hwnd;
    MSG msg;
    WNDCLASS w;
    x = points; // задание исходны данных
    memset(&w, 0, sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    w.hInstance = hInstance;
    w.hbrBackground = CreateSolidBrush(0x00FFFFFF);
    w.lpszClassName = "My Class";
    RegisterClass(&w);
    hwnd = CreateWindow("My Class", "График функции",
                        WS_OVERLAPPEDWINDOW,
                        500, 300, 500, 380, NULL, NULL,
                        hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
// Главная функция
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int choice = 0;
    cout << "Choose mode: solve Equation(0) or solve System of equations(1):" << endl;
    cin >> choice;
    if(choice){
        cout << "Simple Iterations Method was chosen" << endl;
        int choose = 0;
        cout << "Choose equation" << endl;
        cout << "(0) x=sin(y+2)-15 : y=0.5-cos(x-2)" << endl;
        cout << "(1) x=y^2+4 : y = 4 - sqrt(x)" << endl;
        cin >> choose;
        if(choose == 0){
            system("start https://www.desmos.com/calculator/lednbuq8an");
            IterationMethodSystem(1);

        }
        if(choose == 1){
            system("start https://www.desmos.com/calculator/qnsqlnqeqe");
            IterationMethodSystem(2);

        }
    }else{
        cout << "Choose method: Simple Iterations (0) or Chord (1):" << endl;
        cin >> choice;
        if(choice){
            cout << "Chord Method was chosen" << endl;
            int choose = 0;
            cout << "Choose equation" << endl;
            cout << "(0) 2x^3+3x^2+5" << endl;
            cout << "(1) 3cos(x)-4sin(x)" << endl;
            cout << "(2) log(x)+x^2" << endl;
            cin >> choose;
            if(choose == 0){
                system("start https://www.desmos.com/calculator/k6yrm4f8zn");
                ChordMethod(func1);
                IterationMethod(func1);
                //RenderGraph(hInstance, hPrevInstance, lpCmdLine,nCmdShow, renderFunc1(70));
            }
            if(choose == 1){
                system("start https://www.desmos.com/calculator/ffengyvhnw");
                ChordMethod(func2);
                IterationMethod(func2);
               // RenderGraph(hInstance, hPrevInstance, lpCmdLine,nCmdShow, renderFunc2(70));
            }
            if(choose == 2){
                system("start https://www.desmos.com/calculator/xm8qtlhdom");
                ChordMethod(func3);
                IterationMethod(func3);
               // RenderGraph(hInstance, hPrevInstance, lpCmdLine,nCmdShow, renderFunc3(70));
            }
        }else{
            cout << "Simple Iterations Method was chosen" << endl;
            int choose = 0;
            cout << "Choose equation" << endl;
            cout << "(0) 2x^3+3x^2+5" << endl;
            cout << "(1) 3cos(x)-4sin(x)" << endl;
            cout << "(2) sin^2x-0.5" << endl;
            cin >> choose;
            if(choose == 0){
                IterationMethod(func1);
                ChordMethod(func1);
               // RenderGraph(hInstance, hPrevInstance, lpCmdLine,nCmdShow, renderFunc1(70));
            }
            if(choose == 1){
                IterationMethod(func2);
                ChordMethod(func2);
                //RenderGraph(hInstance, hPrevInstance, lpCmdLine,nCmdShow, renderFunc2(70));
            }
            if(choose == 2){
                IterationMethod(func3);
                ChordMethod(func3);
               // RenderGraph(hInstance, hPrevInstance, lpCmdLine,nCmdShow, renderFunc3(70));
            }
        }
    }

    return 0;
}
// Оконная функция
LONG WINAPI WndProc(HWND hwnd, UINT Message,
                    WPARAM wparam, LPARAM lparam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (Message)
    {
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            DrawGraph(hdc, ps.rcPaint, x, NUM); // построение графика
            // Вывод текста y=sin(x)
            SetTextColor(hdc, 0x00FF0000); // синий цвет букв
            TextOut(hdc, 10, 20, "y=sin(x)", 8);
            EndPaint(hwnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, Message, wparam, lparam);
    }
    return 0;
}

//int main() {
//
//}

static double func1(double x) //2x^3+3x^2+5
{
  return 2*pow(x,3)+3*pow(x,2)+5;
}

static double func2(double x) //3cos(x)-4sin(x)
{
    return 3*cos(x)-4*sin(x);
}

static double func3(double x) //sin^2x-0.5
{
    return pow(sin(x),2)-0.5;
}
