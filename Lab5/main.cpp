/*
*    Adams-Bashforth four-step explicit Multistep method.
*    RUNGE-KUTTA (ORDER 4) ALGORITHM is used to compute w1
*
*    TO APPROXIMATE THE SOLUTION TO THE INITIAL VALUE PROBLEM:
*               Y' = F(T,Y), A<=T<=B, Y(A) = ALPHA,
*    AT (N+1) EQUALLY SPACED NUMBERS IN THE INTERVAL [A,B].
*
*    INPUT:   ENDPOINTS A,B; INITIAL CONDITION ALPHA; INTEGER N.
*
*    OUTPUT:  APPROXIMATION W TO Y AT THE (N+1) VALUES OF T.
*/

#include<stdio.h>
#include<math.h>
#include<iostream>
#include <windows.h>

#define true 1
#define false 0
#define MAX_N 2000

static   double F(double, double);

using namespace std;
double A,B,ALPHA,H,T,W[MAX_N], K1,K2,K3,K4, INIT_Y, INIT_X, X_DRAW[MAX_N], Y_DRAW[MAX_N];
int I,N;
double **f;
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
        f[0][i] = X_DRAW[i];
        f[1][i] = Y_DRAW[i];
    }
    return f;
}
void Init(){
    A = 0.0;
    B = 2.0;
    N = 10;

    cout << "Set the initial value of Y" << endl;
    cin >> INIT_Y;

    cout << "Set the initial value of X" << endl;
    cin >> INIT_X;

    cout << "Set count of steps" << endl;
    cin >> N;

    cout << "Set the end of interval" << endl;
    cin >> B;

    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(10);

    A = INIT_X;

    /* STEP 1 */
    H = (B - A) / N;
    T = A;
    W[0] = INIT_Y; // initial value
}

void Runge(){
    /* STEP 2 --- Use order 4 RK method to get w1, w2, w3 */
    /// NOTE: The "for" loop starts with I = 1.
    for (I=1; I<=3; I++)
    {
        /* STEP 3 */
        /* Compute K1, K2 RESP. */
        K1 = H*F(T, W[I-1]);
        K2 = H*F(T + H/2.0, W[I-1] + K1/2.0);
        K3 = H*F(T + H/2.0, W[I-1] + K2/2.0);
        K4 = H*F(T + H, W[I-1] + K3);


        /* STEP 4 */
        /* COMPUTE W(I) */
        W[I] = W[I-1] + 1/6.0*(K1 + 2.0*K2 + 2.0*K3 + K4);

        /* COMPUTE T(I) */
        T = A + I * H;
        X_DRAW[I-1] = T;
        Y_DRAW[I-1] = W[I];
        /* STEP 5 */
        cout <<"At time "<< T <<" the solution = "<< W[I] << endl;
    }
}

void Adams(){
    /* STEP 6---Use Adam-Bashforth 4-step explicit method */
    for(I = 4; I <= N; I++)
    {
        K1 = 55.0*F(T, W[I-1]) - 59.0*F(T-H, W[I-2]) + 37.0*F(T-2.0*H, W[I-3]) - 9.0*F(T-3.0*H, W[I-4]);
        W[I] = W[I-1] + H/24.0*K1;
        /* COMPUTE T(I) */
        T = A + I * H;
        X_DRAW[I-1] = T;
        Y_DRAW[I-1] = W[I];
        /* STEP 7 */
        cout <<"At time "<< T <<" the solution = "<< W[I] << endl;
    }

    x = getData(N);
}

/*  Change function F for a new problem   */
double F(double T, double Y)
{
    double f;

    f = Y/(T+1)+T;
   // f = Y - T*T + 1.0;
    //f = (Y - T) / ( Y + T);
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


// Главная функция
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS w;
     // задание исходны данных
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

    Init();
    Runge();
    Adams();
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
    switch (Message)
    {
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            DrawGraph(hdc, ps.rcPaint, x, N); // построение графика
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
