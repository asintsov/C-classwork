#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define N 10
#define M 10
#define SIZE_NUMB 99

void generate(int (*arr)[M],int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            arr[i][j] = rand() % SIZE_NUMB+1;
        }
    }
}

void print(int (*arr)[M], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%02d ", arr[i][j]);
        }
        puts("");
    }
}

void sum_matrix(int(*arr0)[M], int(*arr_sum)[M], int n, int m)
{

for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            arr_sum[i][j] = arr0[i][j];
        }
    }  

    for (int j = 1; j < m; j++)
        arr_sum[0][j] += arr_sum[0][j - 1];

    for (int i = 1; i < n; i++)
        arr_sum[i][0] += arr_sum[i-1][0];

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            if (arr_sum[i-1][j]>arr_sum[i][j-1])
                arr_sum[i][j]+= arr_sum[i - 1][j];
            else
                arr_sum[i][j] += arr_sum[i ][j-1];
        }
    }   
}

void way_matrix(int(*way)[M], int(*arr_sum)[M], int n, int m)
{
    int i = n-1;
    int j = m-1;

    way[0][0] = 1;
    way[n - 1][m - 1] = 1;

    while (i!=0 || j!=0)
    {
        if (i > 0 && j > 0)
        {
            if (arr_sum[i - 1][j] > arr_sum[i][j - 1])
            {
                way[i - 1][j] = 1;
                i--;
            }
            else
            {
                way[i][j - 1] = 1;
                j--;
            }
        }
        else if (i == 0 && j > 0)
        {
            if (arr_sum[i][j] > arr_sum[i][j - 1])
                way[i][j - 1] = 1;
            j--;
        }
        else if (i > 0 && j == 0)
        {
            if (arr_sum[i][j] > arr_sum[i - 1][j])
                way[i - 1][j] = 1;
            i--;
        }
        else
            break;
    }   
}
void print_way(int(*arr0)[M], int(*way)[M], int n, int m)
{
    HANDLE hstdout;
    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (way[i][j] == 1)
            {
                SetConsoleTextAttribute(hstdout, 0x70);
                printf("%02d ", arr0[i][j]);
                SetConsoleTextAttribute(hstdout, 0x07);
            }
            else
            {
                SetConsoleTextAttribute(hstdout, 0x07);
                printf("%02d ", arr0[i][j]);
            }
            
        }
        puts("");
    }
}



int main()
{
    int arr0[N][M] = { 0 };
    int arr_sum[N][M] = { 0 };
    int way[N][M] = { 0 };
    

    time_t now;
    time(&now);
    srand(now);
    rand();

    generate(arr0, N, M);
    print(arr0, N, M);

    puts("");

    sum_matrix(arr0, arr_sum, N, M);
    way_matrix(way, arr_sum, N, M);
    print_way(arr0, way, N, M);

}