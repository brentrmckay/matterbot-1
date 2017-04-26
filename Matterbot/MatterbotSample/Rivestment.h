#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include <map>
#include <chrono>
#include <thread>
#include <sstream>
#include <iterator> 
#include <algorithm>
#include <string>
#define SLACK_MAX 4000

namespace lospi {

	//Global Variables
	std::map<std::string, std::string> hash_map;
	std::wstring password;
	std::wstring userName;
	std::string alphabet;
	unsigned int range;
	unsigned int level;
	unsigned int points;

	void generateMap(void) {
		for (int i = level; i <= (level + 10); i++) {
			auto c = Combinator(alphabet, i);
			while (c.has_next()) {
				auto fullPassword = c.next();
				for (auto x : password) {
					fullPassword.emplace_back(x);
				}
				//Optimize how hashes are stored
				std::string fullPasswordStr(fullPassword.data(), i + password.size());
				hash_map.emplace(wstring_to_string(get_str_from_md5(compute_md5(&fullPassword[0], fullPassword.size()))), fullPasswordStr);
			}
		}
	}

	std::vector<std::string> parseInput(const std::wstring command_text) {
		std::string s = wstring_to_string(command_text);
		std::stringstream ss(s);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> vstrings(begin, end);
		return vstrings;
	}

	std::wstring findHash(std::vector<std::string> vstrings) {
		std::wstring output = L"rivestment try";
		//optimize how hashes are stored
		for (const auto& element : vstrings) {
			auto result = hash_map.find(element);
			if (result == hash_map.end()) {
				//No result found
			}
			else if ((output + L" " + string_to_wstring(result->second)).size() > SLACK_MAX) {
				//Output is about to be too long. Break loop and return current.
				break;
			}
			else {
				output += L" " + string_to_wstring(result->second);
			}		
		}
		return output;
	}
}