#ifndef get_h
#define get_h

#include "status.h"

char* skip_midspaces(char* x);
char* skip_allspaces(char* x);
int get_int(int* a);
void get_valid_int(int* x);
int get_char(char* x);
void get_valid_char(char* x);
void get_shape_dimensions(int ndim, int* shape);
void get_twochoice(char* x);
void get_array2D_dimensions(int* row, int* col);
ATKStatus get_string(char** out_put);

#endif

