#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include "RivestmentPrompts.h"
#include "Rivestment.h"

#define HASHCOST 5

namespace lospi
{
	struct RivestmentResponses : ICommand {
		explicit RivestmentResponses(std::shared_ptr<Matterbot> bot) : bot{ bot } { }
		std::wstring get_name() override {
			return L"mcbot";
		}

		std::wstring get_help() override {
			return L"mcbot";
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {

			if (user != L"rivestment") {
				return (L"You are not allowed McBot use.");
			}
			
			else if (command_text == L"password") {
				password = command_text;
				return (L"Password Set");
			}

			else if (command_text.find(L"points")) {
				std::wstring str = command_text, temp;
				std::vector<std::wstring> parts;
				std::wstringstream wss(str);
				while (std::getline(wss, temp, L' '))
					parts.push_back(temp);

				points = stoi(command_text);
				return (L"Points Updated");
			}

			else if (command_text == L"challenges" || command_text == L"scraps") {
				findHash(parseInput(command_text));

			}

			else {
				return (L"Invalid Input.");
			}
		}
		private:
			std::shared_ptr<Matterbot> bot;
	};
}
