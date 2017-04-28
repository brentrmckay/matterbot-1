#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Rivestment.h"

namespace lospi
{
	struct getpoints : ICommand {
		std::wstring get_name() override {
			return L"points";
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
					return (L"");
				}

				else {
					points = std::stoi(command_text);
					pointTotals.emplace(level, points);
					return (L"");
				}
			}
		}
	};
}
