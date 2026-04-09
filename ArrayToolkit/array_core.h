#ifndef array_core_h
#define array_core_h


int** transpose_matrix(int** mat, int* row, int* col);  //返回新的矩阵指针（旧的内存记得自己释放）
void array_linear_search(int* arr, int len);
void array_search_ui(int* arr, int len);
void print_array(int* arr, int x);
void matrix_search(int** mat, int row, int col);
void reverse_array(int* arr, int len);
void bubble_sort(int* arr, int len);
void select_Asort(int* arr, int len);
void select_Bsort(int* arr, int len);
void select_sort(int* arr, int len);
void print_matrix(int** mat, int row, int col);
int* matrix_flat(int** mat, int row, int col);
int** matrix_unflat(int* flat, int len,int* row,int* col);
int calculateDeterminant(int** mat, int n,double* result);  //返回函数运行状态，计算结果存储在result中

#endif