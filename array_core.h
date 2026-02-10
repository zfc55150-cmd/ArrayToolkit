#ifndef array_core_h
#define array_core_h

#define MAX_N 500
#define MAX_M 50

void get_char(char* x);
void get_int(int* x);
void get_twochoice(char* x);
char* skip_allspaces(char* x);
void transpose_matrix(int (*mat)[MAX_M], int* row, int* col);
void array_linear_search(int* arr, int len);
void array_search_ui(int* arr, int len);
void print_array(int* arr, int x);
void matrix_search(int (*mat)[MAX_M], int row, int col);
void reverse_array(int* arr, int len);
void bubble_sort(int* arr, int len);
void select_Asort(int* arr, int len);
void select_Bsort(int* arr, int len);
void select_sort(int* arr, int len);
void get_A_matrix(int (*arr)[MAX_M], int* row, int* col);
void print_matrix(int (*arr)[MAX_M], int row, int col);
void get_B_matrix(int (*mat)[MAX_M], int* row, int* col);
void get_matrix(int (*mat)[MAX_M], int* row, int* col);
void matrix_flat(int (*mat)[MAX_M], int row, int col, int* flat);
void matrix_unflat(int (*mat)[MAX_M], int* flat, int len,int* row,int* col);

#endif