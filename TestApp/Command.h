#ifndef Command_h
#define Command_h

#include "ArrayToolkit.h"


void print_menu();
void print_Command(Menu* menu,SystemState* state);
bool always_available(const SystemState* head);
bool has_array1D(const SystemState* state);
bool has_array2D(const SystemState* state);
bool has_matrix(const SystemState* state);
void cmd_exit(SystemState* state);
void cmd_get_array(SystemState* state);
void state_tail_insert(SystemState* state, Node* new_node);
void cmd_get_array2D(SystemState* state);
void cmd_print_array(SystemState* state);
void cmd_get_matrix(SystemState* state);
void cmd_print_array2D(SystemState* state);
void cmd_calculate_det(SystemState* state);
void cmd_matrix_transpose(SystemState* state);
void cmd_print_matrix(SystemState* state);

#endif
