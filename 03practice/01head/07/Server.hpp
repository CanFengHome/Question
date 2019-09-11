#ifndef Server_hpp
#define Server_hpp

#include <string>

class Client;

class Server
{
public:
    Server() = default;
    void init(int port);
    void init(const std::string& host, int port);
    Server(const Server& other) = delete;
    Server& operator=(const Server& other) = delete;
    
    void setBlock();
    void setUnBlock();
    
    int getSocket() const;
    
    Client accept();
    
    void destroy();
private:
    int m_socket = -1;
};

#endif /* Server_hpp */
