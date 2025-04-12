#pragma once
#include <stdint.h>
#include "common.h"
#include "statement.h"
#include "cursor.h"

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)
#define TABLE_MAX_PAGES 100

extern const uint32_t ID_SIZE;
extern const uint32_t USERNAME_SIZE;
extern const uint32_t EMAIL_SIZE;
extern const uint32_t ID_OFFSET;
extern const uint32_t USERNAME_OFFSET;
extern const uint32_t EMAIL_OFFSET;
extern const uint32_t ROW_SIZE;
extern const uint32_t PAGE_SIZE;
extern const uint32_t ROWS_PER_PAGE;
extern const uint32_t TABLE_MAX_ROWS;

typedef struct {
    int file_descriptor;
    uint32_t file_length;
    void* pages[TABLE_MAX_PAGES];
} Pager;

typedef struct Table {
    Pager* pager;
    uint32_t num_rows;
} Table;

Pager* pager_open(const char* filename);
void pager_flush(Pager* pager, uint32_t page_num, uint32_t size);
Table* db_open(const char* filename);
void db_close(Table* table);
void* get_page(Pager* pager, uint32_t page_num);
void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);