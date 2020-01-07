#include <stdio.h>
#include <Windows.h>

#define LINES 10
#define COLUMNS 10

#define EMPTY_CELL '+'
#define POINT_A 'A'
#define POINT_B 'B'
#define BUILDING_CELL 'O'
#define STEP -4

void print(char(*room)[COLUMNS], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%c ", room[i][j]);
        }
        puts("");
    }
}

void print_2(int(*way)[COLUMNS], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%2d ", way[i][j]);
        }
        puts("");
    }
}

void copy_room(char(*room)[COLUMNS], int(*way)[COLUMNS], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (room[i][j]== EMPTY_CELL)
                way[i][j] = 0;
            else if (room[i][j] == POINT_A)
                way[i][j] = -1;
            else if (room[i][j] == POINT_B)
                way[i][j] = -2;
            else
                way[i][j] = -3;
        }
    }
}

void single_wave(int(*way)[COLUMNS], int n, int m, int i, int j, int count)
{
        if ((way[i][j + 1] == 0) && (j+1 < m))
            way[i][j + 1] = count + 1;
        if ((way[i + 1][j] == 0) && (i+1 < n))
            way[i + 1][j] = count + 1;
        if ((way[i - 1][j] == 0) && (i-1 >= 0))
            way[i - 1][j] = count + 1;
        if ((way[i][j - 1] == 0) && (j-1 >= 0))
            way[i][j - 1] = count + 1;
}



void waves(int(*way)[COLUMNS], int n, int m, int cord1, int cord2)
{
    int count = 0;
    
    single_wave(way, n, m, cord1, cord2,count);

    count++;
   
    while (count<n+m)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (way[i][j]==count) single_wave(way, n, m, i, j, count);
            }
        }
        count++;
    }
}

void steps_on_way(int(*way)[COLUMNS], int n, int m, int cord_A_1, int cord_A_2, int cord_B_1, int cord_B_2)
{
    int i = cord_B_1;
    int j = cord_B_2;
    int min_horisontal = 0;
    int min_vertical = 0;
    int min_common = 0;

    while (1)
    {      
            if (way[i][j - 1] < 0 && way[i][j + 1] < 0)
                min_horisontal = LINES + COLUMNS;
            else if (way[i][j + 1] < 0 || j >= COLUMNS)
                min_horisontal = way[i][j - 1];
            else if (way[i][j - 1] < 0 || j < 0)
                min_horisontal = way[i][j + 1];
            else if (way[i][j - 1] <= way[i][j + 1])
                min_horisontal = way[i][j - 1];
            else
                min_horisontal = way[i][j + 1];

            if (way[i - 1][j] < 0 && way[i + 1][j] < 0)
                min_vertical = LINES + COLUMNS;
            else if (way[i + 1][j] < 0 || i >= LINES)
                min_vertical = way[i - 1][j];
            else if (way[i - 1][j] < 0 || i < 0)
                min_vertical = way[i + 1][j];
            else if (way[i - 1][j] <= way[i + 1][j])
                min_vertical = way[i - 1][j];
            else
                min_vertical = way[i + 1][j];

            if (min_horisontal <= min_vertical)
                min_common = min_horisontal;
            else
                min_common = min_vertical;

            if (min_common == way[i][j - 1])
            {
                if (way[i][j - 1] == 1)
                {
                    way[i][j - 1] = STEP;
                    break;
                }
                else
                {
                    way[i][j - 1] = STEP;
                    j--;
                }
            }
            else if (min_common == way[i][j + 1])
            {
                if (way[i][j + 1] == 1)
                {
                    way[i][j + 1] = STEP;
                    break;
                }
                else
                {
                    way[i][j + 1] = STEP;
                    j++;
                }
            }
            else if (min_common == way[i - 1][j])
            {
                if (way[i - 1][j] == 1)
                {
                    way[i - 1][j] = STEP;
                    break;
                }
                else
                {
                    way[i - 1][j] = STEP;
                    i--;
                }
            }
            else
            {
                if (way[i + 1][j] == 1)
                {
                    way[i + 1][j] = STEP;
                    break;
                }
                else
                {
                    way[i + 1][j] = STEP;
                    i++;
                }
            }
    }
}

void print_way(char(*room)[COLUMNS], int(*way)[COLUMNS], int n, int m)
{
    HANDLE hstdout;
    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (way[i][j] == -1)
                SetConsoleTextAttribute(hstdout, 0x90);
            else if (way[i][j] == -2)
                SetConsoleTextAttribute(hstdout, 0x90);
            else if (way[i][j] == -4)
                SetConsoleTextAttribute(hstdout, 0x70);
            else if (way[i][j] == -3)
                SetConsoleTextAttribute(hstdout, 0x50);
            else
                SetConsoleTextAttribute(hstdout, 0x07);

            printf("%c ", room[i][j]);
        }
        puts("");
    }
}

int main()
{
    char b = BUILDING_CELL;
    char e = EMPTY_CELL;
    char room[LINES][COLUMNS] = {e, e, e, e, e, e, e, b, e, e,
                                 e, e, e, e, e, e, e, b, e, e,
                                 e, e, e, b, b, b, e, e, e, e,
                                 e, e, e, b, e, e, e, e, e, e,
                                 e, e, e, e, e, e, e, b, e, e,
                                 e, e, e, e, e, e, e, b, e, e,
                                 e, e, e, e, b, e, e, b, e, e,
                                 e, e, e, e, b, e, e, e, e, e,
                                 e, e, e, e, b, e, e, e, e, e,
                                 e, e, e, e, b, e, e, e, e, e};

    int way[LINES][COLUMNS] = {0};

    int cord_A_1 = 1;
    int cord_A_2 = 1;
    int cord_B_1 = 4;
    int cord_B_2 = 8;

    room[cord_A_1][cord_A_2] = POINT_A;
    room[cord_B_1][cord_B_2] = POINT_B;

    print(room, LINES, COLUMNS);
    puts("");

    copy_room(room, way, LINES, COLUMNS);

    waves(way, LINES, COLUMNS, 1, 1);

    //print_2(way, LINES, COLUMNS);
    //puts("");

    steps_on_way(way, LINES, COLUMNS, cord_A_1, cord_A_2, cord_B_1, cord_B_2);

    print_way(room,way, LINES, COLUMNS);

    return 0;
}