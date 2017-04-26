//#include "Matterbot.h"
//
//namespace lospi
//{
//	struct WeatherCommand : ICommand {
//		std::wstring get_name() override {
//			return L"weather";
//		}
//
//		std::wstring get_help() override {
//			return L"`weather [CMD]`:\n`weather rain`: Make it rain\n`weather sunny`: Make it sunny\n`weather report`: Print current weather";
//		}
//
//		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
//			const std::wstring &user, const std::wstring &command_text) override {
//			return command_text;
//		}
//	};
//}
