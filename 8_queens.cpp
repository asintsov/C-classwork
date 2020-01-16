#include <stdio.h>

#define LINES 8
#define COLUMNS 8
#define QUEEN 1
#define EMPTY_CELL 0
#define CELL_UNDER_ATTACK 0
#define CELL_READY_FOR_QUEEN 1
#define QUEEN_IS_IN_LINE 1
#define QUEEN_IS_NOT_IN_LINE 0

void print(int(*chessboard)[COLUMNS], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%2d ", chessboard[i][j]);

        puts("");
    }
    puts("");
}

int check_position(int (*chessboard)[COLUMNS], int lines, int columns, int i_now, int j_now)
{
    int i = i_now;
    int j = j_now;
    int step = 1;
    int result = CELL_READY_FOR_QUEEN;

    while (i_now-step >= 0)
    {
        if (chessboard[i - step][j_now] == QUEEN)
        {
            result = CELL_UNDER_ATTACK;
            break;
        }
        else if (j_now - step >= 0 && chessboard[i - step][j_now - step] == QUEEN)
        {
            result = CELL_UNDER_ATTACK;
            break;
        }
        else if (j_now + step < columns && chessboard[i - step][j_now + step] == QUEEN)
        {
            result = CELL_UNDER_ATTACK;
            break;
        }
        else
            step++;
    }
    return result;
}

int find_queen(int(*chessboard)[COLUMNS], int columns, int i_now)
{
    for (int j = 0; j < columns; j++)
        if (chessboard[i_now][j] == QUEEN)
        {
            return j;
            break;
        }
}

void queen_in_line(int(*chessboard)[COLUMNS], int lines, int columns, int n, int j, int count)
{
    if (n == lines)
    {
        print(chessboard, lines, columns);
        count++;
    }
    while (j < columns)
    {
        if (check_position(chessboard, lines, columns, n, j) == CELL_READY_FOR_QUEEN)
        {
            chessboard[n][j] = QUEEN;
            break;
        }
        else
        {
            j++;
        }
    }
    if (n == 0 && chessboard[0][0] == QUEEN && count != 0)
    {
        printf("Number of variants is %d\n", count);
    }
    else if (j == columns && chessboard[n][columns - 1] != QUEEN)
    {
        n--;
        j = find_queen(chessboard, columns, n) + 1;
        chessboard[n][find_queen(chessboard, columns, n)] = EMPTY_CELL;
        queen_in_line(chessboard, lines, columns, n, j, count);
    }
    else
    {
        n++;
        j = 0;
        queen_in_line(chessboard, lines, columns, n, j, count);
    }
}


int main()
{
    int q = QUEEN;
    int e = EMPTY_CELL;

    int chessboard[LINES][COLUMNS] = { e, e, e, e, e, e, e, e,
                                       e, e, e, e, e, e, e, e,
                                       e, e, e, e, e, e, e, e,
                                       e, e, e, e, e, e, e, e, 
                                       e, e, e, e, e, e, e, e, 
                                       e, e, e, e, e, e, e, e, 
                                       e, e, e, e, e, e, e, e, 
                                       e, e, e, e, e, e, e, e, };

    queen_in_line(chessboard, LINES, COLUMNS, 0, 0, 0);

    return 0;
}