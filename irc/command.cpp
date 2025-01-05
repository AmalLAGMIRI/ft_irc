#include "command.hpp"
#include "client.hpp"
#include "server.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <string>
#include <vector>


#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cerrno>

void ft_response(int fd, const char* message, int i) 
{
    // const char* RED2 = "\x03""04";   // IRC red color code
    // const char* GREEN2 = "\x03""03"; // IRC green color code
    // const char* BD2 = "\x0F";        // IRC reset/bold off code

    char formatted_message[512];

    if (i == 0) {
        std::snprintf(formatted_message, sizeof(formatted_message), "%s:%s \r\n", "SERVER", message);
    } else {
        std::snprintf(formatted_message, sizeof(formatted_message), "%s:%s\r\n", "SERVER", message);
    }

    int len = std::strlen(formatted_message);
     send(fd, formatted_message, len, 0);
}

void command::excute(const std::string& command,const std::vector<std::string>& parameters,std::map< int ,client> &clients, int fd, std::string password,std::vector<channel *> &channels)
{
		if (clients[fd].is_registered() == "none" && command != "PASS") 
		{
			ft_response(fd, "You should enter the passwotrd", 1);
				return ;
		}

		if(clients[fd].is_registered() != "registed"  && command != "USER" && command != "PASS" && command != "NICK")
		{	
			ft_response(fd, "YOu are not registred yet", 1);
			return ;
		}

        if (command == "JOIN") 
		{
            if (parameters.size() >= 1) 
			{
                ft_join(parameters,clients,fd,channels);
            } else 
			{
				ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "JOIN")).c_str(), 0);
            }
        } 
		else if (command == "KICK")
		 {
            if (parameters.size() >= 2) 
			{
				ft_kick(parameters, clients,fd,channels);
            } else 
			{
				ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "KICK")).c_str(), 0);
            }
        }
		else if (command == "USER")
		 {
            if (parameters.size() >= 4) 
			{
                ft_user(parameters,clients,fd);

            } else {

				ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "USER")).c_str(), 0);      
		 }
        }else if(command == "PASS")
		{
			if(parameters.size() >=1)
			{
				ft_pass(parameters,clients,fd,password);

			}else
			{
				ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PASS")).c_str(), 0);
			}

		}else if(command == "NICK")
		{
			if(parameters.size() >= 1)
			{
				ft_nick(parameters,clients,fd);
			}else
			{
				ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "NICK")).c_str(), 0);
			}
		}else if(command == "TOPIC")
		{
			
			ft_topic(parameters,clients,fd);

		}
		else if (command == "PRIVMSG")
	{
        ft_privmsg(parameters, clients, fd);
    }
	else if (command == "NOTICE")
	{
        ft_notice(parameters, clients, fd);
    }
	else if (command == "PART")
	{
        ft_part(parameters, clients, fd);
    }
	else if (command == "INVITE")
	{
        invite(fd, parameters, clients, channels);
    }
	else if (command == "MODE")
	{
        mode(clients, parameters, channels, fd);
    }
	else if (command == "PING")
	{
		ping(parameters, clients, fd);
	}
	else if (command == "GETFILE")
	{
		if (parameters.size() == 2)
            transferFile::ft_getFile(clients, parameters[0], parameters[1], fd);
		else
			send(fd, "error in number arguments\n", strlen("error in number arguments\n"), 0);
	}
	else if (command == "SENDFILE")
	{
		if (parameters.size() == 2)
            transferFile::ft_sendFile(clients, parameters[0], parameters[1], fd);
		else
			send(fd, "error in number arguments\n", strlen("error in number arguments\n"), 0);
	}
	else
		{
				ft_response(fd,"Unknown command: ", 0); 
        }
}
void ft_welcome(int fd,std::map< int ,client> &clients)
{
	std::string one = ":irc.amal 001 " +  clients[fd].get_nickname()+ " :Welcome to the TopG Network, " + clients[fd].get_nickname() + '\n';
	std::string two = ":irc.amal 002 " + clients[fd].get_nickname() + " :Your host is TopG, running version 4.5" + '\n';
	std::string tre = ":irc.amal 003 " + clients[fd].get_nickname() + " :This server is created " + '\n';
	std::string foor = ":irc.amal 004 " + clients[fd].get_nickname() + " irc.amal TopG(enterprise)-2.3(12) netty(5.4c) proxy(0.9)\n";
	send(fd, one.c_str(), one.length(), 0);
	send(fd, two.c_str(), two.length(), 0);
	send(fd, tre.c_str(), tre.length(), 0);
	send(fd, foor.c_str(), foor.length(), 0);
}

command::command()
{

}

// stntax: USER <username> <hostname> <servername> <realname>

//Command: USER  Parameters: <username> 0 * <realname>

void command::ft_user(std::vector<std::string> parametres ,std::map< int ,client> &clients,int fd)
{
	std::map< int ,client>::iterator it;
	for (it = clients.begin(); it != clients.end() ; ++it)
	{
		if(it->first == fd && it->second.is_registered() == "registed")
		{
			ft_response(fd, std::string(ERR_ALREADYREGISTERED(clients[fd].get_nickname())).c_str(), 0);
			return;
		}
		else if (it->second.get_username() == parametres[0] && it->first != fd) 
		{ 
			ft_response(fd, std::string(ERR_USERONCHANNELL(clients[fd].get_nickname())).c_str(), 0);
			return;        	
		}
	}

	if(clients[fd].get_nickname()== "")
	{
			ft_response(fd, "You should enter the nickname first", 0);
			return;
	}
	it = clients.find(fd);
	
	if(it != clients.end())
	{
		clients[fd].set_username(parametres[0]);
		clients[fd].set_hostname(parametres[1]);
		clients[fd].set_servername(parametres[2]);
		std::string realname;
		for(size_t i = 3 ; i < parametres.size() ; i++)	
		{
			realname += parametres[i];
			if(i< parametres.size()-1)
				realname+= " ";
		}
	
		clients[fd].set_realname(parametres[3]);
		if(clients[fd].get_nickname()!= "")
			clients[fd].set_registered("registed");
		ft_welcome(fd,clients);
	}
}


int  isValidNickname(const std::string& nickname) 
{
    for (size_t i = 0; i < nickname.size(); i++) {
        char c = nickname[i];
        if (!(isalnum(c) || c == '[' || c == ']' || c == '{' || c == '}' || c == '|' || c == '\\' || c=='_')) 
		{
            return false;
        }
    }
	return true;
}

// Command: NICK  Parameters: <nickname>
// => nickname

void command::ft_nick(const std::vector<std::string> &parametres ,std::map< int ,client> &clients ,int fd)
{
	client& sender = clients[fd];
	if (parametres.empty())  
	{
		ft_response(fd, std::string(ERR_NONICKNAMEGIVEN(sender.get_nickname())).c_str(), 0);
		return;
	}

	std::map< int ,client>::iterator it;
	for(it = clients.begin() ; it != clients.end() ;++it)
	{
		if(it->second.get_nickname() == parametres[0] && it->first != fd)
		{
			ft_response(fd, std::string(ERR_NICKNAMEINUSE(sender.get_nickname())).c_str(), 0);
		   return;
		}
	}
	
	if(!isValidNickname(parametres[0]))
	{
			ft_response(fd, std::string(ERR_ERRONEUSNICKNAME(sender.get_nickname(), parametres[0])).c_str(), 0);
			return;
	}

	it = clients.find(fd);
	if(it!= clients.end())
	{
		it->second.set_nickname(parametres[0]);
		std::string resp = "Nickname set successfully, Your Nick is " + parametres[0];
		ft_response(fd,resp.c_str(), 1);
	}
}


void ft_msg(channel* channelOfUsers, const std::string& msg,std::map< int ,client> &clients) 
{
    std::vector<int> users = channelOfUsers->get_Users();
    for (size_t i = 0; i < users.size(); ++i) 
	{
		clients[users[i]].write(msg,users[i]);
    }
}

void command::ft_pass(std::vector<std::string> parametres ,std::map< int ,client> &clients ,int fd ,std::string pass)
{
	 client& sender = clients[fd];
	if (parametres.empty()) 
	{
		ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "PASS")).c_str(), 0);
		return;
	}

	if(clients[fd].is_registered() == "pass"  || clients[fd].is_registered() == "registed")
	{	
		ft_response(fd, std::string(ERR_ALREADYREGISTERED(sender.get_nickname())).c_str(), 0);
        return;
	}

	if (parametres[0] == pass) // 
	{
		clients[fd].set_registered("pass");
		ft_response(fd,"PASS command successful", 1);
    } else
	{
	   ft_response(fd,"ERR_PASSWDMISMATCH ", 0);
    }
}

void command::ft_topic(std::vector<std::string> parametres , std::map<int ,client> &clients ,int fd)
{
	client& sender = clients[fd];
	if (parametres.empty())
	{
		ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "TOPIC")).c_str(), 0); 
			return;
	}

	std::string channelName;
	std::string newTopic;

	if (parametres.size() >= 1)
	{
		channelName = parametres[0];
	}

	if (parametres.size() >= 2)
	{
		newTopic = parametres[1];
	}
	bool joinedChannel = false;
	std::vector<channel*>::iterator it;
	for (it = clients[fd].channels.begin(); it != clients[fd].channels.end(); ++it)
	{
		if ((*it)->get_name() == parametres[0])
		{
			joinedChannel = true;
			if (parametres.size() == 1) 
			{
				std::string str= "Topic in this channel: " +  (*it)->get_Topic();
				clients[fd].reply(RPL_TOPIC(clients[fd].get_nickname(),parametres[0],(*it)->get_Topic()),fd);
				break;

			} else if ((*it)->is_operator(fd) || (*it)->getOwner() == fd || !(*it)->get_mode().count('t')) 
			{
				std::string newTopic;
				for(size_t  i = 1; i  < parametres.size();  i++)
				{
					newTopic += parametres[i];
					if(i != parametres.size() - 1)
						newTopic  += " ";
				}
				(*it)->set_topic(newTopic);
			
				std::string msg = ":" + clients[fd].get_prefix() + " TOPIC " + (*it)->get_name() + " " + newTopic;
				ft_msg(*it, msg,clients);
				return;
			}
			else if(parametres.size() > 1)  
			{
				ft_response(fd, std::string(ERR_CHANOPRIVSNEEDED(sender.get_nickname(), channelName)).c_str(), 0);
				return;
			}
		}
	}
	
	if(!joinedChannel)
	{
		ft_response(fd, std::string(ERR_NOTONCHANNEL(sender.get_nickname(), channelName)).c_str(), 0);
    		return;
	}
}


// // Command: JOIN
// // Parameters: <channel>{,<channel>} [<key>{,<key>}]
// // Alt Params: 0

int searchUserInsideChannel(int fd, channel channelS)
{

	if(fd == channelS.getOwner())
		return 3;
	if(channelS.is_operator(fd))
		return 2;
	std::vector<int> test = channelS.get_Users();
	if (std::find(test.begin(), test.end(), fd) != test.end())
		return 1;


	return 0;
}

void command::ft_join(std::vector<std::string> parametres , std::map<int ,client> &clients ,int fd ,std::vector<channel *> &channels)
{
	client& sender = clients[fd];
	if (parametres.empty())
	{
		ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "JOIN")).c_str(), 0);
		return;
	}
		std::istringstream iss2;
    if (parametres.size() > 1)
	{
        iss2.str(parametres[1]);
	}
    std::string buffer;
    std::istringstream iss(parametres[0]); 
	while (std::getline(iss,buffer,','))
	{
		std::vector<channel *>::iterator it;
		for (it = channels.begin(); it != channels.end() ;++it)
		{
			if ((*it)->get_name()== buffer && searchUserInsideChannel(fd,**it))
			{
				ft_response(fd, std::string(ERR_USERONCHANNEL(clients[fd].get_nickname(), buffer)).c_str(), 0);
				break;
			}
			else if((*it)->get_name()== buffer) 
			{
				if ((*it)->get_mode().count('i') != 0) {
					ft_response(fd, std::string(ERR_INVITEONLYCHAN(clients[fd].get_nickname(), buffer)).c_str(), 0);
					return;
				}
				else if((*it)->get_mode().count('l') && static_cast<unsigned int>((*it)->_limit) <= (*it)->get_Users().size()) 
				{
					ft_response(fd, std::string(ERR_CHANNELISFULL(sender.get_nickname(), buffer)).c_str(), 0);
					return;
				}
				buffer = "";
				if(parametres.size() > 1) 
				{
					std::istringstream iss1(parametres[1]); 
					getline(iss1,buffer,',');
				}
				if(!(*it)->get_mode().count('k') ||((*it)->get_mode().count('k') && (*it)->get_key() == buffer)) 
				{
					// add the user to the channel
					clients[fd].channels.push_back(&(*(*it))); 
					ft_response(fd, "You're succesfully joined the channel", 1);
					std::vector<int> users = (*it)->get_Users();
					(*it)->addUser(fd); 
					
					std::string names;
					for(size_t i = 0; i <  users.size(); i++)
					{
						if((*it)->getOwner() == users[i])
							names += "@" + clients[(*it)->getOwner()].get_nickname();
						else
							names += " " + clients[users[i]].get_nickname();
					
						std::string msg = clients[fd].get_nickname()  + " has joined the channel" + (*it)->get_name();
						clients[users[i]].write(RPL_JOIN(clients[fd].get_prefix(),(*it)->get_name() ),users[i]);
						
					}
				
						
						clients[fd].reply(RPL_NAMREPLY(clients[fd].get_nickname(), (*it)->get_name(), names),fd);
						clients[fd].reply(RPL_ENDOFNAMES(clients[fd].get_nickname(),(*it)->get_name() ),fd);
						
						break;
				}
				else{

					ft_response(fd, std::string(ERR_BADCHANNELKEY(clients[fd].get_nickname(), (*it)->get_name())).c_str(), 0);
					break;
				}
				}
			}
			if(it == channels.end()) 
			{
				
				std::string key = ""; 
				if(parametres.size() > 1)
				{
				std::string buffer1;
				getline(iss2,buffer1,',');

				if (!buffer.empty())
					key = buffer1;
				}
				channel* newchannel = new channel(buffer, fd, "", key);
				channels.push_back(newchannel);
				clients[fd].channels.push_back((newchannel));

				clients[fd].reply(RPL_NAMREPLY(clients[fd].get_nickname(), buffer, "@" + clients[fd].get_nickname() ),fd); 
				clients[fd].reply(RPL_ENDOFNAMES(clients[fd].get_nickname(),buffer ),fd);		
				clients[fd].write(RPL_JOIN(clients[fd].get_prefix(),buffer ),fd);
				 newchannel->set_Owner(fd);

				}

	}

}

int serch_by_name(std::map<int ,client> &clients ,const std::string& username)
{
	std::map< int ,client>::iterator it;

	for (it = clients.begin(); it != clients.end() ; ++it)
	{
		if (it->second.get_username() == username) 
		{
			return it->first;        	
		}
	}
	return -1;
}

//Command: KICK
//Parameters: <channel> <user> *( "," <user> ) [<comment>]

void command::ft_kick(std::vector<std::string> parametres , std::map<int ,client> &clients ,int fd ,std::vector<channel *> &channels)
{

	if(parametres.size() < 2)
	{
		ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "KICK")).c_str(), 0);
		return;
	}
	std::istringstream iss1;

    if (parametres.size() > 2) 
	{
        iss1.str(parametres[2]);
	}
	std::string channel_name = parametres[0];
	channel *channelOfUsers;
	size_t i = 0;
	for(i = 0; i < channels.size(); i++)
	{
		if(channels[i]->get_name() == channel_name)
		{
			channelOfUsers = channels[i];
			break;
		}
	}
	int owner = 0;
	if(i == channels.size())
	{
		ft_response(fd, std::string(ERR_NOSUCHCHANNEL(clients[fd].get_nickname(), channel_name)).c_str(), 0); // channls not found
		return ;
	}

	std::string user_to_kick = parametres[1];
	std::string comment;
	std::string buffer;
	
	int check = searchUserInsideChannel(fd, *channelOfUsers);
	if(check == 0)
	{
		ft_response(fd, std::string(ERR_NOTONCHANNEL(clients[fd].get_nickname(), channel_name)).c_str(), 0); 
		return ;
	}
	else if(check == 1)
	{
		ft_response(fd, std::string(ERR_CHANOPRIVSNEEDED(clients[fd].get_nickname(), channel_name)).c_str(), 0);
		return ;
	}
	else if(check ==3){

		owner = 1;
	}
    std::istringstream iss(parametres[1]);
    while (std::getline(iss, buffer, ','))
    {
		int found = serch_by_name(clients, buffer);
		int searchResult = searchUserInsideChannel(found, *channelOfUsers);
		if(found != -1 && (searchResult == 1 || (searchResult ==2 && owner ==1) ))
		{
				
				for(size_t i = 0; i < clients[found].channels.size(); i++) {
					if(clients[found].channels[i]->get_name() == channel_name)
					{
						clients[found].channels.erase(clients[found].channels.begin() + i);
						break;
					}}
					std::string buffer1;
					if(parametres.size() > 2)
					{
						std::getline(iss1, buffer1, ',');
					}
					
						ft_msg(channelOfUsers,RPL_KICK(clients[fd].get_prefix(),channelOfUsers->get_name()  , clients[found].get_nickname(), buffer1),clients);

				std::vector<int>::iterator it;
			 	it = std::find(channelOfUsers->get_Users().begin(), channelOfUsers->get_Users().end(), found);
				if (it != channelOfUsers->get_Users().end()) {
					channelOfUsers->get_Users().erase(it); 
				}
				if(searchResult == 2)
				{
					std::set<int>& operators = channelOfUsers->get_operators();
					std::set<int>::iterator it = operators.find(found); 

					if (it != operators.end()) {
							operators.erase(it); 
						
					}					
				}
				return;
				}
		else if(found != -1 && searchResult) { 
			ft_response(fd, std::string(ERR_CHANOPRIVSNEEDED(clients[fd].get_nickname(), channel_name)).c_str(), 0);
			return;
		}
		else {
			ft_response(fd, std::string(ERR_USERNOTINCHANNEL(clients[fd].get_nickname(), buffer, channel_name)).c_str(), 0);
				return;
		}
	}
}

int ft_ckeak(std::string &nick, std::map<int, client>& clients)
{
	for(std::map<int, client>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second.get_nickname() == nick)
		{
             return it->first;
		}
	}
	return 0;
}

void command::ft_privmsg(std::vector<std::string> args, std::map<int, client>& clients, int fd)
{
    if (args.size() < 2 || args[0].empty() || args[1].empty() || args[1].at(0) != ':')
    {
        ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PRIVMSG")).c_str(), 0);
        return;
    }

	args[1].erase(args[1].begin());
    // Extraire la cible et le message
    std::string target = args.at(0);
    std::string message;

    for (std::vector<std::string>::iterator it = args.begin() + 1; it != args.end(); ++it)
		(it != (args.end() - 1)) ? message.append(*it + " ") : message.append(*it);
    // Si le message est destiné à un canal
    if (target.at(0) == '#')
    {
        channel* chan = NULL;

		target.erase(target.begin());
        // Recherche du canal par son nom
        for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it)
        {
			chan = it->second.get_channel_by_name(target);
			if (chan)
				break;
        }

        // Canal non trouvé
        if (!chan)
        {
             ft_response(fd, std::string(ERR_NOSUCHCHANNEL(clients[fd].get_nickname(), target)).c_str(), 0);
            return;
        }
		// std::cout << "\nClient ID: " << clients[fd].get_id() << std::endl;
		// Vérifier si le client est dans le canal
		if (!chan->is_member(fd))
		{
			ft_response(fd, std::string(ERR_CANNOTSENDTOCHAN(clients[fd].get_nickname(), target)).c_str(), 0);
			return;
		}

        // Diffuser le message au canal
        chan->broadcast(RPL_PRIVMSG(clients[fd].get_prefix(), target, message), clients, fd);
        return;
    }

    // Si le message est destiné à un autre client
    client* destClient = NULL;
    for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->second.get_nickname() == target)
        {
            destClient = &(it->second);
            break;
        }
    }

    if (destClient == NULL)
    {
        ft_response(fd, std::string(ERR_NOSUCHNICK(clients[fd].get_nickname(), target)).c_str(), 0);
        return;
    }

    // Envoyer le message au client destinataire
    destClient->write(ft_ckeak(args[0], clients), RPL_PRIVMSG(clients[fd].get_prefix(), target, message));
}

void command::ft_notice(std::vector<std::string> args, std::map<int, client>& clients, int fd)
{
   if (args.size() < 2 || args[0].empty() || args[1].empty() || args[1].at(0) != ':')
    {
      ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PRIVMSG")).c_str(), 0);
        return;
    }

	args[1].erase(args[1].begin());
    // Extraire la cible et le message
    std::string target = args.at(0);
    std::string message;

    for (std::vector<std::string>::iterator it = args.begin() + 1; it != args.end(); ++it)
		(it != (args.end() - 1)) ? message.append(*it + " ") : message.append(*it);
    // Si le message est destiné à un canal
    if (target.at(0) == '#')
    {
        channel* chan = NULL;

		target.erase(target.begin());
        // Recherche du canal par son nom
        for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it)
        {
			chan = it->second.get_channel_by_name(target);
			if (chan)
				break;
        }

        // Canal non trouvé
        if (!chan)
        {
            ft_response(fd, std::string(ERR_NOSUCHCHANNEL(clients[fd].get_nickname(), target)).c_str(), 0);
            return;
        }

		// Vérifier si le client est dans le canal
		if (!chan->is_member(fd))
		{
			ft_response(fd, std::string(ERR_CANNOTSENDTOCHAN(clients[fd].get_nickname(), target)).c_str(), 0);
			return;
		}

        // Diffuser le message au canal
        chan->broadcast(RPL_NOTICE(clients[fd].get_prefix(), target, message), clients, fd);
        return;
    }

    // Si le message est destiné à un autre client
    client* destClient = NULL;
    for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->second.get_nickname() == target)
        {
            destClient = &(it->second);
            break;
        }
    }

    if (destClient == NULL)
    {
        ft_response(fd, std::string(ERR_NOSUCHNICK(clients[fd].get_nickname(), target)).c_str(), 0);
        return;
    }

    // Envoyer le message au client destinataire
    destClient->write(ft_ckeak(args[0], clients), RPL_NOTICE(clients[fd].get_prefix(), target, message));
}

std::vector<std::string> split(std::string s)
{
	std::stringstream ss(s);
	std::vector<std::string> res;
	std::string tmp;
	
	while (std::getline(ss, tmp, ','))
		res.push_back(tmp);
	return res;
}

void remove_client_from_channel(client& target, channel *ch, int fd)
{
	ch->remove_user(fd);	
	target.remove_channel(ch);
}

void command::ft_part(std::vector<std::string> args, std::map<int, client>& clients, int fd)
{
    if (args.empty()) 
    {
        ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PART")).c_str(), 0);
        return;
    }
	std::vector<std::string> targetChannels = split(args[0]);
	// TODO: jion all messages
	std::string reason = args.size() > 1 ? args[1] : "";

	for (std::vector<std::string>::iterator ch_it = targetChannels.begin(); ch_it != targetChannels.end(); ++ch_it)
	{
		channel *ch = NULL;
		std::string nickname = clients[fd].get_nickname();

		// Check if channel exists and get its object
		for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it)
        {
			ch = it->second.get_channel_by_name(*ch_it);
			if (ch)
				break;
        }

		if (!ch)
		{
			ft_response(fd, std::string(ERR_NOSUCHCHANNEL(nickname, *ch_it)).c_str(), 0);
			continue;
		}
		if (!ch->is_member(fd))
		{
			ft_response(fd, std::string(ERR_NOTONCHANNEL(nickname, *ch_it)).c_str(), 0);
			continue;
		}
		remove_client_from_channel(clients[fd], ch, fd);
		clients[fd].write(fd, RPL_PART(clients[fd].get_nickname(), *ch_it, reason));
		ch->broadcast(RPL_PART(clients[fd].get_nickname(), *ch_it, reason), clients, fd);
	}
}

void command::invite(int fd, const std::vector<std::string>& args, std::map<int, client>& clients, std::vector<channel*>& channels) {
    client& sender = clients[fd];

    if (args.size() < 2) {
		ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "INVITE")).c_str(), 0);
        return;
    }

    std::string invitedNickname = args[0];
    std::string channelName = args[1];

    // Trouver le client invité par son pseudo !!! Merciiii
    std::map<int, client>::iterator invitedClientIt = clients.end();

    for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->second.get_nickname() == invitedNickname) {
            invitedClientIt = it;
            break;
        }
    }

	// Check if no target user
    if (invitedClientIt == clients.end()) {
        ft_response(fd, std::string(ERR_NOSUCHNICK(sender.get_nickname(), invitedNickname)).c_str(), 0);
        return;
    }

    // Trouver le canal par son nom !!! Merciiiii
    std::vector<channel*>::iterator chanIt = channels.end();

    for (std::vector<channel*>::iterator it = channels.begin(); it != channels.end(); ++it) {
        if ((*it)->get_name() == channelName) {
            chanIt = it;
            break;
        }
    }

	// Check if no target channel
    if (chanIt == channels.end()) {
        ft_response(fd, std::string(ERR_NOSUCHCHANNEL(sender.get_nickname(), channelName)).c_str(), 0);
        return;
    }

	// Check if the sender is a member of the target channel
	if (!(*chanIt)->is_member(fd)) {
		ft_response(fd, std::string(ERR_NOTONCHANNEL(sender.get_nickname(), channelName)).c_str(), 0);
		return;
	}

	// Check if the target user is not already a member of the target channel
	if ((*chanIt)->is_member(invitedClientIt->first)) {
		ft_response(fd, std::string(ERR_USERONCHANNEL(sender.get_nickname(), channelName)).c_str(), 0);
		return;
	}
	 if ((*chanIt)->get_mode().count('i') != 0 && !(*chanIt)->is_operator(fd) && (*chanIt)->getOwner() != fd) {
        ft_response(fd, std::string(ERR_CHANOPRIVSNEEDED(sender.get_nickname(), channelName)).c_str(), 0);
        return;
    }
    // Inviter le client au canal
    sender.invite_to_channel(fd, invitedClientIt, *chanIt);
}

void command::ping(std::vector<std::string> args, std::map<int, client>& clients, int fd)
{
    if (args.empty())
    {
        ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "PING")).c_str(), 0);
        return;
    }

    std::string target = args[0];

    // Verify the client exists in the clients map
    if (clients.find(fd) == clients.end())
    {
        ft_response(fd, std::string(ERR_NOSUCHNICK(clients[fd].get_nickname(), target)).c_str(), 0);
        return;
    }

    // Respond to the PING command
    clients[fd].write(fd, RPL_PONG(target));
}

void command::mode(std::map<int, client>& clients, std::vector<std::string> args, std::vector<channel*>& channels, int fd) {
    // Handling errors
	client& sender = clients[fd];
    if (args.size() < 2) {
        ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "MODE")).c_str(), 0);
        return;
    }

    std::string target = args[0];
    channel* chan = NULL;

    // Recherche du canal par nom
    for (size_t i = 0; i < channels.size(); ++i) {
        if (channels[i]->get_name() == target) {
            chan = channels[i];
            break;
        }
    }

    if (!chan) {
        ft_response(fd, std::string(ERR_NOSUCHCHANNEL(sender.get_nickname(), target)).c_str(), 0);
        return;
    }

    // user is not an operator
    if (!chan->is_operator(fd) && chan->getOwner() != fd) 
	{
        ft_response(fd, std::string(ERR_CHANOPRIVSNEEDED(sender.get_nickname(), target)).c_str(), 0);
        return;
    }
    //Changing the mode
    std::string modeStr = args[1];

    if (modeStr == "+i" || modeStr == "-i") {
        chan->change_invite_only_mode(modeStr);
		chan->broadcast(RPL_MODE(sender.get_nickname(), chan->get_name(), modeStr, ""), clients, fd);
    }
	else if (modeStr == "+t" || modeStr == "-t") {
        chan->change_topic_mode(modeStr);
		chan->broadcast(RPL_MODE(sender.get_nickname(), chan->get_name(), modeStr, ""), clients, fd);
    }
	else if (modeStr == "+k" || modeStr == "-k") {
        if (args.size() < 3 && modeStr == "+k") {
            ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "MODE")).c_str(), 0);
            return;
        }
        chan->change_key_mode(clients, args, modeStr, fd);
		chan->broadcast(RPL_MODE(sender.get_nickname(), chan->get_name(), modeStr, ""), clients, fd);
    }
	else if (modeStr == "+o" || modeStr == "-o") {
        if (args.size() < 3) {
            ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "MODE")).c_str(), 0);
            return;
        }
        chan->change_operator_mode(clients, args, modeStr, fd);
		chan->broadcast(RPL_MODE(sender.get_nickname(), chan->get_name(), modeStr, ""), clients, fd);
    }
	else if (modeStr == "+l" || modeStr == "-l") {
        if (args.size() < 3 && modeStr == "+l") {
            ft_response(fd, std::string(ERR_NEEDMOREPARAMS(sender.get_nickname(), "MODE")).c_str(), 0);
            return;
        }
        chan->change_limit_mode(clients, args, modeStr, fd);
		chan->broadcast(RPL_MODE(sender.get_nickname(), chan->get_name(), modeStr, ""), clients, fd);
    }
	else 
        ft_response(fd, std::string(ERR_UNKNOWNMODE(sender.get_nickname(), modeStr)).c_str(), 0);
}

command::~command()
{

}
