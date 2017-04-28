#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include "Rivestment.h"
#include <chrono>
#include <iterator> 
#include <map>
#include <sstream>
#include <string>
#include <thread>

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
			return L"`rivestment [CMD]`:\n\t`begin`: Registers the user, sets the password. Level will begin at " + std::to_wstring(STARTING_LVL) + L" and will be tuned automatically\n\t`lvlup`: Exits auto-level and increments the current level by 1\n\t`lvldown`: Exits auto-level and decrements the current level by 1\n\t`quit`: Removes McBot from the Rivestment program";
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {

			//Invalid User
			if (user != L"brentmckay") {
				return (L"You are not allowed McBot use");
			}

			//Challenge Logic
			else if (command_text == L"begin") {
				//Set Username
				userName = L"McBot";

				//Register User
				bot->post_message(L"rivestment register " + userName);
				inGame = true;
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));

				//Fetch Password
				bot->post_message(L"rivestment password");
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));

				//Set Level
				mapLevel = 0;
				level = STARTING_LVL;
				autoLvl = true;
				bot->post_message(L"rivestment level " + std::to_wstring(level));
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));

				//Set alphabet
				alphabet = ALPHABET;
				bot->post_message(L"Current Alphabet: " + string_to_wstring(alphabet));
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));

				//Generate Map
				bot->post_message(L"Generating Lookup Tables");
				generateMap();
				bot->post_message(L"Lookup Tables Generated");
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));

				//Fetch Current Point Total
				bot->post_message(L"rivestment points");
				while (!points) {
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}

				//Call For Challenges
				lastRunTime = time(0);
				bot->post_message(L"rivestment challenge " + std::to_wstring(findRange(level, points)));
				return (L" `begin` complete");
			}
			else if (inGame == false) {
				return (L"Not currently registered in Rivestment. Register by inputting 'mcbot rivestment begin'");
			}
			else if (command_text == L"lvlup") {
				autoLvl = false;
				if (level >= 7) {
					return (L"Highest possible level is 7");
				}
				else {
					//reset command
					if (mapLevel >= level + LEVEL_RANGE) {
						
						level++;
						bot->post_message(L"rivestment level " + std::to_wstring(level));

						//Generate Map
						bot->post_message(L"Generating Lookup Tables");
						generateMap();
						bot->post_message(L"Lookup Tables Generated");
						std::this_thread::sleep_for(std::chrono::milliseconds(2000));

						//Fetch Current Point Total
						bot->post_message(L"rivestment points");
						while (!points) {
							std::this_thread::sleep_for(std::chrono::milliseconds(10));
						}

						//Call For Challenges
						lastRunTime = time(0);
					}
					return (L"rivestment challenge " + std::to_wstring(findRange(level, points)));
				}
			}
			else if (command_text == L"lvldown") {
				autoLvl = false;
				if (level <= 1) {
					return (L"Lowest possible level is 1");
				}
				else {
					//reset command
					return (L"rivestment level " + std::to_wstring(level - 1));
				}
			}
			else if (command_text == L"quit") {
				inGame = false;
				return (L"rivestment quit");
			}
			//Invalid Command
			else {
				return (L"Invalid Command");
			}
		}

		//Shared Pointer Definition
		private:
			std::shared_ptr<Matterbot> bot;
	};
}
