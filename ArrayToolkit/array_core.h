#ifndef array_core_h
#define array_core_h

#include <stdbool.h>
#include "status.h"


double** transpose_matrix(double** mat, int* row, int* col);  //返回新的矩阵指针（旧的内存记得自己释放）
void array_linear_search(int* arr, int len);
void array_search_ui(int* arr, int len);
void print_array(int* arr, int x);
void matrix_search(int** mat, int row, int col);
void reverse_array(int* arr, int len);
ATKStatus bubble_sort(int* arr, int len,char* if_ascending);
void select_Asort(int* arr, int len);
void select_Bsort(int* arr, int len);
void select_sort(int* arr, int len);
void print_array2D(int** mat, int row, int col);
int* array2D_flat(int** mat, int row, int col);
int** array2D_unflat(int* flat, int len,int* row,int* col);
double** clone_matrix(double** mat, int row, int col);
bool calculate_det(double** mat, int n,double* result);  //返回函数运行状态，计算结果存储在result中
int matrix_rank(double** mat, int row, int col);
ATKStatus matrix_to_rowechelon(double** mat, int row, int col);
ATKStatus matrix_to_rowsimplest(double** mat, int row, int col);
ATKStatus inverse_matrix(double** mat, int n);
void print_matrix(double** mat, int row, int col);

#endif