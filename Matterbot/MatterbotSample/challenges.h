#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include "RivestmentPrompts.h"
#include "Rivestment.h"

#define HASHCOST 5

namespace lospi
{
	struct challenges : ICommand {
		explicit challenges(std::shared_ptr<Matterbot> bot) : bot{ bot } { }
		std::wstring get_name() override {
			return L"challenges";
		}

		std::wstring get_help() override {
			return L"challenges";
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {

			if (user != L"rivestment") {
			}

			else {
				bot->post_message(findHash(parseInput(command_text)));
			}
			return (L"rivestment scraps");
		}
	private:
		std::shared_ptr<Matterbot> bot;
	};
}
