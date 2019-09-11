#ifndef Log_hpp
#define Log_hpp

#include <fstream>
#include <string>

class Log
{
public:
    static void init();
    
    static void info(const std::string& msg);
    static void errExit(const char* const msg);
private:
    static std::ofstream m_outStream;
};

#endif /* Log_hpp */
