#pragma once
#include "input_buffer.h"
#include "table.h"
#include "node.h"

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

void print_constants();
void print_leaf_node(void* node);
MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table);