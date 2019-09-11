//
//  Utility.cpp
//  Test
//
//  Created by mfp on 2019/9/11.
//  Copyright © 2019 ccf. All rights reserved.
//

#include "Utility.hpp"

#include <stdio.h>
#include <stdarg.h>

using namespace std;

namespace Utility
{
    std::string formatStr(const char* const format, ...)
    {
        va_list args;
        va_start(args, format);
        char buf[BUFSIZ];
        vsnprintf(buf, BUFSIZ, format, args);
        va_end(args);
        
        return buf;
    }
}
