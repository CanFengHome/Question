#ifndef ICAL_H_
#define ICAL_H_

struct _ICal;
typedef struct _ICal ICal;

typedef void (*ICalInput)(ICal* thiz, int lh, int rh);
typedef int (*ICalGetResult)(ICal* thiz);
typedef void (*ICalDestroy)(ICal* thiz);

struct _ICal
{
    ICalInput input;
    ICalGetResult getResult;
    ICalDestroy destroy;

    char priv[0];
};

static inline void ICal_input(ICal* thiz, int lh, int rh)
{
    thiz->input(thiz, lh, rh);
}

static inline int ICal_get_result(ICal* thiz)
{
    return thiz->getResult(thiz);
}

static inline void ICal_destroy(ICal* thiz)
{
    thiz->destroy(thiz);
}

#endif