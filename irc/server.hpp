#ifndef server_hpp
#define  server_hpp

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <sys/poll.h>
#define RED "\e[1;31m" 
#define GREEN "\033[1;32m"
#define YELLOW "\e[1;33m"
#define BD "\033[0m"
#define RS "\033[1;35m"
#define BLEU "\033[1;34m"
#include <map>
#include "channel.hpp"
#include "client.hpp"
#include <csignal> 

class server
{
    private:
    std::string pass;
     
    int serverSocket;
    int port;
    std::map<int,client>  clients;
    std::vector<channel *> channels;
   
    public:
    server();
    ~server();
    static bool signn;
    server(std::string p, int  port);
    void ft_server();
    static void signalHandler(int i);
    void ft_close();
    void welcomemsg(void);
    void ft_free();
    void ft_remove_chanels(int fd);
};

#endif