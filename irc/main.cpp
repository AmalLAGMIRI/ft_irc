#include "channel.hpp"
#include "client.hpp"
#include "command.hpp"
#include "server.hpp"

int main(int argc,char **argv)
{
   (void)argv;
    if(argc != 3)
    {
        std::cerr << "usage : ./ircserv [port] [password]" << std::endl;
            return (1);
    }
    server serverClient = server(argv[2], std::atoi(argv[1]));
    try
    {
        signal(SIGINT, serverClient.signalHandler);  
        signal(SIGQUIT, serverClient.signalHandler);
         serverClient.ft_server();
    }
    catch(std::string &str)
    {
        std::cout << str << BD << std::endl;
        serverClient.ft_close();
    }
    return (0);
}
