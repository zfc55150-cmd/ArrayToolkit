#ifndef Command_h
#define Command_h

#include "ArrayToolkit.h"


void print_menu();
int count_array(SystemState* state);
void print_Command(Menu* menu,SystemState* state);
void cmd_exit(SystemState* state);
void cmd_get_array(SystemState* state);
void state_tail_insert(SystemState* state, Node* new_node);
void cmd_get_matrix(SystemState* state);
void cmd_print_array(SystemState* state);

#endif
