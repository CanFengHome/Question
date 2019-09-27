#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dlist.h"

void test_dlist_insert_by_index();
void test_dlist_prepend();
void test_dlist_append();

void test_dlist_get_data_by_index();

void test_dlist_delete_data_by_index();

void test_dlist_foreach();
void test_dlist_find();

int main()
{
    test_dlist_insert_by_index();
    test_dlist_prepend();
    test_dlist_append();
    test_dlist_get_data_by_index();
    test_dlist_delete_data_by_index();
    test_dlist_foreach();
    test_dlist_find();

    puts("=== all over. ===");

    return 0;
}

static void free_int(void* ctx, void* data)
{
    if (data != NULL)
        free(data);
}

void test_dlist_insert_by_index()
{
    DList* ls = dlist_create();
    assert(ls != NULL);

    // insert index:0
    int* pVal = malloc(sizeof(int));
    *pVal = 0;
    RetStatus ret = dlist_insert_by_index(ls, 0, pVal);
    assert(ret == RET_OK);

    // insert index:len
    int len = dlist_length(ls);
    assert(len == 1);
    pVal = malloc(sizeof(int));
    *pVal = 1;
    ret = dlist_insert_by_index(ls, len, pVal);
    assert(ret == RET_OK);

    // insert index -1
    len = dlist_length(ls);
    assert(len == 2);
    ret = dlist_insert_by_index(ls, -1, pVal);
    assert(ret == RET_INVALIDATE_INDEX);
    assert(dlist_length(ls) == len);

    // insert index size
    len = dlist_length(ls);
    assert(len == 2);
    ret = dlist_insert_by_index(ls, len+1, pVal);
    assert(ret == RET_INVALIDATE_INDEX);
    assert(dlist_length(ls) == len);

    ret = dlist_destroy(ls, free_int);
    assert(ret == RET_OK);
}

void test_dlist_prepend()
{
    DList* ls = dlist_create();
    assert(ls != NULL);

    int* pVal = malloc(sizeof(int));
    *pVal = 0;

    RetStatus ret = dlist_prepend(ls, pVal);
    assert(ret == RET_OK);
    assert(dlist_length(ls) == 1);

    pVal = malloc(sizeof(int));
    *pVal = 1;
    ret = dlist_prepend(ls, pVal);
    assert(ret == RET_OK);
    assert(dlist_length(ls) == 2);

    assert(dlist_get_data_head(ls) == pVal);

    ret = dlist_destroy(ls, free_int);
    assert(ret == RET_OK);
}

void test_dlist_append()
{
    DList* ls = dlist_create();
    assert(ls != NULL);

    int* pVal = malloc(sizeof(int));
    *pVal = 0;

    RetStatus ret = dlist_append(ls, pVal);
    assert(ret == RET_OK);
    assert(dlist_length(ls) == 1);

    pVal = malloc(sizeof(int));
    *pVal = 1;
    ret = dlist_append(ls, pVal);
    assert(ret == RET_OK);
    assert(dlist_length(ls) == 2);

    assert(dlist_get_data_tail(ls) == pVal);

    ret = dlist_destroy(ls, free_int);
    assert(ret == RET_OK);
}

void test_dlist_get_data_by_index()
{
    DList* ls = dlist_create();
    assert(ls != NULL);

    int* pVal0 = malloc(sizeof(int));
    *pVal0 = 0;
    dlist_append(ls, pVal0);

    int* pVal1 = malloc(sizeof(int));
    *pVal1 = 1;
    dlist_append(ls, pVal1);

    assert(dlist_get_data_by_index(ls, 0) == pVal0);
    assert(dlist_get_data_by_index(ls, 1) == pVal1);
    assert(dlist_get_data_by_index(ls, -1) == NULL);
    assert(dlist_get_data_by_index(ls, dlist_length(ls)) == NULL);

    RetStatus ret = dlist_destroy(ls, free_int);
    assert(ret == RET_OK);
}

void test_dlist_delete_data_by_index()
{
    DList* ls = dlist_create();
    assert(ls != NULL);

    const int test_len = 5;

    for (int i=0; i<test_len; ++i)
    {
        int* pVal = malloc(sizeof(int));
        *pVal = i;
        dlist_append(ls, pVal);
    }

    assert(dlist_length(ls) == test_len);

    const int index = test_len / 2;
    RetStatus ret = dlist_delete_data_by_index(ls, index, free_int);
    assert(ret == RET_OK);
    void* curData = dlist_get_data_by_index(ls, index);
    int* pNowVal = (int*)(curData);
    assert(*pNowVal == (index+1));

    ret = dlist_delete_data_by_index(ls, -1, NULL);
    assert(ret == RET_INVALIDATE_INDEX);

    ret = dlist_delete_data_by_index(ls, dlist_length(ls), NULL);
    assert(ret == RET_INVALIDATE_INDEX);

    ret = dlist_destroy(ls, free_int);
    assert(ret == RET_OK);
}


void test_cal_num(void* ctx, void* data)
{
    int* pRet = (int*)ctx;
    int* pNum = (int*)data;
    *pRet += *pNum;
}

void test_dlist_foreach()
{
    DList* ls = dlist_create();
    assert(ls != NULL);

    const int test_len = 5;
    int total = 0;

    for (int i=0; i<test_len; ++i)
    {
        int* pVal = malloc(sizeof(int));
        *pVal = i;
        dlist_append(ls, pVal);

        total += i;
    }

    int target = 0;
    dlist_foreach(ls, test_cal_num, &target);
    assert(target == total);

    RetStatus ret = dlist_destroy(ls, free_int);
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

void test_dlist_find()
{
    DList* ls = dlist_create();
    assert(ls != NULL);

    const int test_len = 5;

    for (int i=0; i<test_len; ++i)
    {
        int* pVal = malloc(sizeof(int));
        *pVal = i;
        dlist_append(ls, pVal);
    }

    int target = test_len / 2;
    int index = dlist_find(ls, compare_func, &target);
    assert(index == target);

    RetStatus ret = dlist_destroy(ls, free_int);
    assert(ret == RET_OK);
}