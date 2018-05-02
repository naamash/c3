#ifndef MATALAC_H_INCLUDED
#define MATALAC_H_INCLUDED

#include "matala3.c"

void PrintMatrix(char matrix[MATRIX_ROW][MATRIX_COL]);
bool winSlant2(char matrix[MATRIX_ROW][MATRIX_COL],int row,int col);
bool winSlant(char matrix[MATRIX_ROW][MATRIX_COL],int row,int col);
bool winCol(char matrix[MATRIX_ROW][MATRIX_COL],int row,int col);
bool winRow(char matrix[MATRIX_ROW][MATRIX_COL],int row,int col);
int checkelet(char kelet[1100]);
void checkelet2(char kelet[1100]);
void changeMatrix (char matrix[MATRIX_ROW][MATRIX_COL],int col);
void PlayPlayer (char matrix[MATRIX_ROW][MATRIX_COL]);
void Game (char matrix[MATRIX_ROW][MATRIX_COL]);

#endif