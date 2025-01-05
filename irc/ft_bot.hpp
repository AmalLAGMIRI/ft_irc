
#ifndef FT_bot_hpp
#define FT_bot_hpp

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
#include <ctime>
#include <cstdlib>
#include <algorithm> 

struct QuestionData 
{
         std::string question;
        std::string optionA;
        std::string optionB;
        std::string optionC;
        std::string correctAnswer;

};
class client;
class bot
{
  
    private:
        
    public:
       int s;
       int qs;
       int score_bot;
        int index;
        int bott;
        std::map<int, QuestionData> questions;
       std::vector<int> usedQuestions;
       std::vector<std::string> answers;
       
       bot();

       int &get_index();
       int get_score() const;
       int  get_bot() const;

       void  set_index(int i);
       void set_score(int n);
       void set_bot(int b);
    
       void choose_questions(std::string &a, std::string &b, std::string &c, std::string &question, int fd);
       int ft_presentation();
       void ft_bot(std::map<int, client> &clients, int fd);
       std::string covert_to_string(int n);
       void ft_cheackk(std::map<int, client> &clients, int fd, std::string &recv);
       void addQuestion(int index,const std::string& correctAnswer, const std::string& optionA, const std::string& optionB, const std::string& optionC, const std::string& corr);
       bool checkAnswer(int index, const std::string& userAnswer);
       void ft_header_bot(int fd);
       void ft_terminete(std::map<int, client> &clients, int fd, int choose);
       std::string convert_to_string(int n);
       int generateRandomQuestions(int fd, std::map<int , client> &clients);
};
#endif

