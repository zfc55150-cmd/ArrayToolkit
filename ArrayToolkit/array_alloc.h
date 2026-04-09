#ifndef array_alloc_h
#define array_alloc_h

void** createContiguousMatrix(int row, int col,size_t element_size);
void freeContiguousMatrix(void** mat);
int* get_array(int* len);
int** get_A_matrix(int row, int col);
int** get_B_matrix(int row, int col);
int** get_matrix(int row, int col);
int** get_Determinant(int* n);

#endif