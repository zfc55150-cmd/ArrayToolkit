#ifndef array_core_h
#define array_core_h

int get_char(char* x);
void get_valid_char(char* x);
int get_int(int* x);
void get_valid_int(int* x);
void get_twochoice(char* x);
char* skip_allspaces(char* x);
void** createContiguousMatrix(int row, int col,size_t element_size);
void freeContiguousMatrix(void** mat);
void transpose_matrix(int** mat, int* row, int* col);
void array_linear_search(int* arr, int len);
void array_search_ui(int* arr, int len);
void print_array(int* arr, int x);
int** get_matrix(int row, int col);
void matrix_search(int** mat, int row, int col);
void reverse_array(int* arr, int len);
void bubble_sort(int* arr, int len);
void select_Asort(int* arr, int len);
void select_Bsort(int* arr, int len);
void select_sort(int* arr, int len);
void print_matrix(int** mat, int row, int col);
int* matrix_flat(int** mat, int row, int col);
int** matrix_unflat(int* flat, int len,int* row,int* col);
double calculateDeterminant(int** mat, int n);

#endif