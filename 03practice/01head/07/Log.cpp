//
//  Log.cpp
//  Test
//
//  Created by mfp on 2019/9/11.
//  Copyright © 2019 ccf. All rights reserved.
//

#include "Log.hpp"
#include "TimeFormat.hpp"

#include <stdlib.h>

using namespace std;

ofstream Log::m_outStream;

void Log::init()
{
    m_outStream.open("log.txt", ofstream::out | ofstream::app);
    if (!m_outStream.is_open())
    {
        errExit("log open");
    }
}

void Log::info(const std::string& msg)
{
    m_outStream << "[" << TimeFormat::getFullTime() << "] " << msg << endl;
}

void Log::errExit(const char* const msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
