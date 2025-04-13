#pragma once
#include <stdint.h>
#include "common.h"
#include "statement.h"

#define ID_SIZE sizeof(((Row*)0)->id)
#define USERNAME_SIZE sizeof(((Row*)0)->username)
#define EMAIL_SIZE sizeof(((Row*)0)->email)

#define PAGE_SIZE 4096
#define ROW_SIZE (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)
#define TABLE_MAX_PAGES 100

extern const uint32_t ID_OFFSET;
extern const uint32_t USERNAME_OFFSET;
extern const uint32_t EMAIL_OFFSET;

typedef struct {
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void* pages[TABLE_MAX_PAGES];
} Pager;

typedef struct Table {
    Pager* pager;
    uint32_t root_page_num;
} Table;

Pager* pager_open(const char* filename);
void pager_flush(Pager* pager, uint32_t page_num);
Table* db_open(const char* filename);
void db_close(Table* table);
void* get_page(Pager* pager, uint32_t page_num);
void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);