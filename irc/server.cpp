
#include "channel.hpp"
#include"command.hpp"
#include "client.hpp"
#include "server.hpp"
#include "ft_bot.hpp"
#include <pthread.h> 
#include <fcntl.h>
void server::welcomemsg(void)
{
	std::string welcome = RED;
	welcome.append("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
	welcome.append("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
	welcome.append("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n");
	welcome.append("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n");
	welcome.append("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
	welcome.append(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
	welcome.append(BLEU);
	welcome.append("You need to login so you can start chatting OR you can send HELP to see how :) \n");
	welcome.append(RS);
    std::cout << welcome<< std::endl;
}

void server::ft_free()
{
     for (std::vector<channel *>::iterator it  = channels.begin() ; it != channels.end(); it++)
        delete *it;
}

bool server::signn = true;

server::server()
{}

server::server(std::string p, int port)
{
    this->pass = p;
    this->port = port;
}

void server::signalHandler(int i)
{
    (void)i;
    signn = false;
    server s;
    std::cout << RS << std::endl;
    std::string str = "throw signal \n";
    throw (str);
}

void server::ft_close()
{
    for(std::map<int, client>::iterator n = clients.begin(); n != clients.end(); n++)
    {
        close (n->first);
    }
}

void server::ft_remove_chanels(int fd)
{
     for (std::vector<channel*>::iterator it = channels.begin(); it != channels.end();) 
     {
        std::vector<int>::iterator it2 = std::find((*it)->Users.begin(), (*it)->Users.end(), fd);
        if (it2 != (*it)->Users.end()) 
        {
            (*it)->Users.erase(it2);
            if ((*it)->Users.size() == 0)
            {
                std::vector<channel*>::iterator  tmp = it;
                it = channels.erase(it);
                delete *tmp;
            }
            else
                ++it; 
        }
        else
          ++it;
    }
}

void server::ft_server()
{
    int c = 0;
    std::vector<pollfd> fds;
    command executeCommand = command();
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cout << "error in create socket \n";
        close (serverSocket);
    }
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY; // htonl(INADDR_LOOPBACK); 
    int optval = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
    {
        close(serverSocket);
        throw "Error setting socket options";
    }
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        close(serverSocket);
        throw "Error binding socket";
    }
    if (listen(serverSocket, 10) == -1) 
    {
        close(serverSocket);
        throw "Error listening";
    }
     welcomemsg();
    std::cout << YELLOW << "Server listening.......\n" << BD;
    
    pollfd t;
    t.fd = serverSocket;
    t.events = POLLIN;
    fds.push_back(t);
    bot bott;
    while (signn != false)
    {  
        c = poll(fds.data(), fds.size(), -1);
        if (c == -1)
        {
            std::cout << "error in function poll \n";
        }
        else if (c > 0)
        {
            for(unsigned int i = 0; i < fds.size() ; i++)
            {
                if (fds[i].revents & POLLIN)
                {
                    if (fds[i].fd == serverSocket)
                    {
                        struct sockaddr_in clientAddr;
                     
		                socklen_t clientAddrSize = sizeof(clientAddr);
                        int clientsock = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrSize);
                        if (clientsock == -1)
                        {
                            close(serverSocket);
                            close (clientsock);
                            throw "Error in accept";
                        }
                        else
                        {
                            if (fcntl(clientsock, F_SETFL, O_NONBLOCK) == -1)
                            {
                                close(serverSocket);
                                close(clientsock);
                                throw "Error in fcntl";
                            }
                            pollfd t;
                            t.fd = clientsock;
                            t.events = POLLIN;
                            fds.push_back(t);
                            client newClient = client();
                            clients[t.fd] = newClient;
                            std::cout << RS << "accept connection ......." << BD << std::endl;
                        }              
                    }
                    else
                    {
                        char buffer[1024];
                        std::string total;
    
                            int bytesReceived = recv(fds[i].fd, buffer, sizeof(buffer), 0);
                            if (bytesReceived == -1)
                                close(fds[i].fd);
                            else if (bytesReceived == 0) 
                            {
                                std::cout <<  BLEU << "😢 client disconnected" <<  BD  << std::endl;
                                    int f = fds[i].fd;
                                    clients.erase(f);
                                    fds.erase(fds.begin() + i);

                                    ft_remove_chanels(f);
                                   close(f);
                                  --i;                   
                            }
                            else if (clients[fds[i].fd].bot_client.get_bot() == 1)
                            {
                                std::string line = std::string(buffer, bytesReceived);
                                clients[fds[i].fd].bot_client.ft_cheackk(clients,fds[i].fd, line);
                            }
                            else
                            {
                                std::string line = std::string(buffer, bytesReceived);
                                std::cout  << "line recieved ==== > " << line << std::endl;
                                std::vector<std::string> tokens;
                                std::istringstream iss(line);
                                std::string token;
                                std::string com ;
                                iss >> com;
                                while (iss >> token) 
                                {
                                    tokens.push_back(token);
                                }
                              
                                if (com == "BOT")
                                {
                                    if (tokens.size() == 0)
                                    {
                                        clients[fds[i].fd].bot_client.set_bot(1);
                                        clients[fds[i].fd].bot_client.ft_bot( clients, fds[i].fd);
                                    }
                                    else
                                        send(fds[i].fd, "error in number arguments\n",strlen("error in number arguments\n"), 0);
                               }
                               else
                               {
                    
                                 executeCommand.excute(com,tokens, clients,fds[i].fd,pass,  channels);
                               }
                            }
                    }
               }
        }
    }
    } 
}

server::~server()
{
    for (std::vector<channel *>::iterator it  = channels.begin() ; it != channels.end(); it++)
        delete *it;
}
