#include <stdio.h>
#include "execute.h"

void print_row(Row* row) {
    printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}

ExecuteResult execute_insert(Statement* statement, Table* table) {
    // allows us to read/write from our table structure
    void* node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = *leaf_node_num_cells(node);

    Row* row_to_insert = &(statement->row_to_insert);
    uint32_t key_to_insert = row_to_insert->id;

    Cursor* cursor = table_find(table, key_to_insert);

    if (cursor->cell_num < num_cells) {
        uint32_t key_at_index = *leaf_node_key(node, cursor->cell_num);
        if (key_at_index == key_to_insert) {
            return EXECUTE_DUPLICATE_KEY;
        }
    }

    leaf_node_insert(cursor, row_to_insert->id, row_to_insert);

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
