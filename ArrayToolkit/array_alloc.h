#ifndef array_alloc_h
#define array_alloc_h

int get_int(int *x);
void get_valid_int(int* x);
void** createContiguousMatrix(int row, int col,size_t element_size);
void freeContiguousMatrix(void** mat);
void get_twochoice(char* x);
char* skip_allspaces(char* x);
int* get_array(int* len);
int** get_A_matrix(int row, int col);
int** get_B_matrix(int row, int col);
int** get_matrix(int row, int col);
int** get_Determinant(int* n);

#endif