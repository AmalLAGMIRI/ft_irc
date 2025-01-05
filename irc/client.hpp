#ifndef client_hpp
#define  client_hpp

#include <iostream>
#include <sstream>
#include <cstddef>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <stdio.h>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>
#include<map>
#include <set>
#include "ft_bot.hpp"
#define ERR_NEEDMOREPARAMS(source, command)             "461 " + source + " " + command + " :Not enough parameters"
#define ERR_NOSUCHCHANNEL(source, channel)              "403 " + source + " " + channel + " :No such channel"
#define ERR_CANNOTSENDTOCHAN(source, channel)           "404 " + source + " " + channel + " :Cannot send to channel"
#define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " :" + message
#define ERR_NOSUCHNICK(source, nickname)                "401 " + source + " " + nickname + " :No such nick/channel"
#define RPL_NOTICE(source, target, message)             ":" + source + " NOTICE " + target + " :" + message
#define RPL_PING(source, token)                         ":" + source + " PONG :" + token
#define RPL_MODE(source, channel, modes, args)          ":" + source + " MODE " + channel + " " + modes + " " + args
#define ERR_CHANOPRIVSNEEDED(source, channel)           "482 " + source + " " + channel + " :You're not channel operator"
#define ERR_NOTONCHANNEL(source, channel)               "442 " + source + " " + channel + " :You're not on that channel"
#define RPL_PART(source, channel, reason)                       ":" + source + " PART :" + channel + " " + reason
#define ERR_UNKNOWNMODE(nickname, mode) "472 " + nickname + " " + mode + " :is unknown mode char to me"
#define RPL_PONG(token) "PONG :" + token
#define ERR_USERONCHANNEL(source, channel) "443 " + source + " " + channel + " :is already on channel"
#define RPL_INVITING(user, channel) "341 " + user + " " + channel + " :Inviting"
#define ERR_ALREADYREGISTERED(source)                   "462 " + source + " :You may not register"
#define ERR_NONICKNAMEGIVEN(source)                     "431 " + source + " :Nickname not given"
#define ERR_NICKNAMEINUSE(source)                       "433 " + source   + " :Nickname is already in use"
#define ERR_ERRONEUSNICKNAME(client, nick) "432 " + client + " " + nick + " :Erroneous nickname"
#define ERR_INVITEONLYCHAN(client, channel) "473 " + client + " " + channel + " :Cannot join channel (+i)"
#define ERR_BADCHANNELKEY(source, channel)              "475 " + source + " " + channel + " :Cannot join channel (+k)"
#define ERR_USERNOTINCHANNEL(source, nickname, channel) "441 " + source + " " + nickname + " " + channel + " :They aren't on that channel"
#define ERR_NOPRIVILEGES(source) ("481 " + source + " :Permission Denied- You're not an IRC operator")
#define RPL_NAMREPLY(source, channel, users)            "353 " + source + " = " + channel + " :" + users
#define RPL_ENDOFNAMES(source, channel)                 "366 " + source + " " + channel + " :End of /NAMES list."
#define RPL_JOIN(source, channel)                       ":" + source + " JOIN :" + channel
#define RPL_KICK(source, channel, target, reason)       ":" + source + " KICK " + channel + " " + target + " :" + reason
#define RPL_TOPIC(nickname,channel,topic)      "332 " + nickname + " " +  channel + " " + topic 
#define ERR_CHANNELISFULL(source, channel)              "471 " + source + " " + channel + " :Cannot join channel (+l)"
#define ERR_USERONCHANNELL(source)           "443 " + source +  " :is already on channel"

class channel;
class client
{
    private:
        std::string state;
        int fd;
        int id;                                                                                                                                                                                                                                                                                                                                
        std::string port;
        std::string nickname;
        std::string username;
        std::string realname;
        std::string hostname;
        std::string password;
        channel* ChannelPtr;
        std::string servername;
        std::set<std::string>  Operators;
        std::set<std::string> modes;

         std::map<std::vector<std::string>, std::string> bufferFile;

    public:
    /* Getters */
    bot bot_client;
        std::vector<channel*>  channels;

        int             get_fd() const;
        int             get_port() const;
        std::string     get_nickname() const;
        std::string     get_username() const;
        std::string     get_realname() const;
        std::string     get_hostname() const;
        std::string get_servername() const;
        int get_id() const;
        std::vector<channel*>       get_channel() const;
        channel* get_channel_by_name(const std::string& name) const;
        std::string is_registered();
        std::string get_password() const;
        void sendMessage(const std::string& message);
        void invite_to_channel(int fd, std::map<int, client>::iterator& invitedClient, channel* channel);
        std::string get_prefix() const;
        void write(int fd, const std::string& message) const;
        void remove_channel(const channel* channelToRemove);
        void close_connection();
        std::set<std::string> &get_operators();

    /**setes*/
        void            set_nickname(const std::string nickn);
        void            set_username(const std::string usern);
        void            set_realname(const std::string realn);
        void            set_hostname(const std::string hostn);
        void            set_channel(const std::vector<channel*> chan);
        void            set_registered(std::string status);
        void            write(const std::string& message,int fd) const;
        void            reply(const std::string& reply,int fd);
        void            set_servername(const std::string    server_n);
        void            set_bufferFile(std::string sender, std::string &buffer, const std::string &filename);
        std::map<std::vector<std::string>, std::string> &get_dataBuffer();
        client();
        client & operator=(const client &orginal);
        client(const client &orginal);

        ~client();
};

#endif