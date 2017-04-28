#include "Matterbot.h"
#include "ConsoleLogger.h"
#include "EchoCommand.h"
#include "RivestmentPrompts.h"
#include "challenges.h"
#include "scraps.h"
#include "getpoints.h"
#include "getpassword.h"
#include <iostream>
#define ERROR_SUCCESS 0
#define ERROR_FAILURE -1

using namespace std;
using namespace lospi;

int main() {
	wstring mattermost_url = L"https://hooks.slack.com",
	incoming_hook_route = L"services/T4Z1QAKSS/B5071EGBF/2D0Ok4THVkmhtLdNBn20zLDz",
	outgoing_hook_route = L"http://127.0.0.1:7777/",
	outgoing_hook_token = L"yABOaSRAkFqybSJtNNcmgGCr",
    welcome_message = L"bot is running.";

  try {
    auto bot = make_shared<Matterbot>(mattermost_url, incoming_hook_route, outgoing_hook_route, outgoing_hook_token);
    bot->set_logger(make_unique<ConsoleLogger>());
    bot->register_command(make_shared<EchoCommand>());
	bot->register_command(make_shared<RivestmentPrompts>(bot));
	bot->register_command(make_shared<challenges>(bot));
	bot->register_command(make_shared<scraps>(bot));
	bot->register_command(make_shared<getpoints>());
	bot->register_command(make_shared<getpassword>());
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
