#ifndef DLIST_H_
#define DLIST_H_

#include "common.h"

struct _DList;
typedef struct _DList DList;

typedef void (*DListFreeDataFunc)(void* ctx, void* data);


DList* dlist_create();

RetStatus dlist_insert_by_index(DList* thiz, int index, void* data);
int dlist_length(DList* thiz);

RetStatus dlist_destroy(DList* thiz, DListFreeDataFunc free_data_func);

#endif