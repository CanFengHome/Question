#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "darray.h"

void test_darray_insert_by_index();
void test_darray_prepend();
void test_darray_append();

void test_darray_get_data_by_index();

void test_darray_delete_data_by_index();

void test_darray_foreach();
void test_darray_find();

int main()
{
    test_darray_insert_by_index();
    test_darray_prepend();
    test_darray_append();
    test_darray_get_data_by_index();
    test_darray_delete_data_by_index();
    test_darray_foreach();
    test_darray_find();

    puts("=== all over. ===");

    return 0;
}

static void free_int(void* ctx, void* data)
{
    if (data != NULL)
        free(data);
}

void test_darray_insert_by_index()
{
    DArray* ls = darray_create();
    assert(ls != NULL);

    // insert index:0
    int* pVal = malloc(sizeof(int));
    *pVal = 0;
    RetStatus ret = darray_insert_by_index(ls, 0, pVal);
    assert(ret == RET_OK);

    // insert index:len
    int len = darray_length(ls);
    assert(len == 1);
    pVal = malloc(sizeof(int));
    *pVal = 1;
    ret = darray_insert_by_index(ls, len, pVal);
    assert(ret == RET_OK);

    // insert index -1
    len = darray_length(ls);
    assert(len == 2);
    ret = darray_insert_by_index(ls, -1, pVal);
    assert(ret == RET_INVALIDATE_INDEX);
    assert(darray_length(ls) == len);

    // insert index size
    len = darray_length(ls);
    assert(len == 2);
    ret = darray_insert_by_index(ls, len+1, pVal);
    assert(ret == RET_INVALIDATE_INDEX);
    assert(darray_length(ls) == len);

    ret = darray_destroy(ls, free_int);
    assert(ret == RET_OK);
}

void test_darray_prepend()
{
    DArray* ls = darray_create();
    assert(ls != NULL);

    int* pVal = malloc(sizeof(int));
    *pVal = 0;

    RetStatus ret = darray_prepend(ls, pVal);
    assert(ret == RET_OK);
    assert(darray_length(ls) == 1);

    pVal = malloc(sizeof(int));
    *pVal = 1;
    ret = darray_prepend(ls, pVal);
    assert(ret == RET_OK);
    assert(darray_length(ls) == 2);

    assert(darray_get_data_head(ls) == pVal);

    ret = darray_destroy(ls, free_int);
    assert(ret == RET_OK);
}

void test_darray_append()
{
    DArray* ls = darray_create();
    assert(ls != NULL);

    int* pVal = malloc(sizeof(int));
    *pVal = 0;

    RetStatus ret = darray_append(ls, pVal);
    assert(ret == RET_OK);
    assert(darray_length(ls) == 1);

    pVal = malloc(sizeof(int));
    *pVal = 1;
    ret = darray_append(ls, pVal);
    assert(ret == RET_OK);
    assert(darray_length(ls) == 2);

    assert(darray_get_data_tail(ls) == pVal);

    ret = darray_destroy(ls, free_int);
    assert(ret == RET_OK);
}

void test_darray_get_data_by_index()
{
    DArray* ls = darray_create();
    assert(ls != NULL);

    int* pVal0 = malloc(sizeof(int));
    *pVal0 = 0;
    darray_append(ls, pVal0);

    int* pVal1 = malloc(sizeof(int));
    *pVal1 = 1;
    darray_append(ls, pVal1);

    assert(darray_get_data_by_index(ls, 0) == pVal0);
    assert(darray_get_data_by_index(ls, 1) == pVal1);
    assert(darray_get_data_by_index(ls, -1) == NULL);
    assert(darray_get_data_by_index(ls, darray_length(ls)) == NULL);

    RetStatus ret = darray_destroy(ls, free_int);
    assert(ret == RET_OK);
}

void test_darray_delete_data_by_index()
{
    DArray* ls = darray_create();
    assert(ls != NULL);

    const int test_len = 5;

    for (int i=0; i<test_len; ++i)
    {
        int* pVal = malloc(sizeof(int));
        *pVal = i;
        darray_append(ls, pVal);
    }

    assert(darray_length(ls) == test_len);

    const int index = test_len / 2;
    RetStatus ret = darray_delete_data_by_index(ls, index, free_int);
    assert(ret == RET_OK);
    void* curData = darray_get_data_by_index(ls, index);
    int* pNowVal = (int*)(curData);
    assert(*pNowVal == (index+1));

    ret = darray_delete_data_by_index(ls, -1, NULL);
    assert(ret == RET_INVALIDATE_INDEX);

    ret = darray_delete_data_by_index(ls, darray_length(ls), NULL);
    assert(ret == RET_INVALIDATE_INDEX);

    ret = darray_destroy(ls, free_int);
    assert(ret == RET_OK);
}


void test_cal_num(void* ctx, void* data)
{
    int* pRet = (int*)ctx;
    int* pNum = (int*)data;
    *pRet += *pNum;
}

void test_darray_foreach()
{
    DArray* ls = darray_create();
    assert(ls != NULL);

    const int test_len = 5;
    int total = 0;

    for (int i=0; i<test_len; ++i)
    {
        int* pVal = malloc(sizeof(int));
        *pVal = i;
        darray_append(ls, pVal);

        total += i;
    }

    int target = 0;
    darray_foreach(ls, test_cal_num, &target);
    assert(target == total);

    RetStatus ret = darray_destroy(ls, free_int);
    assert(ret == RET_OK);
}

int compare_func(void* ctx, void* data)
{
    int* pTarget = (int*)ctx;
    int* pCur = (int*)data;

    if (*pTarget == *pCur)
    {
        return 0;
    }
    else if (*pTarget > *pCur)
    {
        return 1;
    }
    else
    {
        return -1;
    }
    
}

void test_darray_find()
{
    DArray* ls = darray_create();
    assert(ls != NULL);

    const int test_len = 5;

    for (int i=0; i<test_len; ++i)
    {
        int* pVal = malloc(sizeof(int));
        *pVal = i;
        darray_append(ls, pVal);
    }

    int target = test_len / 2;
    int index = darray_find(ls, compare_func, &target);
    assert(index == target);

    RetStatus ret = darray_destroy(ls, free_int);
    assert(ret == RET_OK);
}