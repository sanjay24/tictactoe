/*
 * gamestate.cpp
 *
 *  Created on: Dec 9, 2016
 *      Author: Sanjay Kumar
 */
#include "gamestate.h"

namespace Game {

	GameState::GameState(): mScore(0) {
		mState.resize(ROW_SIZE * COL_SIZE);
		std::size_t maxElems = ROW_SIZE * COL_SIZE;
		for(std::size_t indx = 0; indx < maxElems;  ++indx) {
			mState[indx] = Player::NONE;
		}
	}

	bool GameState::operator==(const GameState& rhs) const{
		bool isEqual = true;
		if (this->mPlayer != rhs.mPlayer) {
			isEqual = false;
			return isEqual;
		}

		for(std::size_t indx = 0; indx < mState.size(); ++indx) {
			if (mState[indx] != rhs.mState[indx]) {
				isEqual = false;
				break;
			}
		}
		return isEqual;
	}

	bool GameState::isWinningState() {
		bool isWinning = false;
		// check rows
		if (mPlayer == mState[0] && mState[0] == mState[1] &&	mState[0] == mState[2] ) {
			isWinning = true;
		} else if (mPlayer == mState[3] && mState[3] == mState[4] &&	mState[4] == mState[5] ) {
			isWinning = true;
		} else if (mPlayer == mState[6] && mState[6] == mState[7] &&	mState[7] == mState[8] ) {
			isWinning = true;
		}

		// check cols
		if (mPlayer == mState[0] && mState[0] == mState[3] &&	mState[3] == mState[6] ) {
			isWinning = true;
		} else if (mPlayer == mState[1] && mState[1] == mState[4] &&	mState[4] == mState[7] ) {
			isWinning = true;
		} else if (mPlayer == mState[2] && mState[5] == mState[2] &&	mState[5] == mState[8] ) {
			isWinning = true;
		}

		// check diagonals
		if (mPlayer == mState[0] && mState[0] == mState[4] &&	mState[4] == mState[8] ) {
			isWinning = true;
		} else if (mPlayer == mState[2] && mState[2] == mState[4] &&	mState[4] == mState[6] ) {
			isWinning = true;
		}

		return isWinning;
	}

	std::vector< std::pair<int, int> > GameState::getEmptyCells() const {
		std::vector< std::pair<int, int> > emptyCells;
		for(std::size_t indx = 0;  indx < mState.size(); ++indx) {
			if (mState[indx] == Player::NONE) {
				emptyCells.push_back(std::make_pair(indx/ROW_SIZE, indx%COL_SIZE));
			}
		}
		return emptyCells;
	}
}
