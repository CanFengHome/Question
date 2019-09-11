//
//  TimeFormat.cpp
//  Test
//
//  Created by mfp on 2019/9/11.
//  Copyright © 2019 ccf. All rights reserved.
//

#include "TimeFormat.hpp"

#include <time.h>

using namespace std;

namespace TimeFormat
{
    std::string getFullTime()
    {
        time_t rawtime = time(NULL);
        struct tm * timeinfo = localtime(&rawtime);
        char buf[BUFSIZ];
        strftime(buf, BUFSIZ, "%F %T", timeinfo);
        return buf;
    }
}

