#ifndef ft_transfer_file_hpp
#define ft_transfer_file_hpp
#include <cstddef>
#include <iostream>
#include <fstream>
#include <unistd.h>     // for close()
#include <sys/socket.h> // for socket-related functions
#include <unistd.h>     // for close()
#include <cstring>      // for memset()
#include <iostream>     // for cout
#include <string> 
#include <string>
#include <cstdlib> 
#include <stdio.h>
#include<vector>
#include <map>
#include "client.hpp"
//void ft_bot(int fd);
class transferFile
{
    public:
    void static ft_sendFile(std::map<int, client> &clients,const std::string &Nickname, const std::string &filename, int fdd);
	void static ft_getFile(std::map<int, client> &clients, const std::string &Nickname, const std::string &filename, int fd);
    void static ft_sendMessage(int fd, const char color[], std::string mssg);
    const static std::string &parss_Path(const std::string &Path_filename);
    ~transferFile();
};
#endif
