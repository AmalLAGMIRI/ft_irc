#include <iostream>
#include "server.hpp"
#include "command.hpp"
#include "client.hpp"
#include "ft_bot.hpp"
#define RESET "\033[0m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define Mage "\033[95m"
#define ROSY "\033[38;2;255;102;203m"
#define LIGHT "\033[38;5;218m"
#define PURPLE "\033[1;35m"
#define orange "\033[38;5;208m"
#define GREENN "\e[1;32m"
#include <iostream>
#include <string>
#include <csignal>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include "server.hpp"
#include "command.hpp"
#include "client.hpp"
#include "ft_bot.hpp"
#define RESET "\033[0m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define Mage "\033[95m"
#define ROSY "\033[38;2;255;102;203m"
#define LIGHT "\033[38;5;218m"
#define PURPLE "\033[1;35m"
#define orange "\033[38;5;208m"
#include <iostream>
#include <string>
#include <csignal>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

#define PINK    "\033[38;5;206m" // Light pink
#define ROSE    "\033[38;5;210m" // Rose
#define BLUSH   "\033[38;5;219m" // Blush
#define CORAL   "\033[38;5;209m" // Coral
#define SALMON  "\033[38;5;173m" // Salmon
#define MAUVE   "\033[38;5;176m" // Mauve
#define LAVENDER "\033[38;5;183m" // Lavender


bot::bot()
{
     index = 0;
	 score_bot = 0;
	 s = 0;
	 bott = 0;
}
int &bot::get_index()
{
	return index;
}

int bot::get_score() const
{
	return score_bot;
}
int bot::get_bot() const
{
	return bott;
}

void bot::set_score(int n)
{
	score_bot = n;
}

void bot::set_bot(int b)
{
	bott = b;
}

void bot::set_index(int i)
{
	index = i;
}

void bot::addQuestion(int index,const std::string& correctAnswer, const std::string& optionA, const std::string& optionB, const std::string& optionC, const std::string& corr) {
    QuestionData qd = {correctAnswer, optionA, optionB, optionC, corr};
    questions[index] = qd;
}

bool bot::checkAnswer(int index, const std::string& userAnswer) 
{
    return questions[index].correctAnswer == userAnswer;
}

int bot::ft_presentation()
{
		addQuestion(-1,  "Do you want to complete the game? (yes/no)\n", "hh", "hhh", "hhhh", "yes\n");
		addQuestion(0, "Are you ready to start? (yes/no);", "yes", "yes", "no", "yes\n");
		addQuestion(1, "Which of the following is a valid C++ data type?", 
						"integer", "int", "num", "b\n");
		addQuestion(2, "What is the correct syntax for declaring a pointer in C?", 
						"int ptr;", "int *ptr;", "int &ptr;", "b\n");
		addQuestion(3, "Which of the following is not a standard header file in C?", 
						"stdio.h", "conio.h", "stdlib.h", "b\n");
		addQuestion(4, "How do you comment a single line in C++?", 
						"/* comment */", "# comment", "// comment", "c\n");
		addQuestion(5, "What is the default return type of the main function in C++?", 
						"void", "int", "float", "b\n");
		addQuestion(6, "Which of the following operators is used to access a member of a structure through a pointer in C?", 
						".", "->", "::", "b\n");
		addQuestion(7, "What is the output of the following code in C++?\n\nint a = 5;\nstd::cout << ++a;", 
						"4", "5", "6", "c\n");
		addQuestion(8, "Which function is used to dynamically allocate memory in C?", 
						"malloc()", "alloc()", "new", "a\n");
		addQuestion(9, "What is the purpose of the 'const' keyword in C++?", 
						"To define a constant value", "To declare a constant pointer", "Both", "c\n");
		addQuestion(10, "Which of the following is a valid way to declare an array in C?", 
						"int array[5];", "int array(5);", "int array{5};", "a\n");
		addQuestion(11, "Which of the following is a loop construct in C?", 
						"for", "foreach", "loop", "a\n");
		addQuestion(12, "What is the output of the following C code?\n\nint x = 10;\nprintf(\"%d\", x);", 
						"x", "10", "%d", "b\n");
		addQuestion(13, "What is the size of a 'char' data type in C?", 
						"1 byte", "2 bytes", "4 bytes", "a\n");
		addQuestion(14, "What is the use of the 'break' statement in C++?", 
						"To exit a loop", "To terminate a function", "To skip the current iteration", "a\n");
		addQuestion(15, "Which of the following is the correct way to declare a reference variable in C++?", 
						"int &ref;", "int ref;", "int *ref;", "a\n");
		addQuestion(16, "What does STL stand for in C++?", 
						"Standard Type Library", "Standard Template Library", "Standard Text Library", "b\n");
		addQuestion(17, "Which of the following is not a valid access specifier in C++?", 
						"public", "protected", "internal", "c\n");
		addQuestion(18, "What is the purpose of the 'virtual' keyword in C++?", 
						"To define a virtual function", "To create a new object", "To declare a static function", "a\n");
		addQuestion(19, "What is the use of the 'sizeof' operator in C?", 
						"To determine the size of a data type", "To allocate memory", "To create an array", "a\n");
		addQuestion(20, "Which of the following is a valid way to define a constant in C?", 
						"#define PI 3.14", "const float PI = 3.14;", "Both", "c\n");
		addQuestion(21, "Which keyword is used to handle exceptions in C++?", 
						"try", "catch", "throw", "a\n");
		addQuestion(22, "What is a destructor in C++?", 
						"A special member function called when an object is destroyed", "A function to allocate memory", "A function to initialize an object", "a\n");
		addQuestion(23, "Which of the following is a preprocessor directive in C?", 
						"#include", "import", "require", "a\n");
		addQuestion(24, "What is the purpose of the 'continue' statement in C++?", 
						"To exit a loop", "To skip the current iteration of a loop", "To terminate a function", "b\n");
		addQuestion(25, "Which function is used to compare two strings in C?", 
						"strcmp()", "strcpy()", "strcat()", "a\n");
		addQuestion(26, "Which of the following is a correct way to declare a function in C++?", 
						"void func();", "function void func();", "void function();", "a\n");
		addQuestion(27, "What is the output of the following C++ code?\n\nint x = 5;\nstd::cout << x--;", 
						"4", "5", "6", "b\n");
		addQuestion(28, "What is the purpose of the 'new' operator in C++?", 
						"To declare a new variable", "To allocate memory dynamically", "To create a new function", "b\n");
		addQuestion(29, "Which of the following is used to deallocate memory in C++?", 
						"free()", "delete", "Both", "b\n");
		addQuestion(30, "What does the 'static' keyword mean in C++?", 
						"The variable retains its value across function calls", "The variable is constant", "The variable is global", "a\n");

	return 0;
}

void bot::ft_header_bot(int fd)
{
	std::ofstream file("txt.txt");
	file.is_open();
	std::string sendd;
	sendd = ROSY;
	std::string str;
	sendd += "🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸\n";
	sendd += "🌸🌸🌸🌸🌸🌸★♫.•°”˜˜”°•.♫°”˜˜”°•.♫°”˜˜”°•.♫°”˜˜”°•.♫°”˜˜”°•.♫°”˜˜”🌸🌸🌸🌸🌸🌸\n";
	sendd += "🌸🌸🌸🌸🌸🌸   ★   ▄▄▄▄▄   ★     ★       ★   ★      ★  ★   ★     ★🌸🌸🌸🌸🌸🌸\n";
	sendd += "🌸🌸🌸🌸🌸🌸  ★ ▄▀░░░░░░▀▄░██░██ █████ ██░░ ██░░ █████    ★   ★   🌸🌸🌸🌸🌸🌸\n";
	sendd += "🌸🌸🌸🌸🌸🌸 ★ ▐░▄▄▄░░▐▀▌░▌██▄██ ██▄▄▄ ██░░ ██░░ ██░██   ★    ★   🌸🌸🌸🌸🌸🌸\n";
	sendd += "🌸🌸🌸🌸🌸🌸 ★ ▐░░░░░░░░░░▌██▀██ ██▀▀▀ ██░░ ██░░ ██░██     ★      🌸🌸🌸🌸🌸🌸\n";
	sendd += "🌸🌸🌸🌸🌸🌸 ★ ▐░░▀▄░░▄▀░░▌██░██ █████ ████ ████ █████    ★  ★ ★  🌸🌸🌸🌸🌸🌸\n";
	sendd += "🌸🌸🌸🌸🌸🌸 ★★ ▀▄░░▀▀░░▄▀   ★   ★   ★  ★    ★  ★   ★  ★   ★   ★  🌸🌸🌸🌸🌸🌸\n";
	sendd += "🌸🌸🌸🌸🌸🌸   ★★ ▀▀▀▀▀▀   ★  ★    ★   ★   ★  ★  ★   ★    ★    ★  🌸🌸🌸🌸🌸🌸\n";
	sendd += "🌸🌸🌸🌸🌸🌸★.•°”˜˜”°•.♫°”˜˜”°•.♫°”˜˜”°•.♫°”˜˜”°•.♫°”˜˜”°•.♫°”˜˜”°🌸🌸🌸🌸🌸🌸\n";
	sendd += "🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸\n";
	sendd += "🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸\n\n";
	sendd += RESET;
    sendd += ROSY;
	sendd += " #####  ★   ⭐       ★     ##   ⭐             ##     ##      ★ ⭐  #######\n";
	sendd += "##   ##             ⭐    ####                 ###   ###     ⭐     ##\n";
	sendd += "##           ★        ★  ##  ##     ★       ⭐ #### ####            ##\n";
	sendd += "##  ###                 ##    ##               ## ### ##    ★ ⭐    ######\n";
	sendd += "##   ##             ⭐  ########    ⭐         ##  #  ##            ##\n";
	sendd += "##   ##     ⭐          ##    ##               ##     ##       ★    ##\n";
	sendd += " #####                  ##    ##    ★          ##     ##         ⭐ #######\n\n";

	send(fd, sendd.c_str(), sendd.length(), 0);
	str = "\033[1;35m";
	str += "Welcome to the Question and Answer Game 🥰!";
	str += "\033[0m";

	str += LIGHT;
	str += "\nIn this game, you'll be presented with questions and you need to provide the correct answers.";
	str += "For each correct answer, you'll earn points. Let's see how many points you can score!\n";
	str += "\033[0m";

	 str = PURPLE;
	str += "\nAre you ready to start? (yes/no); \n";
	str += "\033[0m";
    send(fd, str.c_str(), str.length(), 0);
}

void bot::choose_questions(std::string &question, std::string &a, std::string &b, std::string &c,  int fd)
{
	std::string str;
	str = GREEN;
	str += "                     ,---.           ,---.\n";
	str += "                    / /\"`\\.--\"\"\"\"--./,'\"\\ \\\n";
	str += "                    \\ \\    _       _    / /\n";
	str += "                     `./  / __   __ \\  \\,'\n";
	str += "                      /    /_O)_(_O\\    \\\n";
	str += "                      |  .-'  ___  `-.  |\n";
	str += "                   .--|       \\_/       |--.\n";
	str += "                 ,'    \\   \\   |   /   /    `.\n";
	str += "                /       `.  `--^--'  ,'       \\\n";
	str += "           .-\"\"\"\"\"\"\"-. .  `--.___.--'     .-\"\"\"\"\"\"\"-.\n";
	str += ".-----------/         \\------------------/         \\------------|\n";
	str += "| .---------\\         /----------------- \\         /------------|\n";
	str += "| |          `-`--`--'                     `--'--'-'            | |\n";
	str += "| |                                                             | |\n";
	str += "  ⭐ " + question + " ⭐ 									\n";
	str += "| |                                                             | |\n";
	str += "| |                                                             | |\n";
	str += "| |                                                             | |\n";
	str += "| |_____________________________________________________________| |\n";
	str += "|_________________________________________________________________|\n";
	str += "                   )__________|__|__________(\n";
	str += "                  |            ||            |\n";
	str += "                  |____________||____________|\n";
	str += "                    ),-----.(      ),-----.(\n";
	str += "                  ,'   ==.   \\    /  .==    `.\n";
	str += "                 /            )   (            \\\n";
	str += "                 `============'   `===========' \n" ;
	str += RESET;
	str += ROSY;
	str += "  	 🌸 a) ";
	str += a;
	str += "\n\n";
	str += "  	 🌸 b) ";
	str += b;
	str += "\n\n";
	str += "  	 🌸 c) ";
	str += c;
	str += "\n\n";
	str += RESET;
	send(fd, str.c_str(), str.length(), 0);
}

std::string bot::convert_to_string(int n)
{
	std::stringstream s;
	s << n;
	return s.str();
}

void bot::ft_terminete(std::map<int, client> &clients, int fd, int choose)
{
	        std::string str = orange;
			if (choose == 1)
			{
				str += "\n🎈🎈 Congratulations on completing the quiz!. Now, let's see how well you did. Here are your results: 🎈🎈 ";
				str+= convert_to_string(clients[fd].bot_client.get_score());
			    str +=  "/20\n";
			}
			else
			    str += "\nNo problem! Whenever you're ready, just come back to start the game 😔.\n";
			str += RESET;
			send(fd, str.c_str(), str.length(), 0);
			clients[fd].bot_client.set_bot(0);
			clients[fd].bot_client.set_index(0);
			clients[fd].bot_client.set_score(0);
			clients[fd].bot_client.s = 0;
}

int bot::generateRandomQuestions(int fd, std::map<int, client> &clients) 
{
    std::srand(std::time(0));
    int randomIndex = 0;
    clients[fd].bot_client.usedQuestions.push_back(0);
    do 
	{
        randomIndex = std::rand() % 30 + 1;
    } 
	while (std::find(clients[fd].bot_client.usedQuestions.begin(), clients[fd].bot_client.usedQuestions.end(), randomIndex) != clients[fd].bot_client.usedQuestions.end());
        clients[fd].bot_client.usedQuestions.push_back(randomIndex);
	return randomIndex;
}

void bot::ft_cheackk(std::map<int, client> &clients, int fd, std::string &recv)
{
	std::string str;
	if  (clients[fd].bot_client.get_index() == 0)
	      clients[fd].bot_client.qs = 0;
    switch (clients[fd].bot_client.qs) 
	{
		case -1:
		    if (recv != "yes\n" && recv != "no\n") 
			{
				str = CORAL;
				str += "\nEntrer (yes/no); \n";
				str += RESET;
				send(fd, str.c_str(), str.length(), 0);
				return ;
            }
			else if (!checkAnswer(clients[fd].bot_client.qs, recv))
			{
                ft_terminete(clients, fd, 1);
				return ;
			}		   
		    break ;
        case 0:
            if (recv != "yes\n" && recv != "no\n") 
			{
                str = CORAL;
                str += "\nEntrer (yes/no); \n";
                str += RESET;
                send(fd, str.c_str(), str.length(), 0);
				return ;
            }
            else if (checkAnswer(clients[fd].bot_client.qs, recv)) 
			{
				str += orange;
                str += "\nGreat! Let's begin 😉...\n";
                str += RESET;
                send(fd, str.c_str(), str.length(), 0);
				sleep(1);
            }
			else 
			{
                ft_terminete(clients, fd, 0);
				return ;
			}
            break;
        default:
            if (checkAnswer(clients[fd].bot_client.qs, recv)) 
			{
                str = GREENN;
                str += "Well done, your answer is correct. Congratulations,👏👏 you got two points\n";
                str += RESET;
                send(fd, str.c_str(), str.length(), 0);
                clients[fd].bot_client.set_score(clients[fd].bot_client.get_score() + 2);
            } 
			else 
			{
                if (recv != "a\n" && recv != "b\n" && recv != "c\n") 
				{
                    str = CORAL;
                    str += "=>> Choose one of the answers:(a or b or c);\n";
                    str += RESET;
                    send(fd, str.c_str(), str.length(), 0);
                    return;
                }
                str = RED;
                str += "Unfortunately, your answer is wrong 😔. Try again\n";
                str += RESET;
                send(fd, str.c_str(), str.length(), 0);
            }
    }
	if (clients[fd].bot_client.get_index() > 11)
	{
	    ft_terminete(clients, fd, 1);
		return ;
	}
	clients[fd].bot_client.qs = generateRandomQuestions(fd, clients);
	if ((clients[fd].bot_client.s % 2) % 2 != 0)
	{
		str = YELLOW;
		str +=  "Do you want to complete the game? (yes/no)\n";
		str += RESET;
		send (fd, str.c_str(), str.length(),0);
		clients[fd].bot_client.qs = -1;
		 clients[fd].bot_client.s += 1;
	}
	else 
	{
		choose_questions(questions[clients[fd].bot_client.qs].question, questions[clients[fd].bot_client.qs].optionA, 
		questions[clients[fd].bot_client.qs].optionB,questions[clients[fd].bot_client.qs].optionC, fd);
		clients[fd].bot_client.set_index(clients[fd].bot_client.get_index() + 1);  
		clients[fd].bot_client.s += 1;
	} 
}

void bot::ft_bot(std::map<int, client> &clients, int fd)
{
	try 
	{
		ft_header_bot(fd);
		int total = ft_presentation();
		(void)total;
		(void)clients;
	}
	catch (char const str[])
	{
		std::cout <<  BLEU << "😢 client disconnected" <<  BD  << std::endl;
		close (fd);
	}
}
