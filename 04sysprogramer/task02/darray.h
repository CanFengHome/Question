#ifndef DARRAY_H_
#define DARRAY_H_

#include "common.h"

struct _DArray;
typedef struct _DArray DArray;

typedef void (*DArrayFreeDataFunc)(void* ctx, void* data);
typedef void (*DArrayForeachFunc)(void* ctx, void* data);
typedef int (*DArrayDataCompareFunc)(void* ctx, void* data);

DArray* darray_create();

RetStatus darray_insert_by_index(DArray* thiz, int index, void* data);
RetStatus darray_prepend(DArray* thiz, void* data);
RetStatus darray_append(DArray* thiz, void* data);

RetStatus darray_delete_data_by_index(DArray* thiz, int index, DArrayFreeDataFunc free_data_func);
RetStatus darray_delete_data_head(DArray* thiz, int index, DArrayFreeDataFunc free_data_func);
RetStatus darray_delete_data_tail(DArray* thiz, int index, DArrayFreeDataFunc free_data_func);

void* darray_get_data_by_index(DArray* thiz, int index);
void* darray_get_data_head(DArray* thiz);
void* darray_get_data_tail(DArray* thiz);

int darray_length(DArray* thiz);

void darray_foreach(DArray* thiz, DArrayForeachFunc foreachFunc, void* ctx);
int darray_find(DArray* thiz, DArrayDataCompareFunc cmp, void* ctx);

RetStatus darray_destroy(DArray* thiz, DArrayFreeDataFunc free_data_func);

#endif