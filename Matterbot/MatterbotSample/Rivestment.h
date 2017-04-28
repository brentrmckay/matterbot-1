#pragma once
#include "Matterbot.h"
#include "Md5.h"
#include "Md5Utilities.h"
#include <chrono>
#include <map>
#include <sstream>
#include <string>
#define ALPHABET "josh"
#define HASH_COST 5
#define LEVEL_RANGE 10
#define MAX_LEVEL 7
#define MAX_RANGE 100
#define MD5DIGEST_LENGTH 32
#define SLACK_MAX 4000
#define STARTING_LVL 5

namespace lospi {

	//Global Variables
	std::map<uint64_t, uint64_t> hashMap;
	std::wstring password;
	std::wstring userName;
	std::string alphabet;
	int level;
	int mapLevel;
	std::map<int, uint64_t> mapSize;
			 //level, size
	std::map<int, int> pointTotals;
			 //level, points
	int points;
	time_t lastRunTime;
	bool autoLvl;
	bool inGame;

	uint64_t to_tiny_val(std::string &digest);
	std::string from_tiny_val(uint64_t myInt);

	void generateMap() {
		inGame = false;
		for (int i = mapLevel; i < (level + LEVEL_RANGE); i++) {
			auto c = Combinator(alphabet, i);
			while (c.has_next()) {
				auto fullPassword = c.next();
				std::string uniquePasswordStr(fullPassword.data(), i);
				for (auto x : password) {
					fullPassword.emplace_back(x);
				}
				//MD5 Cut in Half
				Md5Digest m = compute_md5(&fullPassword[0], fullPassword.size());
				uint64_t y = *(uint64_t*)&m[0];
				
				//Hash converted to 32bit int
				auto z = to_tiny_val(uniquePasswordStr);
				hashMap.emplace(y, z);

				//Map Sizing
				auto size = mapSize.find(i);
				if (size == mapSize.end()) {
					mapSize.emplace(i, hashMap.size());
				}
				else {
					size->second = hashMap.size();
				}
			}
			mapLevel++;
		}
		inGame = true;
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
		std::wstring output;
		//optimize how hashes are stored
		for (const auto& element : vstrings) {

			auto x = get_md5_from_str(string_to_wstring(element));
			uint64_t n = *(uint64_t*)&x[0];

			auto result = hashMap.find(n);

			//Hash converted to 32bit int
			std::wstring b = string_to_wstring(from_tiny_val(result->second));

			if (result == hashMap.end()) {
				//No result found
			}
			else if ((output + L" " + b).size() > SLACK_MAX) {
				//Output is about to be too long. Break loop and return current output.
				break;
			}
			else {
				output += L" " + b + password;
			}		
		}
		return output;
	}

	int findRange(int level, int points) {
		return std::min(int((SLACK_MAX - (userName.length() + std::string("rivestment").length() + 1)) / (MD5DIGEST_LENGTH + 1)), points / HASH_COST);
	}

	uint64_t to_tiny_val(std::string &digest) {
		std::map<char, char> hexmap = { { 'h', 0x1 },{ 's', 0x2 },{ 'o', 0x3 },{ 'j', 0x4 } };

		uint64_t myVal = 0x0;

		for (int i = 0; i <digest.size(); i++) {
			myVal <<= 3;
			myVal |= hexmap[digest[i]];
		}
		return myVal;
	}

	std::string from_tiny_val(uint64_t myInt) {

		std::map<char, char> hexmap = { { 0x0, 0x0 },{ 0x1, 'h' },{ 0x2, 's' },{ 0x3, 'o' },{ 0x4, 'j' } };

		std::string myVal;

		for (int i = 0; i < sizeof(uint64_t) * 4; i++) {
			if (hexmap[myInt & 0x7] != 0x0) {
				myVal += hexmap[myInt & 0x7];
			}
			myInt >>= 3;
		}
		reverse(myVal.begin(), myVal.end());
		return myVal;
	}
}