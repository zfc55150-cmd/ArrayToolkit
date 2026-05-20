#ifndef Status_h
#define Status_h

typedef enum {
	Funk_Op_OK = 0,
	Funk_Param_Err,

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
	Matrix_Singular,

	Array_Input_NULL,
	Arrray_InvalidSize,
	
}ATKStatus;

#endif
