#include <iostream>     
#include <string> 
#include<vector>
#include <map>
#include "ft_transfer_file.hpp"
#include <sys/stat.h>

const std::string &transferFile::parss_Path(const std::string &Path_filename)
{
    size_t pos = Path_filename.find('/');
    if (pos != std::string::npos)
    {
        std::stringstream ss(Path_filename);
        std::string token;
        std::vector<std::string> parts;

        while (std::getline(ss, token, '/')) 
            parts.push_back(token);
        std::string &filename = parts.back();
        return filename;
    }
  return Path_filename;
}

void transferFile::ft_sendMessage(int fd, const char color[], std::string mssg)
{
    std::string message;
    message += color;
    message += mssg;
    message +=  "\033[0m";
    send(fd, message.c_str() ,message.length(), 0);
}

void transferFile::ft_sendFile(std::map<int, client> &clients, const std::string &Nickname, const std::string &filename, int fdd)
{
	int fd;
	std::string buff;
     std::map<int, client>::iterator s;
     for (s = clients.begin(); s != clients.end(); s++)
     {
        if (s->second.get_nickname() == Nickname)
        {
            fd = s->first;
            std::ifstream file(filename.c_str());
            if (!file.is_open())
			{
                std::cerr << "\e[1;31m" << "Error opening file"  << "\033[0m" << std::endl;
				    ft_sendMessage(fdd, "\e[1;31m", "error in open this file, sorry try again\n");
                return;
            }
            char buffer[1024];
            while (!file.eof())
            {
                 file.read(buffer, sizeof(buffer));
                 buff += std::string(buffer, file.gcount());
            }
			s->second.set_bufferFile(clients[fdd].get_nickname(), buff, filename);
			std::map<std::vector<std::string>, std::string> g =  s->second.get_dataBuffer();
			ft_sendMessage(fd, "\e[1;32m", "you have recieved a file form " + clients[fdd].get_nickname() + " that can be downloaded "  + filename + " using cmd GETFILE:\n");
            return ;	
        }
     }
    ft_sendMessage(fdd, "\e[1;31m", "not found this nickname\n");
	std::cout << "\e[1;31m" <<  "not found this nickname\n" << "\033[0m";
}

void transferFile::ft_getFile(std::map<int, client> &clients, const std::string &Nickname, const std::string &filename, int fdd)
{
     std::map<int, client>::iterator s;
     for (s = clients.begin(); s != clients.end(); s++)
     {
        if (s->second.get_nickname() == Nickname)
        {
            std::map<std::vector<std::string>, std::string> files =  clients[fdd].get_dataBuffer();
            std::map<std::vector<std::string>, std::string>::iterator it;
            for(it = files.begin(); it != files.end(); it++)
            {
                std::vector<std::string> info = it->first;
                if (info[0] == Nickname && info[1] == filename)
                {
                    std::string folderName = "Files_";
                    folderName += clients[fdd].get_nickname();
                    if (mkdir(folderName.c_str(), 0755) == 0 || errno == EEXIST) 
                    std::cout << "\e[1;32m" << "Directory created or already exists." << "\033[0m" << std::endl;
                    else 
                    {
                        std::cout << "\e[1;31m" <<  "Failed to create directory." << "\033[0m" << std::endl;
                        return ;
                    }
                    std::string filena = parss_Path(filename);
                    std::ofstream file((folderName + "/" + Nickname + "_" + filena).c_str());
                    if (!file.is_open())
                    {
                        std::cerr << "\e[1;31m" <<  "Error opening file" << "\033[0m" << std::endl;
                        ft_sendMessage(fdd,"\e[1;31m", "error in open this file, sorry try again\n");
                        return;
                    }
                    file  << files[info];
                    return ;
                }           
            }
        }
     }
     ft_sendMessage(fdd,"\e[1;31m", "not found this file from this sender\n");
      std::cout << "\e[1;31m" << "not found this file from this sender" << "\033[0m" << std::endl;
}

transferFile::~transferFile(){};
