//#include "Matterbot.h"
//#define NUM_ROWS 3
//#define NUM_COLS 3
//
//namespace lospi
//{
//	struct tictactoe_game {
//		std::wstring player1;
//		std::wstring player2;
//		std::wstring activePlayer;
//		int numberMoves = 9;
//		std::wstring gameBoard[NUM_COLS * NUM_ROWS];
//	};
//
//	tictactoe_game g;
//
//	struct tictactoe : ICommand {
//		std::wstring get_name() override {
//			return L"tictactoe";
//		}
//
//		std::wstring get_help() override {
//			return L"`tictactoe [CMD]`:\n\t`start`: Accepts a username to play Tic Tac Toe with.\n\t`turn`: Accepts a number corresponding to a board piece to place\n\t`quit game`: Accepts a username to quit against\n";
//		}
//		std::wstring handle_command(const std::wstring &team, const std::wstring &channel,
//			const std::wstring &user, const std::wstring &command_text) override {
//			std::wstring output;
//
//			if (command_text == L"quit" && (user == g.player1 || user == g.player2)) {
//				if (user == g.player1) {
//					output = g.player2 + L" Wins!";
//				}
//				else {
//					output = g.player1 + L" Wins!";
//				}
//				g = {};
//			}
//			else if (command_text == (L"start")) {
//				if (g.player1.size() == 0) {
//					g.player1 = user;
//					g.activePlayer = user;
//					output = (g.player1 + L" has joined the game.");
//				}
//				else if (g.player2.size() == 0) {
//					g.player2 = user;
//					output = (g.player2 + L" has joined the game. " + g.player1 + L" take your turn.\n");
//					output += display_board(g);
//				}
//			}
//			else {
//				if (user != g.activePlayer) {
//					output = L"Invalid User.";
//				}
//				else if (command_text == L"1" || command_text == L"2" || command_text == L"3" || command_text == L"4" || command_text == L"5" || command_text == L"6" || command_text == L"7" || command_text == L"8" || command_text == L"9") {
//					if (g.gameBoard[std::stoi(command_text)].size() > 0) {
//						output += L"This space has been taken.";
//					}
//					else {
//						g.gameBoard[std::stoi(command_text)] = g.activePlayer;
//						g.numberMoves--;
//						output += display_board(g);
//						if (winCheck(g).size() > 0) {
//							output += winCheck(g);
//						}
//						else {
//							if (g.activePlayer == g.player1) {
//								g.activePlayer = g.player2;
//							}
//							else {
//								g.activePlayer = g.player1;
//							}
//
//						}
//					}
//
//				}
//				else {
//					output = L"Invalid Command.";
//				}
//			}
//			return output;
//		}
//
//		std::wstring display_board(tictactoe_game& g) {
//			std::wstring output;
//			output = (g.player1 + L" vs. " + g.player2 + L":\n");
//			for (int row = 0; row < NUM_ROWS; row++) {
//				output += L"\t";
//				for (int col = 0; col < NUM_COLS; col++) {
//					if (g.gameBoard[col + (row * NUM_COLS) + 1] == g.player1) {
//						output += L"[ ```X ]";
//					}
//					else if (g.gameBoard[col + (row * NUM_COLS) + 1] == g.player2) {
//						output += L"[ ```O ]";
//					}
//					else {
//						output += L"[ ```" + std::to_wstring(col + (row * NUM_COLS) + 1) + L" ]";
//					}
//				}
//				output += L"\n";
//			}
//			return (output);
//		}
//
//		std::wstring winCheck(tictactoe_game& g) {
//			std::wstring output;
//			for (int i = 1; i < NUM_COLS; i++) {
//				//check vertical
//				if ((g.gameBoard[i] == g.gameBoard[i + 3] && g.gameBoard[i] == g.gameBoard[i + 6]) && (g.gameBoard[i].size() > 0)) {
//					g.numberMoves = 0;
//					output += g.gameBoard[i] + (L" IS THE WINNER!!!!!!\n");
//					display_board(g);
//					break;
//				}
//				//check horizonal
//				else if ((g.gameBoard[i] == g.gameBoard[i + 1] && g.gameBoard[i] == g.gameBoard[i + 2] && i % 3 == 1) && g.gameBoard[i].size() > 0) {
//					g.numberMoves = 0;
//					output += g.gameBoard[i] + (L" IS THE WINNER!!!!!!\n");
//					display_board(g);
//					break;
//				}
//				//check diagonal
//				else if (((g.gameBoard[1] == g.gameBoard[5] && g.gameBoard[1] == g.gameBoard[9]) || (g.gameBoard[3] == g.gameBoard[5] && g.gameBoard[3] == g.gameBoard[7])) && g.gameBoard[5].size() > 0) {
//					g.numberMoves = 0;
//					output += g.gameBoard[5] + (L" IS THE WINNER!!!!!!\n");
//					display_board(g);
//					break;
//				}
//				//cats game
//				else if (g.numberMoves == 0 && i == NUM_COLS - 1) {
//					display_board(g);
//					output += (L"THERE IS NO WINNER!!!!!!!!!!\n");
//				}
//			}
//			return output;
//		}
//
//	};
//}