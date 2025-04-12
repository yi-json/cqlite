#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "table.h"

typedef struct Table Table;

typedef struct {
    struct Table* table;
    uint32_t row_num;
    bool end_of_table;
} Cursor;

Cursor* table_start(Table* table);
Cursor* table_end(Table* table);
void* cursor_value(Cursor* cursor);
void cursor_advance(Cursor* cursor);