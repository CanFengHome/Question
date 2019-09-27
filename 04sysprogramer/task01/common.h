#ifndef COMMON_H_
#define COMMON_H_

typedef enum _RetStatus
{
    RET_OK,
    RET_FAIL,
    RET_INVALIDATE_INDEX,
    RET_OOM,
} RetStatus;

#define return_if_fail(p) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n", \
		__func__, __LINE__); return;}
#define return_val_if_fail(p, ret) if(!(p)) \
	{printf("%s:%d Warning: "#p" failed.\n",\
	__func__, __LINE__); return (ret);}

#endif