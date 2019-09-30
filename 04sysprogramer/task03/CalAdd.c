#include <stdio.h>
#include <stdlib.h>

#include "CalAdd.h"
#include "common.h"

typedef struct _CalAdd
{
    int a;
    int b;
} CalAdd;

static void cal_add_input(ICal* thiz, int lh, int rh)
{
    CalAdd* pAdd = (CalAdd*)(thiz->priv);
    pAdd->a = lh;
    pAdd->b = rh;
}

static int cal_add_get_result(ICal* thiz)
{
    CalAdd* pAdd = (CalAdd*)(thiz->priv);
    return pAdd->a + pAdd->b;
}

static void cal_add_destroy(ICal* thiz)
{
    free(thiz);
}

ICal* ICal_add_create()
{
    ICal* ret = calloc(1, sizeof(ICal) + sizeof(CalAdd));
    return_val_if_fail(ret != NULL, NULL);

    ret->input = cal_add_input;
    ret->getResult = cal_add_get_result;
    ret->destroy = cal_add_destroy;

    return ret;
}