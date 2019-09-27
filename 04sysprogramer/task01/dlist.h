#ifndef DLIST_H_
#define DLIST_H_

#include "common.h"

struct _DList;
typedef struct _DList DList;

typedef void (*DListFreeDataFunc)(void* ctx, void* data);
typedef void (*DListForeachFunc)(void* ctx, void* data);
typedef int (*DListDataCompareFunc)(void* ctx, void* data);

DList* dlist_create();

RetStatus dlist_insert_by_index(DList* thiz, int index, void* data);
RetStatus dlist_prepend(DList* thiz, void* data);
RetStatus dlist_append(DList* thiz, void* data);

RetStatus dlist_delete_data_by_index(DList* thiz, int index, DListFreeDataFunc free_data_func);
RetStatus dlist_delete_data_head(DList* thiz, int index, DListFreeDataFunc free_data_func);
RetStatus dlist_delete_data_tail(DList* thiz, int index, DListFreeDataFunc free_data_func);

void* dlist_get_data_by_index(DList* thiz, int index);
void* dlist_get_data_head(DList* thiz);
void* dlist_get_data_tail(DList* thiz);

int dlist_length(DList* thiz);

void dlist_foreach(DList* thiz, DListForeachFunc foreachFunc, void* ctx);
int dlist_find(DList* thiz, DListDataCompareFunc cmp, void* ctx);

RetStatus dlist_destroy(DList* thiz, DListFreeDataFunc free_data_func);

#endif