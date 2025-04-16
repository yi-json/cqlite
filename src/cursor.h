#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "table.h"
#include "node.h"

const uint32_t LEAF_NODE_RIGHT_SPLIT_COUNT = (LEAF_NODE_MAX_CELLS + 1) / 2;
const uint32_t LEAF_NODE_LEFT_SPLIT_COUNT =
    (LEAF_NODE_MAX_CELLS + 1) - LEAF_NODE_RIGHT_SPLIT_COUNT;

typedef struct Table Table;

typedef struct {
    struct Table* table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table;
} Cursor;

Cursor* table_start(Table* table);
Cursor* table_find(Table* table, uint32_t key);
void* cursor_value(Cursor* cursor);
void cursor_advance(Cursor* cursor);
void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value);
Cursor* leaf_node_find(Table* table, uint32_t page_num, uint32_t key);
void leaf_node_split_and_insert(Cursor* cursor, uint32_t key, Row* value);