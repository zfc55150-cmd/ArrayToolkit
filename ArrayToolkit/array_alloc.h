#ifndef array_alloc_h
#define array_alloc_h

#include <stddef.h>

void** createContiguousArray2D(int row, int col, size_t element_size);
void freeContiguousArray2D(void** mat);
int* get_array(int* len);
int** get_array2D(int row, int col);
double** get_matrix(int row, int col);
double** get_determinant(int* n);

#endif