/*
 * main.cpp
 *
 *  Created on: Dec 3, 2016
 *      Author: Sanjay Kumar
 */

#include <iostream>
#include <Board.h>
#include "gamestrategy.h"
#include "messagebox.h"
using namespace std;
using namespace Game;

int main() {
#if 0
	MessageBox box;
	box.setEmoji(Player::NONE);
	box.setTitle("Test");
	box.setText("You Win!!");
	box.display();
#endif
#if 1 // main logic
	Board board;
	cout<<"Starting the board with state"<<endl;
	GameStrategy::instance()->setStrategy(Strategy::BEST_MOVE);
	GameStrategy::instance()->setExpertLevel(GameExpertLevel::EXPERT);
	board.play();
#endif
#if 0 // usecase 1
	GameState st;

	cout<<"==============="<<endl;
	for(int i=0; i<ROW_SIZE; ++i) {
		for(int j=0; j<COL_SIZE; ++j) {
			cout<<st.getBoardCell(i, j)<<" ";
		}
		cout<<endl;
	}


	vector<GameState> states = GameStrategy::instance()->generateStates(st, Player::COMPUTER);
	cout<<"Total states obtained = "<<states.size()<<endl;
	for(auto v: states) {
		cout<<"==============="<<endl;
		for(int i=0; i<ROW_SIZE; ++i) {
			for(int j=0; j<COL_SIZE; ++j) {
				cout<<v.getBoardCell(i, j)<<" ";
			}
			cout<<endl;
		}
	}

	GameState win;
	win.setPlayer(Player::COMPUTER);
	win.setBoardCell(0, 0, Player::COMPUTER);
	win.setBoardCell(1, 1, Player::COMPUTER);
	win.setBoardCell(2, 2, Player::COMPUTER);

	if (win.isWinningState()) {
		cout<<"its a win by "<<win.getPlayer()<<endl;
	} else {
		cout<<"its not a win by "<<win.getPlayer()<<endl;
	}
#endif

#if 0  // usecase 2
	std::cout<<"TESTING THE BOARD FOR NEXT MOVE"<<std::endl;
	GameState gs;
	gs.setPlayer(Player::HUMAN);
	gs.setBoardCell(0, 0, Player::NONE);
	gs.setBoardCell(0, 1, Player::COMPUTER);
	gs.setBoardCell(0, 2, Player::HUMAN);

	gs.setBoardCell(1, 0, Player::NONE);
	gs.setBoardCell(1, 1, Player::HUMAN);
	gs.setBoardCell(1, 2, Player::NONE);

	gs.setBoardCell(2, 0, Player::NONE);
	gs.setBoardCell(2, 1, Player::NONE);
	gs.setBoardCell(2, 2, Player::NONE);

	GameStrategy::instance()->setStrategy(Strategy::BEST_MOVE);
	std::pair<int, int> nm = GameStrategy::instance()->getNextMove(gs);

	std::cout<<"@@@@@@@@@@@@@@@@@@@@@"<<std::endl;
	gs.displayBoard();

	std::cout<<"Next move is "<<nm.first<<", "<<nm.second<<std::endl;
#endif

#if 0  // usecase 3
	std::cout<<"TESTING THE BOARD FOR NEXT MOVE"<<std::endl;
	GameState gs;
	gs.setPlayer(Player::HUMAN);
	gs.setBoardCell(0, 0, Player::COMPUTER);
	gs.setBoardCell(0, 1, Player::NONE);
	gs.setBoardCell(0, 2, Player::HUMAN);

	gs.setBoardCell(1, 0, Player::NONE);
	gs.setBoardCell(1, 1, Player::HUMAN);
	gs.setBoardCell(1, 2, Player::NONE);

	gs.setBoardCell(2, 0, Player::NONE);
	gs.setBoardCell(2, 1, Player::NONE);
	gs.setBoardCell(2, 2, Player::NONE);

	GameStrategy::instance()->setStrategy(Strategy::BEST_MOVE);
	std::pair<int, int> nm = GameStrategy::instance()->getNextMove(gs);

	std::cout<<"@@@@@@@@@@@@@@@@@@@@@"<<std::endl;
	gs.displayBoard();

	std::cout<<"Next move is "<<nm.first<<", "<<nm.second<<std::endl;
#endif

#if 0 // usecase 4
	std::cout<<"TESTING THE BOARD FOR NEXT MOVE"<<std::endl;
	GameState gs;
	gs.setPlayer(Player::HUMAN);
	gs.setBoardCell(0, 0, Player::COMPUTER);
	gs.setBoardCell(0, 1, Player::NONE);
	gs.setBoardCell(0, 2, Player::HUMAN);

	gs.setBoardCell(1, 0, Player::HUMAN);
	gs.setBoardCell(1, 1, Player::COMPUTER);
	gs.setBoardCell(1, 2, Player::NONE);

	gs.setBoardCell(2, 0, Player::HUMAN);
	gs.setBoardCell(2, 1, Player::NONE);
	gs.setBoardCell(2, 2, Player::NONE);

	GameStrategy::instance()->setStrategy(Strategy::BEST_MOVE);
	std::pair<int, int> nm = GameStrategy::instance()->getNextMove(gs);

	std::cout<<"@@@@@@@@@@@@@@@@@@@@@"<<std::endl;
	gs.displayBoard();

	std::cout<<"Next move is "<<nm.first<<", "<<nm.second<<std::endl;
#endif

#if 0
	std::cout<<"TESTING THE BOARD FOR NEXT MOVE"<<std::endl;
	GameState gs;
	gs.setPlayer(Player::HUMAN);
	gs.setBoardCell(0, 0, Player::COMPUTER);
	gs.setBoardCell(0, 1, Player::NONE);
	gs.setBoardCell(0, 2, Player::NONE);

	gs.setBoardCell(1, 0, Player::HUMAN);
	gs.setBoardCell(1, 1, Player::COMPUTER);
	gs.setBoardCell(1, 2, Player::NONE);

	gs.setBoardCell(2, 0, Player::HUMAN);
	gs.setBoardCell(2, 1, Player::NONE);
	gs.setBoardCell(2, 2, Player::HUMAN);

	GameStrategy::instance()->setStrategy(Strategy::BEST_MOVE);
	std::pair<int, int> nm = GameStrategy::instance()->getNextMove(gs);

	std::cout<<"@@@@@@@@@@@@@@@@@@@@@"<<std::endl;
	gs.displayBoard();

	std::cout<<"Next move is "<<nm.first<<", "<<nm.second<<std::endl;
#endif

#if 0 // usecase 5
	std::cout<<"TESTING THE BOARD FOR NEXT MOVE"<<std::endl;
	GameState gs;
	gs.setPlayer(Player::HUMAN);
	gs.setBoardCell(0, 0, Player::COMPUTER);
	gs.setBoardCell(0, 1, Player::NONE);
	gs.setBoardCell(0, 2, Player::NONE);

	gs.setBoardCell(1, 0, Player::HUMAN);
	gs.setBoardCell(1, 1, Player::COMPUTER);
	gs.setBoardCell(1, 2, Player::NONE);

	gs.setBoardCell(2, 0, Player::HUMAN);
	gs.setBoardCell(2, 1, Player::NONE);
	gs.setBoardCell(2, 2, Player::HUMAN);

	GameStrategy::instance()->setStrategy(Strategy::BEST_MOVE);
	std::pair<int, int> nm = GameStrategy::instance()->getNextMove(gs);

	std::cout<<"@@@@@@@@@@@@@@@@@@@@@"<<std::endl;
	gs.displayBoard();

	std::cout<<"Next move is "<<nm.first<<", "<<nm.second<<std::endl;
#endif
}
