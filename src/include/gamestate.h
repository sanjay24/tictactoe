/*
 * gamestate.h
 *
 *  Created on: Dec 8, 2016
 *      Author: Sanjay Kumar
 */

#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <assert.h>
#include <vector>
#include "constants.h"
#include <iostream>
#include "utility.h"
namespace Game {
	class GameState {
		public:
			GameState();
			GameState(std::vector<Player>& state, Player player, int score):
				mState(state), mScore(score), mPlayer(player){
			}
			GameState(const GameState& rhs) {
				mState = rhs.mState;
				mScore = rhs.mScore;
				mPlayer = rhs.mPlayer;
			}
			bool operator==(const GameState& rhs) const;

			//const std::vector<Player> getStateRep() const;
			std::vector<Player>& getStateRep() { return mState; }
			std::vector< std::pair<int, int> > getEmptyCells() const;
			void setStateRep(std::vector<Player>& state) {
				mState = state;
			}

			Player getPlayer() const { return mPlayer; }
			void setPlayer(Player player) { mPlayer = player;}

			int getScore() const {return mScore;}
			void setScore(int score) { mScore = score; }

			void setBoardCell(int row, int col, Player player) {
				assert (row >= 0 && row < ROW_SIZE &&
						col >= 0 && col < COL_SIZE);
				mState[ROW_SIZE * row + col] = player;
			}

			Player getBoardCell(int row, int col) const {
				return mState[ROW_SIZE * row + col];
			}

			bool isCellEmpty(int row, int col) const {
				return mState[ROW_SIZE * row +  col] == Player::NONE;
			}
			bool isWinningState();

			void displayBoard() {
				if(DEBUG){
					for(std::size_t indx = 0; indx < mState.size(); ++indx) {
						char c = '-';
						if (Player::COMPUTER == mState[indx]) {
							c = 'X';
						} else if (Player::HUMAN == mState[indx]) {
							c = 'O';
						} else {
							c = '-';
						}
						//c = mState[indx] == Player::COMPUTER? 'X': 'O';
						if (indx%ROW_SIZE == 0) std::cout<<std::endl;
						std::cout<<c<<" ";
					}
				}
			}

		private:
			// tic-tac-toe board with moves
			std::vector<Player> mState;
			int mScore;
			Player mPlayer;
	};
}

#endif /* GAMESTATE_H_ */
