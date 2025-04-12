#include <stdio.h>
#include "execute.h"
#include "table.h"
#include "cursor.h"

void print_row(Row* row) {
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

ExecuteResult execute_insert(Statement* statement, Table* table) {
    // allows us to read/write from our table structure
    if (table->num_rows >= TABLE_MAX_ROWS) {
        return EXECUTE_TABLE_FULL;
    }

    Row* row_to_insert = &(statement->row_to_insert);
    Cursor* cursor = table_end(table);
    serialize_row(row_to_insert, cursor_value(cursor));
    table->num_rows++;

    free(cursor);
    
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement* statement, Table* table) {
    // when selecting all rows in a table, we open a cursor at the start of the table, print a row, then advance the cursor to next row
    // repeat until we reached the end of table
    Cursor* cursor = table_start(table);
    Row row;
    while (!(cursor->end_of_table)){
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
        cursor_advance(cursor);
    }
    free(cursor);
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement* statement, Table* table) {
    switch (statement->type) {
        case STATEMENT_INSERT:
            return execute_insert(statement, table);
        case STATEMENT_SELECT:
            return execute_select(statement, table);
    }
}
