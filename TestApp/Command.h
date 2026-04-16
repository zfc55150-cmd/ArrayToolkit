#ifndef Command_h
#define Command_h

#include "ArrayToolkit.h"
typedef struct Array1D Array1D;
typedef struct Array2D Array2D;
typedef enum  ArrayType ArrayType;
typedef union  ArrayData ArrayData;
typedef struct Node Node;
typedef struct  SystemState SystemState;
typedef struct Command Command;
typedef struct Menu Menu;
typedef void (*commandfunc)(SystemState* arr);

void print_menu(SystemState* state);
void print_Command(Menu* menu);
void cmd_exit(SystemState* state);

#endif
