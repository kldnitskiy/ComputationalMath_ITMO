#include <iostream>
#include <windows.h>
#include <math.h>
using namespace std;


int choice = 0;
bool dot1(double x){
   if(x == 0){
       return true;
   }
    if(x == 1){
        return true;
    }
    if(x == 2){
        return true;
    }
    if(x == 3){
        return true;
    }
    if(x == 4){
        return true;
    }
    return false;
}

bool dot2(double x){
    if(x == 0){
        return true;
    }
    if(x == 0.5){
        return true;
    }
    if(x == 1){
        return true;
    }
    if(x == 1.5){
        return true;
    }
    if(x == 2){
        return true;
    }
    if(x == 2.5){
        return true;
    }
    if(x == 3){
        return true;
    }
    if(x == 3.5){
        return true;
    }
    if(x == 4){
        return true;
    }
    return false;
}

bool dot3(double x){
    if(x == 0){
        return true;
    }
    if(x == 0.5){
        return true;
    }

    if(x == 1.5){
        return true;
    }
    if(x == 2){
        return true;
    }
    if(x == 2.5){
        return true;
    }
    if(x == 3){
        return true;
    }
    if(x == 3.5){
        return true;
    }
    if(x == 4){
        return true;
    }
    return false;
}

bool dot4(double x){
    if(x == 0){
        return true;
    }
    if(x == -1){
        return true;
    }
    if(x == -2){
        return true;
    }
    if(x == -3){
        return true;
    }
    if(x == 4){
        return true;
    }
    if(x == 5){
        return true;
    }
    if(x == 6){
        return true;
    }
    if(x == 7){
        return true;
    }
    return false;
}

double  inter3(int x){
    return ((16*pow(x,7)/5) - (208*pow(x,6)/5)+(216*pow(x,5)) - (568*pow(x,4)) + (3944*pow(x,3)/5) - (2637*pow(x,2)/5) + 126*x);
}
//Seeking interposition quotient
double getCS(int n,double Xs[],double Ys[])
{
    double cs;
    cs = 0;
    double l =1;
    for (int k = 0; k <n; k++) {
        for(int j=0;j<n;j++){
            if(k==j)
            {
                continue;
            }
            l = l*(Xs[k] - Xs[j]);
        }
        cs = cs + Ys[k] / l;
        l = 1;

    }
    return cs;
}
//Seeking continuous multiplication
double getvalue(int n,double x,double Xs[]){
    double l = 1.0;
    for(int i = 0;i<n-1;i++)
    {
        l = l*(x-Xs[i]);
    }
    return l;


}
//Find the result of Newton interpolation
int test()
{
    double x,y;
    y = 0;
    int n;
    cout<<"Please enter the x you want to calculate"<<endl;
    cin>>x;
    cout<<"Please enter how many known points are there"<<endl;
    cin>>n;
    double Xs[n];
    double Ys[n];
    cout<<"Please enter the interpolation points, xy are separated by spaces, no need to add parentheses"<<endl;
    for(int i = 0;i<n;i++)
    {
        //cin>>Xs[i];
        //cin>>Ys[i];
        cin>>Xs[i];
        cin>>Ys[i];
    }
//    for(int i = 0; i<n;i++)
//    {
//        cout << getCS(i+1,Xs,Ys) << " " << getvalue(i+1,x,Xs) << endl;
//        y = y + getCS(i+1,Xs,Ys) * getvalue(i+1,x,Xs);
//    }
    //cout<<"The result is"<<y<<endl;

}


const int NUM = 70; // количество точек
LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
double **x; // массив данных




// Задание исходных данных для графика
double ** getData(int n)
{
    double **f;
    f = new double*[3];
    f[0] = new double[n];
    f[1] = new double[n];
    f[2] = new double[n];
    int sign = -35;
    for (int i = 0; i<n; i++)
    {
        sign++;
        cout << choice << endl;
        if(choice == 3){
            double x = (double)sign * 0.1;
            f[0][i] = x;
            f[1][i] = -3*pow(x,3);
            f[2][i] = ((16*pow(x,7)/5) - (208*pow(x,6)/5)+(216*pow(x,5)) - (568*pow(x,4)) + (3944*pow(x,3)/5) - (2637*pow(x,2)/5) + 126*x);
        }else{
            double x = (double)i * 0.1;
            f[0][i] = x;
            f[1][i] = 3*pow(x,3);
            f[2][i] = 3*pow(x,3) + 40;
        }

        if(choice == 4){
            double x = (double)sign * 0.1;
            f[0][i] = x;
            f[1][i] = -3*pow(x,3);
            f[2][i] = 3*pow(x,3) + 40;
        }
    }
    return f;
}

void getPoints()
{
    double x;
    int n;
    int y = 0;
    cout<<"Please enter the x you want to calculate"<<endl;
    cin>>x;
    cout<<"Please enter how many known points are there"<<endl;
    cin>>n;
    double Xs[n];
    double Ys[n];
    cout<<"Please enter the interpolation points, xy are separated by spaces, no need to add parentheses"<<endl;
    for(int i = 0;i<n;i++)
    {
        cin>>Xs[i];
        cin>>Ys[i];
    }
    for(int i = 0; i<n;i++)
    {
        cout << getCS(i+1,Xs,Ys) << " " << getvalue(i+1,x,Xs) << endl;
        y = y + getCS(i+1,Xs,Ys) * getvalue(i+1,x,Xs);
    }
    cout<<"The result is "<<y<<endl;
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

    MAX_X = max - min;
    if(choice == 3 || choice == 4){
        MAX_X = -7;
    }
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
    numrow = 2;
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
            if(choice == 3 && j == 2 || choice == 4 && j == 2)
                X = OffsetX  - x[0][i] * ScaleX;
            Y = OffsetY - x[j][i] * ScaleY;


            LineTo(hdc, X, Y);
            if(choice == 1){
                if(dot1(x[0][i])){
                    LineTo(hdc, X, Y+4);
                    LineTo(hdc, X, Y-4);
                    LineTo(hdc, X, Y);
                }
            }
            if(choice == 2){
                if(dot2(x[0][i])){
                    LineTo(hdc, X, Y+4);
                    LineTo(hdc, X, Y-4);
                    LineTo(hdc, X, Y);
                }
            }
            if(choice == 3){
                if(dot3(x[0][i])){
                    LineTo(hdc, X, Y+4);
                    LineTo(hdc, X, Y-4);
                    LineTo(hdc, X, Y);
                }
            }
            if(choice == 4){
                if(dot4(x[0][i])){
                    LineTo(hdc, X, Y+4);
                    LineTo(hdc, X, Y-4);
                    LineTo(hdc, X, Y);
                }
                if(dot4(-x[0][i])){
                    LineTo(hdc, X, Y+4);
                    LineTo(hdc, X, Y-4);
                    LineTo(hdc, X, Y);
                }
            }


        }


        color = color << 8; // изменение цвета пера для следующего ряда
        DeleteObject(hpen); // удаление текущего пера
    }
}
// Главная функция
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS w;
    cout << "Enter mode" << endl;
    cin >> choice;
    x = getData(NUM);

   //interpolation1 = getData(NUM);// задание исходны данных
    memset(&w, 0, sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    w.hInstance = hInstance;
    w.hbrBackground = CreateSolidBrush(0x00FFFFFF);
    w.lpszClassName = "My Class";
    RegisterClass(&w);
    hwnd = CreateWindow("My Class", "y=3x^2",
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
    return msg.wParam;
}
// Оконная функция
LONG WINAPI WndProc(HWND hwnd, UINT Message,
                    WPARAM wparam, LPARAM lparam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    //getPoints();
    switch (Message)
    {
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            DrawGraph(hdc, ps.rcPaint, x, NUM); // построение графика
            //DrawGraph(hdc, ps.rcPaint, get, NUM);
            // Вывод текста y=sin(x)
            SetTextColor(hdc, 0x00FF0000); // синий цвет букв
            TextOut(hdc, 10, 20, "y=2cos(2x)", 10);
            EndPaint(hwnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, Message, wparam, lparam);
    }

    getPoints();
    return 0;
}


