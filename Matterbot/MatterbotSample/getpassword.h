#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include "RivestmentPrompts.h"
#include "Rivestment.h"

#define HASHCOST 5

namespace lospi
{
	struct getpassword : ICommand {
		std::wstring get_name() override {
			return L"password";
		}

		std::wstring get_help() override {
			return L"password";
		}

		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
			const std::wstring &user, const std::wstring &command_text) override {

			if (user != L"rivestment") {
				return (L"");
			}

			else {
				password = command_text;
				return (L"");
			}
		}
	};
}
