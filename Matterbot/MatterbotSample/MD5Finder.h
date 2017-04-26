//#include "Matterbot.h"
//#include "Md5.h"
//#include "Md5Utilities.h"
//
//namespace lospi
//{
//	struct md5 : ICommand {
//		std::wstring get_name() override {
//			return L"md5";
//		}
//
//		std::wstring get_help() override {
//			return L"`md5 [CMD]`: `md5` Finding MD5 Preimages.";
//		}
//
//		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
//			const std::wstring &user, const std::wstring &command_text) override {
//			if (user != L"rivestment" && user != L"brentmckay") {	
//				return (L"You shall not pass!");
//			}
//			else {
//				return get_str_from_md5(compute_md5(&wstring_to_string(command_text)[0], wstring_to_string(command_text).size()));
//			}
//		}
//	};
//}
