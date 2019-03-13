#ifndef SOLVER_H
#define SOLVER_H
#include <cstring>

int identical_row(char arr[9][9], int rowIndex, int collumnIndex);
int identical_collumn(char arr[9][9], int rowIndex, int collumnIndex);
int identical_block(char arr[9][9], int rowIndex, int collumnIndex);
void stepback(char arr[9][9], int &rowIndex, int &collumnIndex);
int solve2(int cell,char arr[9][9], char origin[9][9]);
int solve(char arr[9][9], char ori[9][9]);
void easy(char arr[9][9], char ans[9][9]);
int check(char arr[9][9]);
void middle(char arr[9][9], char ans[9][9]);
void hard(char arr[9][9], char ans[9][9]);

#endif // SOLVER_H
