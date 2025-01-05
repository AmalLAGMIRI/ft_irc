#include "channel.hpp"
#include <algorithm>

channel::channel(std::string& name, int owner, std::string topic, std::string key)
		: Name(name), Owner(owner), Key(key), Topic(topic), _limit(-1) {
        Users.push_back(owner);
}

channel::channel(): Owner(-1), _limit(-1) {}

channel::channel(const  channel &original)
: Name(original.Name), Owner(original.Owner), Key(original.Key),
          Topic(original.Topic), Operators(original.Operators), mode(original.mode), _limit(original._limit)
          , Users(original.Users)
{

}

 void channel::add_user(int userId) { 
    Users.push_back(userId);
}

channel &channel::operator=(const channel &original)
{
	if (this != &original) {
            Name = original.Name;
            Owner = original.Owner;
            Users = original.Users;
            Key = original.Key;
            Topic = original.Topic;
            _limit = original._limit;
            Operators = original.Operators;
            mode = original.mode;
        }
        return *this;
    }

void channel::broadcast(const std::string& message, std::map<int, client>& clients, int curr_client_fd)
{
    for (std::vector<int>::iterator it = Users.begin(); it != Users.end(); ++it)
    {
        if (*it == curr_client_fd)
            continue;
        clients[*it].write(*it, message);
    }
}


bool channel::is_member(int fd) const {
    if (std::find(Users.begin(), Users.end(), fd) != Users.end() || Owner == fd) {
        return true;
    }
    return false;
}

bool channel::is_operator(int userId) const {
  return this->Operators.count(userId) != 0;
}

channel* channel::get_channel_by_name(const std::string& channelName, const std::vector<channel*>& channels) {
    for (size_t i = 0; i < channels.size(); ++i) {
        if (channels[i]->get_name() == channelName) {
            return channels[i];
        }
    }
    return NULL;
}

/* gesters*/

std::string channel::get_name() const
{
	return this->Name;
}

std::string channel::get_key() const
{
	return this->Key;
}

std::string channel::get_Topic() const
{
	return this->Topic;
}

int channel::getOwner() const
{
	return  Owner;
}

 const std::set<char>& channel::get_mode() const {
        return mode;
}

std::vector<int> &channel::get_Users()
{
	return Users;
}

/*seters */

void channel::set_name(const std::string  namee)
{
	this->Name = namee;
}

void channel::set_key(const std::string keyy)
{
	this->Key = keyy;
}

void  channel::set_topic(const std::string topic)
{
	this->Topic = topic;
}

void channel::set_Owner(const int owner)
{
	this->Owner = owner;
}

void channel::set_Users(const std::vector<int> users)
{
	this->Users =  users;
}
std::set<int> &channel::get_operators() 
{
    return this->Operators;
}

void channel::addUser(int userId)
{
   Users.push_back(userId);
}


void channel::remove_user(int userId)
{
    std::vector<int>::iterator it = std::find(Users.begin(), Users.end(), userId);

    if (it == Users.end())
        return;
    Users.erase(it);
}

void channel::set_limit(int limit)
{
    _limit = limit;
}

channel::~channel()
{
}

void channel::change_invite_only_mode(std::string& mode) {
    if (mode == "+i") {
        this->mode.insert('i');
    } else {
        this->mode.erase('i');
    }
}

void channel::change_topic_mode(std::string& mode) {
    if (mode == "+t") {
        this->mode.insert('t');
    } else {
        this->mode.erase('t');
    }
}

bool channel::change_key_mode(std::map<int, client>& clients, std::vector<std::string>& args, std::string& mode, int fd) {
    if (mode == "+k") {
        if (args.size() < 3) {
            ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "CHANGE_KEY_MODE")).c_str(), 0);
            return false;
        }
        this->mode.insert('k');
        this->Key = args[2];
    } else {
        this->mode.erase('k');
        this->Key = "";
    }
    return true;
}


bool channel::change_operator_mode(std::map<int, client>& clients, std::vector<std::string>& args, std::string& mode, int fd) 
 {
    if (args.size() < 3) {
         ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "CHANGE_OPERATOR_MODE")).c_str(), 0);
        return false;
    } 

    std::string username = args[2]; // Le nom de l'utilisateur est le troisième argument

    // Vérifier si l'utilisateur existe
    client* userClient = NULL;
    int userFd = -1; // Initialisez userFd à une valeur par défaut
    for (std::map<int, client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->second.get_nickname() == username) {
            userClient = &(it->second);
            userFd = it->first; // Stocker la clé de la carte, qui est le descripteur de fichier
            break;
        }
    }

    if (userClient == NULL) {
        ft_response(fd, std::string(ERR_NOSUCHNICK(clients[fd].get_nickname(), username)).c_str(), 0);
        return false;
    }

    if (!this->is_member(userFd)) {
        ft_response(fd, std::string(ERR_USERNOTINCHANNEL(clients[fd].get_nickname(), username, this->Name)).c_str(), 0);
        return false;
    }
    if (mode == "+o")
        this->Operators.insert(userFd);
    else
        this->Operators.erase(userFd);
    
    return true;
}

bool channel::change_limit_mode(std::map<int, client>& clients, std::vector<std::string>& args, std::string& mode, int fd)
{
     if (mode == "+l") {
            if (args.size() < 3) {
                ft_response(fd, std::string(ERR_NEEDMOREPARAMS(clients[fd].get_nickname(), "CHANGE_LIMIT_MODE")).c_str(), 0);
                return false;
            }
            this->mode.insert('l');
            std::stringstream ss(args[2]);
            ss >> this->_limit;
        }
        else {
            this->mode.erase('l');
            this->_limit = 0;
        }
        return true;
}


