#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include "Rivestment.h"
#include <map>
#include <chrono>
#include <thread>
#include <sstream>
#include <iterator> 
#include <algorithm>
#include <string>
#define HASHCOST 5
#define DEFAULT_RANGE 25
#define MAX_RANGE 100

namespace lospi
{
	//Function Prototypes
	std::wstring findHash(std::vector<std::string> vstrings);
	std::vector<std::string> parseInput(const std::wstring command_text);
	void generateMap(void);

	//Command Definition
	struct RivestmentPrompts : ICommand {
		explicit RivestmentPrompts(std::shared_ptr<Matterbot> bot) : bot{bot} { }
		std::wstring get_name() override {
			return L"rivestment";
		}

		std::wstring get_help() override {
			return L"`rivestment [CMD]`:\n\t`begin` Registers the user, sets the password. Level will begin at `1` and will be tuned.";
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {

			//Invalid User
			if (user != L"brentmckay") {
				return (L"You are not allowed McBot use.");
			}

			//Challenge Logic
			else if (command_text == L"begin") {
				//Set Username
				userName = L"McBot";
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));

				//Register User
				bot->post_message(L"rivestment register " + userName);
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));

				//Fetch Password
				bot->post_message(L"rivestment password");
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));

				//Set Level
				level = 3;
				bot->post_message(L"rivestment level " + std::to_wstring(level));
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));

				//Set alphabet
				alphabet = "josh";
				bot->post_message(L"Current Alphabet: " + string_to_wstring(alphabet));
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));

				//Generate Map
				bot->post_message(L"Generating Lookup Tables");
				generateMap();
				bot->post_message(L"Lookup Tables Generated");

				//Fetch Current Point Total
				bot->post_message(L"rivestment points");
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));

				//Find Optimal Range
				//range = DEFAULT_RANGE;
				range = std::min(int((points / HASHCOST)), MAX_RANGE);

				//Call For Challenges
				bot->post_message(L"rivestment challenge");
				return (L" `begin` complete");
			}
			//Invalid Command
			else {
				return (L"Invalid Command.");
			}
		}

		//Shared Pointer Definition
		private:
			std::shared_ptr<Matterbot> bot;
	};
}
