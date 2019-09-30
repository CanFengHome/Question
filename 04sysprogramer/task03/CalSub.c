#include <stdio.h>
#include <stdlib.h>

#include "CalSub.h"
#include "common.h"

typedef struct _CalSub
{
    int a;
    int b;
} CalSub;

static void cal_sub_input(ICal* thiz, int lh, int rh)
{
    CalSub* pSub = (CalSub*)(thiz->priv);
    pSub->a = lh;
    pSub->b = rh;
}

static int cal_sub_get_result(ICal* thiz)
{
    CalSub* pSub = (CalSub*)(thiz->priv);
    return pSub->a - pSub->b;
}

static void cal_sub_destroy(ICal* thiz)
{
    free(thiz);
}

ICal* ICal_sub_create()
{
    ICal* ret = calloc(1, sizeof(ICal) + sizeof(CalSub));
    return_val_if_fail(ret != NULL, NULL);

    ret->input = cal_sub_input;
    ret->getResult = cal_sub_get_result;
    ret->destroy = cal_sub_destroy;

    return ret;
}
