#include "dlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// === dlist node
typedef struct _DListNode
{
    struct _DListNode *pNext;
    struct _DListNode *pPrev;
    void *pData;
} DListNode;

static DListNode *dlist_node_create(void *pData)
{
    DListNode *pRet = calloc(1, sizeof(DListNode));
    return_val_if_fail(pRet != NULL, NULL);
    pRet->pData = pData;
    return pRet;
}

static RetStatus dlist_node_destroy(DListNode *thiz, DListFreeDataFunc free_data_func)
{
    if (free_data_func != NULL)
    {
        free_data_func(NULL, thiz->pData);
    }
    free(thiz);
    return RET_OK;
}
// end === dlist node

struct _DList
{
    DListNode *pHead;
    DListNode *pTail;
    int len;
};

DList *dlist_create()
{
    DList *pRet = calloc(1, sizeof(DList));
    return_val_if_fail(pRet != NULL, NULL);

    pRet->len = 0;
    pRet->pHead = dlist_node_create(NULL);
    pRet->pTail = dlist_node_create(NULL);
    pRet->pHead->pNext = pRet->pTail;
    pRet->pTail->pPrev = pRet->pHead;

    return pRet;
}

// maybe return pTail
static DListNode *dlist_find_node_by_index(DList *thiz, int index)
{
    return_val_if_fail(index >= 0 && index <= thiz->len, NULL);

    if (index == thiz->len)
    {
        return thiz->pTail;
    }
    else
    {
        DListNode *pCur = thiz->pHead->pNext;
        while (pCur != NULL)
        {
            if (index == 0)
            {
                return pCur;
            }

            pCur = pCur->pNext;
            --index;
        }
        return NULL;
    }
}

static RetStatus dlist_chain_node(DListNode *pNewNode, DListNode *pListNode)
{
    return_val_if_fail(pListNode->pPrev != NULL, RET_FAIL);

    pListNode->pPrev->pNext = pNewNode;
    pNewNode->pPrev = pListNode->pPrev;
    pNewNode->pNext = pListNode;
    pListNode->pPrev = pNewNode;

    return RET_OK;
}

RetStatus dlist_insert_by_index(DList *thiz, int index, void *data)
{
    return_val_if_fail(index >= 0 && index <= thiz->len, RET_INVALIDATE_INDEX);

    DListNode *pNewNode = dlist_node_create(data);
    return_val_if_fail(pNewNode != NULL, RET_OOM);

    DListNode *findNode = dlist_find_node_by_index(thiz, index);
    assert(findNode != NULL && findNode != thiz->pHead);

    if (dlist_chain_node(pNewNode, findNode) == RET_OK)
    {
        ++thiz->len;
        return RET_OK;
    }
    else
    {
        return RET_FAIL;
    }
}

RetStatus dlist_prepend(DList *thiz, void *data)
{
    return dlist_insert_by_index(thiz, 0, data);
}

RetStatus dlist_append(DList *thiz, void *data)
{
    return dlist_insert_by_index(thiz, thiz->len, data);
}

RetStatus dlist_delete_data_by_index(DList* thiz, int index, DListFreeDataFunc free_data_func)
{
    return_val_if_fail(index >= 0 && index < thiz->len, RET_INVALIDATE_INDEX);

    DListNode* pFindNode = dlist_find_node_by_index(thiz, index);
    assert(pFindNode != NULL && pFindNode != thiz->pTail);

    pFindNode->pPrev->pNext = pFindNode->pNext;
    pFindNode->pNext->pPrev = pFindNode->pPrev;
    dlist_node_destroy(pFindNode, free_data_func);

    return RET_OK;
}

RetStatus dlist_delete_data_head(DList* thiz, int index, DListFreeDataFunc free_data_func)
{
    return dlist_delete_data_by_index(thiz, 0, free_data_func);
}

RetStatus dlist_delete_data_tail(DList* thiz, int index, DListFreeDataFunc free_data_func)
{
    return dlist_delete_data_by_index(thiz, dlist_length(thiz) - 1, free_data_func);
}

void* dlist_get_data_by_index(DList* thiz, int index)
{
    return_val_if_fail(index >= 0 && index < thiz->len, NULL);
    DListNode* pFindNode = dlist_find_node_by_index(thiz, index);
    assert(pFindNode != NULL && pFindNode != thiz->pTail);
    return pFindNode->pData;
}

void* dlist_get_data_head(DList* thiz)
{
    return dlist_get_data_by_index(thiz, 0);
}

void* dlist_get_data_tail(DList* thiz)
{
    return dlist_get_data_by_index(thiz, dlist_length(thiz) - 1);
}

int dlist_length(DList *thiz)
{
    return thiz->len;
}

void dlist_foreach(DList* thiz, DListForeachFunc foreachFunc, void* ctx)
{
    DListNode *pCur = thiz->pHead->pNext;
    while (pCur != thiz->pTail)
    {
        foreachFunc(ctx, pCur->pData);

        pCur = pCur->pNext;
    }
}

int dlist_find(DList* thiz, DListDataCompareFunc cmp, void* ctx)
{
    int i = -1;
    DListNode *pCur = thiz->pHead->pNext;
    while (pCur != thiz->pTail)
    {
        ++i;

        if(cmp(ctx, pCur->pData) == 0)
		{
			break;
		}
		
        pCur = pCur->pNext;
    }
    return i;
}

RetStatus dlist_destroy(DList *thiz, DListFreeDataFunc free_data_func)
{
    DListNode *pCur = thiz->pHead->pNext;
    DListNode *pNext = NULL;
    while (pCur != thiz->pTail)
    {
        pNext = pCur->pNext;

        dlist_node_destroy(pCur, free_data_func);

        pCur = pNext;
    }
    dlist_node_destroy(thiz->pHead, NULL);
    dlist_node_destroy(thiz->pTail, NULL);
    free(thiz);

    return RET_OK;
}