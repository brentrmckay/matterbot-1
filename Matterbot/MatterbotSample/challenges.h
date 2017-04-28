#pragma once
#include "Matterbot.h"
#include "Rivestment.h"
#include <thread>

namespace lospi
{
	struct challenges : ICommand {
		explicit challenges(std::shared_ptr<Matterbot> bot) : bot{ bot } { }
		std::wstring get_name() override {
			return L"challenges";
		}
		std::wstring get_help() override {
			return L"";
		}
		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {
			if (inGame == false) {
				return (L"Not currently registered in Rivestment. Enter by inputting 'mcbot rivestment begin'");
			}
			else {
				if (user != L"rivestment") {
					return L"";
				}
				else {
					lastRunTime = time(0);
					bot->post_message(L"rivestment try" + findHash(parseInput(command_text)));
					std::this_thread::sleep_for(std::chrono::milliseconds(2000));
					bot->post_message(L"rivestment points");
					std::this_thread::sleep_for(std::chrono::milliseconds(2000));
					bot->post_message(L"rivestment scraps");
					return (L"");
				}
			}
		}
	private:
		std::shared_ptr<Matterbot> bot;
	};
}
