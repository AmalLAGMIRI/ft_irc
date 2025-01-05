#include "client.hpp"
#include "channel.hpp"
#include <algorithm>

client::client(): fd(-1), id(-1), ChannelPtr(NULL)
{
	state = "none";
}

client::client(const client& original) {
    fd = original.fd;
    id = original.id;
    nickname = original.nickname;
    username = original.username;
    realname = original.realname;
    hostname = original.hostname;
    password = original.password;
    ChannelPtr = original.ChannelPtr;
    servername = original.servername;
    channels = original.channels;
    state = original.state;
}

client& client::operator=(const client& original) {
    if (this != &original) {
        fd = original.fd;
        id = original.id;
        nickname = original.nickname;
        username = original.username;
        realname = original.realname;
        hostname = original.hostname;
        password = original.password;
        ChannelPtr = original.ChannelPtr;
        servername = original.servername;
        channels = original.channels;
    }
    return *this;
}

void client::write(int fd, const std::string& message) const {
    send(fd, (message + "\r\n").c_str(), (message + "\r\n").length(), 0);
}

void client::sendMessage(const std::string& message) {
    // Envoyer le message au socket du client
    std::cout << "fd: " << fd << std::endl;
    send(fd, message.c_str(), message.length(), 0);
}

void client::invite_to_channel(int fd, std::map<int, client>::iterator& invitedClient, channel* channel) {
    int target = invitedClient->first;
    write(target, "INVITE " + get_nickname() + " " + channel->get_name());
    invitedClient->second.channels.push_back(channel);
    channel->addUser(target);
    write(fd, RPL_INVITING(get_nickname(), channel->get_name()));
}



void client::remove_channel(const channel* channelToRemove)
{
    for (std::vector<channel*>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if ((*it)->get_name() == channelToRemove->get_name())
        {
            it = channels.erase(it);
            return;
        }
    }
}



void            client::write(const std::string& message,int fd) const
{
    std::string buffer = message + "\r\n";
    if (send(fd, buffer.c_str(), buffer.length(), 0) < 0)
        throw std::runtime_error("Error while sending a message to a client!");
}

void            client::reply(const std::string& reply,int fd)
{

    this->write(":" + get_prefix() + " " + reply,fd);
}

int client::get_fd() const
{
	return fd;
}

std::string client::get_prefix() const 
{
     std::string user = "";
     std::string host = "";

    if (!username.empty()) {
        user = "!" + username;
    }

    if (!hostname.empty()) {
        host = "@localhost";
    }

    return nickname + user + host;
}



std::string client::is_registered()
{
    return state;
}

int client::get_id() const {
    return id;
}

std::string client::get_password() const 
{
	return this->password;
}

void client::set_registered(std::string status)
{
        this->state = status;
}

std::string client::get_nickname() const
{
	return nickname;
}
std::string client::get_username() const
{
	return username;
}
std::string client::get_realname() const
{
	return realname;
}
std::string client::get_hostname() const
{
	return hostname;
}

std::vector<channel *> client::get_channel() const
{
	return channels;
}

std::string client::get_servername() const
{
    return servername;
}

channel* client::get_channel_by_name(const std::string& name) const {

    for (std::vector<channel*>::const_iterator it = this->channels.begin(); it != this->channels.end(); ++it)
    {
        if ((*it)->get_name() == name) 
            return *it;
    }
    return NULL;
}
/* Setters */

void client::set_nickname(const std::string nickn)
{
	this->nickname = nickn;
}

void client::set_username(const std::string usern)
{
	this->username = usern;
}

void client::set_realname(const std::string realn)
{
	this->realname = realn;
}

void client::set_hostname(const std::string hostn)
{
	this->hostname = hostn;
}

void client::set_channel(const std::vector<channel *> chan)
{
	this->channels = chan;
}

void           client:: set_servername(const std::string    server_n)
{
	this->servername = server_n;
}

void client::close_connection() {
    close(fd);
    state = "offline";
}

std::set<std::string> &client::get_operators() {
    return Operators;
}

client::~client()
{

}


 void    client::set_bufferFile(std::string sender, std::string &buffer, const std::string &filename)
 {
	std::vector<std::string> info;
	info.push_back(sender);
	info.push_back(filename);
	bufferFile[info] = buffer;
 }

 std::map<std::vector<std::string>, std::string> &client::get_dataBuffer()
{
	return bufferFile;
}
