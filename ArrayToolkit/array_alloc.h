#ifndef array_alloc_h
#define array_alloc_h

#include <stddef.h>

typedef enum {
	Matrix_Input_OK = 0,
	Matrix_InvalidSize,
	Matrix_Alloc_Failed,
	Matrix_Input_EOF,
	Matrix_TooLarge,
	Matrix_Output_NULL,
	Matrix_Input_Empty,
	Matrix_Input_NotEnough,
	Matrix_Input_InvalidData,
	Matrix_Input_TooMany,
	Matrix_Input_NULL,
}MatrixInputStatus;

void** createContiguousArray2D(int row, int col, size_t element_size);
void freeContiguousArray2D(void** mat);
int* get_array(int* len);
int** get_array2D(int row, int col);
double** get_matrix(int row, int col);
double** get_determinant(int* n);

#endif