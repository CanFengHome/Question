#ifndef TOKEN_BUCKET_HPP_
#define TOKEN_BUCKET_HPP_

namespace TokenBucket
{
    bool init();
    
    int createBucket(int cps, int burst);
    void destroyBucket(int bkt);

    int fetchToken(int bkt);
    void returnToken(int bkt, int retval);
};

#endif