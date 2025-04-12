#include <string.h>
#include <stdio.h>
#include "statement.h"

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    // example statement: insert 1 cstack foo@bar.com
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        int args_assigned = sscanf(
            input_buffer->buffer, // takes in the string located in the buffer
            "insert %d %s %s", // matches it to this format
            &(statement->row_to_insert.id), // integer after "insert"
            statement->row_to_insert.username, // 2nd token
            statement->row_to_insert.email // 3rd token
        );
        if (args_assigned < 3) {
            return PREPARE_SYNTAX_ERROR;
        }
        return PREPARE_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    
    return PREPARE_UNRECOGNIZED_STATEMENT;
}