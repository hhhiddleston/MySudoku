#include "solver.h"
#include "mainwindow.h"
#include <QTime>
#include <QDebug>

int identical_row(char arr[9][9], int rowIndex, int collumnIndex) //判断同一行是否有数字相同
{
    for (int j = 0; j < 9; ++j)
        if (arr[rowIndex][collumnIndex] == arr[rowIndex][j] && collumnIndex != j && arr[rowIndex][collumnIndex]!='0')
            return 1;//有数字相同就返回1
    return 0;
}
int identical_collumn(char arr[9][9], int rowIndex, int collumnIndex) //判断同一列是否有数字相同
{
    for (int i = 0; i < 9; ++i)
        if (arr[rowIndex][collumnIndex] == arr[i][collumnIndex] && rowIndex != i && arr[rowIndex][collumnIndex]!='0')
            return 1;//有数字相同就返回1
    return 0;
}
int identical_block(char arr[9][9], int rowIndex, int collumnIndex)//判断同一宫是否有数字相同
{
    for (int i = 0; i < 9; i += 3)
        for (int j = 0; j < 9; j += 3)
        {
            for (int ii = i; ii < i + 3; ++ii)
                for (int jj = j; jj < j + 3; ++jj)
                {
                    if (ii == rowIndex && jj == collumnIndex)
                    {
                        for (ii = i; ii < i + 3; ++ii)
                            for (jj = j; jj < j + 3; ++jj)
                                if (arr[ii][jj] == arr[rowIndex][collumnIndex] && ii != rowIndex && jj != collumnIndex && arr[rowIndex][collumnIndex]!='0')
                                    return 1;
                        return 0;
                    }
                }
        }
    return 0;
}


void stepback(char arr[9][9], int &rowIndex, int &collumnIndex)
{
    for (int i = rowIndex; i>-1; --i)
        for (int j = 8; j>-1; --j)
            if (arr[i][j] == '0' && (i != rowIndex || (i == rowIndex && j < collumnIndex)))
            {
                rowIndex = i;
                collumnIndex = j;
                return;
            }
}

int solve(char arr[9][9],char ori[9][9])
{
    char outter[9][9];
    memcpy(outter, arr, sizeof(char) * 9 * 9);
    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
            if (identical_row(outter, i, j) + identical_collumn(outter, i, j) + identical_block(outter, i, j) != 0)
                return 0;

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
        {
            if (outter[i][j] == '0')
            {
                do
                {
                    while (1)
                    {
                        ++outter[i][j];
                        //count++;//************************************记录循环次数
                        if (outter[i][j] > '9')
                        {
                            outter[i][j] = '0';
                            stepback(arr, i, j);
                        }
                        else break;
                    }
                } while (identical_row(outter, i, j) + identical_collumn(outter, i, j) + identical_block(outter, i, j) != 0);
            }
        }
    memcpy(ori, outter, sizeof(char) * 9 * 9);
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if(outter[i][i]=='0') return 0; //无解
    return 1; //有解
}


int solve2(int cell, char arr[9][9], char origin[9][9]) {
    static int flag;
    if (cell == 0) flag = 0;

    char sudoku[9][9];
    memcpy(sudoku, arr, sizeof(char) * 9 * 9);

    for (int i=0;i<9;++i)
        for(int j=0;j<9;++j)
            if (identical_row(sudoku, i, j) + identical_collumn(sudoku, i, j) + identical_block(sudoku, i, j) != 0)
                return 0;

    while (sudoku[cell/9][cell%9] != '0' && cell != 81 ) cell++;

    int row = cell / 9;
    int col = cell % 9;
    if (row == 9) {
        if (flag == 0) { flag = 1; memcpy(origin, sudoku, sizeof(char) * 9 * 9); return 1;}
        else { flag = 2; return 2;}
    }


    for (int i = '1'; i <= '9'; ++i) {
        sudoku[row][col] = i;
        if (identical_row(sudoku, row, col) + identical_collumn(sudoku, row, col) + identical_block(sudoku, row, col) == 0) { // yes
            if (solve2(cell+1,sudoku, origin) == 2) return 2; // next cell
        }
    }
    return flag;
}

void easy(char arr[9][9], char ans[9][9]){
    int max,i,j,k;
    char working[9][9];
    char temp[9][9];
    qsrand(time(NULL));
    memcpy(working, arr, sizeof(char) * 9 * 9);
    max=10;
    i=qrand()%9;
    j=qrand()%9;
    working[i][j]='1';
        solve(working, ans);//随机放一个1，生成一个数独workingArr
        memcpy(working, ans, sizeof(char) * 9 * 9);

            for(k=0;k<max;k++)
            {
                i=qrand()%9;
                j=qrand()%9;
                working[i][j]='0';
                memcpy(temp, working, sizeof(char) * 9 * 9);
                if(solve2(0,working, ans)==1)
                    continue;
                else
                {
                    memcpy(working, temp, sizeof(char) * 9 * 9);
                    max=max+1;
                    qDebug("1");
                }
            }

        memcpy(arr, working, sizeof(char) * 9 * 9);

}

void middle(char arr[9][9], char ans[9][9]){
    int max,i,j,k;
    char working[9][9];
    char temp[9][9]; //*********修改
    qsrand(time(NULL));
    memcpy(working, arr, sizeof(char) * 9 * 9);
    max=25;
    i=qrand()%9;
    j=qrand()%9;
    working[i][j]='1';
        solve(working, ans);//随机放一个1，生成一个数独workingArr
        memcpy(working, ans, sizeof(char) * 9 * 9);
        //memcpy(temp, ans, sizeof(char) * 9 * 9);//******************修改
            for(k=0;k<max;k++)
            {
                i=qrand()%9;
                j=qrand()%9;
                working[i][j]='0';
                memcpy(temp, working, sizeof(char) * 9 * 9);//****************************
                if(solve2(0,working, ans)==1)
                    continue;
                else
                {   memcpy(working, temp, sizeof(char) * 9 * 9);
                    max=max+1;
                    qDebug("1");
                }//*********************
            }
            //qDebug("1");
        memcpy(arr, working, sizeof(char) * 9 * 9);
        //qDebug("2");
}
void hard(char arr[9][9], char ans[9][9]){
    int max,i,j,k;
    char working[9][9];
    //char temp[9][9]; //*********修改
    qsrand(time(NULL));
    memcpy(working, arr, sizeof(char) * 9 * 9);
    max=60;
    i=qrand()%9;
    j=qrand()%9;
    working[i][j]='1';
        solve(working, ans);//随机放一个1，生成一个数独workingArr
        memcpy(working, ans, sizeof(char) * 9 * 9);
            for(k=0;k<max;k++)
            {
                i=qrand()%9;
                j=qrand()%9;
                working[i][j]='0';
                /*memcpy(temp, working, sizeof(char) * 9 * 9);
                if(solve2(0,working, ans)==1)
                    continue;
                else
                {
                    memcpy(working, temp, sizeof(char) * 9 * 9);
                    max=max+1;}*/

            }
            //qDebug("1");
        memcpy(arr, working, sizeof(char) * 9 * 9);
        //qDebug("2");
}

