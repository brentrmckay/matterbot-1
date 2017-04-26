#include "Matterbot.h"
#include <iostream>
#include <sstream>
#include "ConsoleLogger.h"
#include "EchoCommand.h"
#include "RivestmentPrompts.h"
#include "challenges.h"
#include "getpoints.h"
#include "scraps.h"
#include "getpassword.h"
//#include "MD5Finder.h"
//#include "ReverseCommand.h"
//#include "WeatherCommand.h"
//#include "TicTacToe.h"
//#include "RivestmentResponses.h"

#define ERROR_SUCCESS 0
#define ERROR_FAILURE -1

using namespace std;
using namespace lospi;

int main() {
	wstring mattermost_url = L"https://hooks.slack.com",
	//hooksinfo
    welcome_message = L"bot is running.";

  try {
    auto bot = make_shared<Matterbot>(mattermost_url, incoming_hook_route, outgoing_hook_route, outgoing_hook_token);
    bot->set_logger(make_unique<ConsoleLogger>());
    bot->register_command(make_shared<EchoCommand>());
	bot->register_command(make_shared<RivestmentPrompts>(bot));
	bot->register_command(make_shared<challenges>(bot));
	bot->register_command(make_shared<getpoints>());
	bot->register_command(make_shared<scraps>(bot));
	bot->register_command(make_shared<getpassword>());

	//bot->register_command(make_shared<WeatherCommand>());
	//bot->register_command(make_shared<md5>());
	//bot->register_command(make_shared<tictactoe>());
	//bot->register_command(make_shared<ReverseCommand>(bot));
	
    bot->post_message(welcome_message);

    wstring console;
    wclog << ">> Type \'quit\' to quit. Any other input will be sent to the bot." << endl;
    while (getline(wcin, console)) {
      if (L"quit" == console) {
        wclog << ">> Quitting." << endl;
        return ERROR_SUCCESS;
      }
      if (L"" != console) { bot->post_message(console); }
    }
  }
  catch (exception e) {
    wcerr << "[-] Unhandled exception:" << e.what() << endl;
    return ERROR_FAILURE;
  }
}
