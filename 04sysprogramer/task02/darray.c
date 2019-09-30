#include "darray.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static const int MIN_CAPACITY = 10;

struct _DArray
{
    void** data;
    int size;
    int capacity;
};

static void darray_expand_capacity(DArray* thiz)
{
    if (thiz->size >= thiz->capacity)
    {
        thiz->capacity = (int)(thiz->capacity * 2);
        thiz->data = realloc(thiz->data, sizeof(void*) * thiz->capacity);
    }
}

static void darray_shrink_capacity(DArray* thiz)
{
    int limitSize = thiz->capacity / 4;
    int shrinkSize = thiz->capacity / 2;
    if (thiz->size <= limitSize && thiz->capacity > MIN_CAPACITY)
    {   
        if (shrinkSize < MIN_CAPACITY)
        {
            shrinkSize = MIN_CAPACITY;
        }

        thiz->capacity = shrinkSize;
        thiz->data = realloc(thiz->data, sizeof(void*) * thiz->capacity);
    }

    assert(thiz->capacity >= MIN_CAPACITY);
}

DArray* darray_create()
{
    DArray* thiz = malloc(sizeof(DArray));
    return_val_if_fail(thiz != NULL, NULL);

    thiz->capacity = MIN_CAPACITY;
    thiz->size = 0;
    thiz->data = calloc(1, sizeof(void*) * thiz->capacity); 

    return thiz;
}

RetStatus darray_insert_by_index(DArray* thiz, int index, void* data)
{
    return_val_if_fail(index >= 0 && index <= thiz->size, RET_INVALIDATE_INDEX);

    darray_expand_capacity(thiz);

    void** pCur = thiz->data + thiz->size;
    for (int i = thiz->size; i>index; --i) {
        *pCur = *(pCur - 1);
        --pCur;
    }
    *pCur = data;
    ++thiz->size;

    return RET_OK;
}

RetStatus darray_prepend(DArray* thiz, void* data)
{
    return darray_insert_by_index(thiz, 0, data);
}

RetStatus darray_append(DArray* thiz, void* data)
{
    return darray_insert_by_index(thiz, darray_length(thiz), data);
}


RetStatus darray_delete_data_by_index(DArray* thiz, int index, DArrayFreeDataFunc free_data_func)
{
    return_val_if_fail(index >= 0 && index < thiz->size, RET_INVALIDATE_INDEX);

    void** pCur = thiz->data + index;
    if (free_data_func)
    {
        free_data_func(NULL, *pCur);
    }

    for (int i=index; i<thiz->size-1; ++i)
    {
        *pCur = *(pCur + 1);
        ++pCur;
    }

    --thiz->size;
    darray_shrink_capacity(thiz);

    return RET_OK;
}

RetStatus darray_delete_data_head(DArray* thiz, int index, DArrayFreeDataFunc free_data_func)
{
    return darray_delete_data_by_index(thiz, 0, free_data_func);
}

RetStatus darray_delete_data_tail(DArray* thiz, int index, DArrayFreeDataFunc free_data_func)
{
    return darray_delete_data_by_index(thiz, darray_length(thiz) - 1, free_data_func);
}

void* darray_get_data_by_index(DArray* thiz, int index)
{
    return *(thiz->data + index);
}

void* darray_get_data_head(DArray* thiz)
{
    return darray_get_data_by_index(thiz, 0);
}

void* darray_get_data_tail(DArray* thiz)
{
    return darray_get_data_by_index(thiz, darray_length(thiz) - 1);
}

int darray_length(DArray* thiz)
{
    return thiz->size;
}

void darray_foreach(DArray* thiz, DArrayForeachFunc foreachFunc, void* ctx)
{
    void** pCur = thiz->data;

    for (int i = 0; i < thiz->size; i++)
    {
        foreachFunc(ctx, *pCur);
        ++pCur;
    }
}

int darray_find(DArray* thiz, DArrayDataCompareFunc cmp, void* ctx)
{
    void** pCur = thiz->data;

    for (int i = 0; i < thiz->size; i++)
    {
        if (cmp(ctx, *pCur) == 0)
            return i;
        ++pCur;
    }

    return -1;
}

RetStatus darray_destroy(DArray* thiz, DArrayFreeDataFunc free_data_func)
{
    void** pCur = thiz->data;

    for (int i = 0; i < thiz->size; i++)
    {
        free_data_func(NULL, *pCur);
        ++pCur;
    }

    thiz->size = 0;
    thiz->capacity = MIN_CAPACITY;
    free(thiz->data);
    free(thiz);

    return RET_OK;
}