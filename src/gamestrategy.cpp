/*
 * gamestrategy.cpp
 *
 *  Created on: Dec 9, 2016
 *      Author: Sanjay Kumar
 */

#include "gamestrategy.h"
#include "utility.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>

namespace Game {

	GameStrategy* GameStrategy::mInstance = nullptr;

	GameStrategy* GameStrategy::instance() {
		if (mInstance == nullptr) {
			mInstance = new GameStrategy();
		}
		return mInstance;
	}
	std::vector<GameState> GameStrategy::generateStates(
			const GameState& rootState, Player player) {

		std::vector<GameState> vRetStates;

		for(int row=0; row<ROW_SIZE; ++row) {
			for(int col=0; col<COL_SIZE; ++col) {
				if (rootState.getBoardCell(row, col) == NONE) {
					GameState newState = rootState;
					newState.setBoardCell(row, col, player);
					vRetStates.push_back(newState);
				}
			}
		}

		return vRetStates;
	}

	std::pair<int, int> GameStrategy::getNextMove(Game::GameState& gameState) {
		std::pair<int, int> cellId = std::make_pair(-1, -1);
		if (mStrategy == Strategy::RANDOM_MOVE) {
			auto emptyCellsVec =  gameState.getEmptyCells();
			debug_print("size of empty cells = %d", emptyCellsVec.size());
			if (!emptyCellsVec.empty()) {
				std::srand (std::time(NULL));
				std::random_shuffle(emptyCellsVec.begin(), emptyCellsVec.end());
				cellId = emptyCellsVec.front();
			}
		} else if (mStrategy == Strategy::BEST_MOVE) {
			GameState currentState = gameState;
			currentState.setPlayer(Player::HUMAN); //current state is owned by human
			int level = 1;
			GameStrategy::Score_t score = minMaxTree(currentState, Player::HUMAN, level);
			cellId = score.cellId;
			debug_print("BEST MOVE FOR CCOMPUTER = %d, %d", cellId.first, cellId.second);
		}

		return cellId;
	}


	GameStrategy::Score_t GameStrategy::minMaxTree(GameState gameState, Player player, int level) {

		auto emptyCells = gameState.getEmptyCells();

		if (level > mExpertLevel) {
			// This level is nutral to both and doesn't
			// maximizes or minimizes to any player's score
			GameStrategy::Score_t noScore;
			noScore.score = 0;
			return noScore;
		}

		GameStrategy::Score_t retValue;

		if (gameState.isWinningState()) {
			debug_print("WINNING Board for player [%d] at level [%d]\n", player, level);
			debug_print("===========================\n");
			gameState.displayBoard();
			debug_print("\n===========================\n");

			if(gameState.getPlayer() == Player::COMPUTER) {
				retValue.score = 10;
				return retValue;
			} else if (gameState.getPlayer() == Player::HUMAN) {
				retValue.score = -10;
				return retValue;
			}
		} else if (emptyCells.empty()) {
			debug_print("EMPTY Board for player [%d] ", player);;
			debug_print("===========================\n");
			gameState.displayBoard();
			debug_print("===========================\n");

			// its a tie
			retValue.score = 0;
			return retValue;
		}
		// toggle the player for next level calculation
		Player newPlayer = gameState.getPlayer() == Player::COMPUTER? Player::HUMAN: Player::COMPUTER;

		std::vector<Score_t> minMaxScore;
		for (std::size_t indx = 0; indx < emptyCells.size(); ++indx) {
			GameState newState = gameState;
			newState.setPlayer(newPlayer);
			newState.setBoardCell(emptyCells[indx].first, emptyCells[indx].second, newPlayer);
			Score_t t = minMaxTree(newState, newPlayer, level+1);
			t.cellId = emptyCells[indx];
			minMaxScore.push_back(t);
		}
		Score_t retData;
		if (/*gameState.getPlayer()*/ newPlayer == Player::COMPUTER) {
			// current state is owned by COMPUTER
			// computer should pick a state that maximizes
			// the score at this level

			debug_print("\nscores at level %d for COMPUTER are ==>\n", level);
			for(int i=0; i<minMaxScore.size(); ++i) {
				debug_print("POS (%d, %d) => ",minMaxScore[i].cellId.first,	minMaxScore[i].cellId.second);
				debug_print("SCORE = %d\n", minMaxScore[i].score);
			}

			auto itr = std::max_element(minMaxScore.begin(), minMaxScore.end(),
					[](const Score_t& lhs, const Score_t& rhs) {
						return lhs.score < rhs.score;
			});
			retData = *itr;
		} else if (/*gameState.getPlayer()*/ newPlayer ==  Player::HUMAN) {
			// current state is owned by HUMAN
			debug_print("\nscores at level %d for HUMAN ARE\n", level);
			for(int i=0; i<minMaxScore.size(); ++i) {

				debug_print("POS (%d, %d) => ",minMaxScore[i].cellId.first,	minMaxScore[i].cellId.second);
				debug_print("SCORE = %d\n", minMaxScore[i].score);
			}
			if (level != 1) {
				auto itr = std::min_element(minMaxScore.begin(),	minMaxScore.end(),
							[](const Score_t& lhs, const Score_t& rhs) {
								return lhs.score < rhs.score;});
				retData = *itr;
			} else if (level == 1) {
				auto itr = std::max_element(minMaxScore.begin(),	minMaxScore.end(),
								[](const Score_t& lhs, const Score_t& rhs) {
									return lhs.score < rhs.score;});
				retData = *itr;
			}
		} else {
			debug_print("INVALID USER FOR CALCULATION");
			assert (false);
		}


		debug_print("=============================\n");
		debug_print("VALUE @ LEVEL[%d] \n", retData.score);
		debug_print("=============================\n");

		return retData;
	}

}
