#ifndef Client_hpp
#define Client_hpp

#include <string>
#include <arpa/inet.h>

class Client
{
public:
    Client() = default;
    explicit Client(int socket, const struct sockaddr_in* socket_addr);
    
    int getSocket() const;
    std::string getInfo() const;

    void destroy();
private:
    int m_socket = -1;
    std::string m_ip;
    int m_port = -1;
};

#endif /* Client_hpp */
