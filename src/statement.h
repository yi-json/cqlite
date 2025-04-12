#pragma once
#include "common.h"
#include "input_buffer.h"

typedef enum { PREPARE_SUCCESS, PREPARE_SYNTAX_ERROR, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);