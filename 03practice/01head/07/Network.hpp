//
//  Network.hpp
//  Test
//
//  Created by mfp on 2019/9/11.
//  Copyright © 2019 ccf. All rights reserved.
//

#ifndef Network_hpp
#define Network_hpp

#include <string>

class Server
{
public:
    void init(const std::string& ip, int port);
    
private:
    int m_socket = -1;
};

#endif /* Network_hpp */
