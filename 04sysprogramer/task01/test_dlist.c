#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dlist.h"

void test_dlist_insert_by_index();

int main()
{
    test_dlist_insert_by_index();

    puts("=== all over. ===");

    return 0;
}

void free_int(void* ctx, void* data)
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