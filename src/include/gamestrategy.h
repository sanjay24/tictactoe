/*
 * gamestrategy.h
 *
 *  Created on: Dec 8, 2016
 *      Author: Sanjay Kumar
 */

#ifndef GAMESTRATEGY_H_
#define GAMESTRATEGY_H_

#include "gamestate.h"
#include <vector>

namespace Game {
	class GameStrategy {
		public:
			static GameStrategy* instance();
			std::vector<GameState> generateStates(const GameState& rootState, Player payer);
			// Computer's next move
			std::pair<int, int> getNextMove(GameState& rootState);

			void setStrategy(Strategy strategy) {
				mStrategy = strategy;
			}

			void setExpertLevel(GameExpertLevel level) {
				mExpertLevel = level;
			}

			typedef struct ScoreWithPos{
				int score;
				std::pair<int, int> cellId;
				ScoreWithPos(): score(0) {
					cellId = std::make_pair(-1, -1);
				}
				ScoreWithPos& operator=(const ScoreWithPos& arg) {
					if (this == &arg) return *this;
					this->score = arg.score;
					this->cellId = arg.cellId;
					return *this;
				}
			} Score_t;

		private:
			GameStrategy() : mStrategy(Strategy::RANDOM_MOVE), mExpertLevel(GameExpertLevel::EXPERT) {}
			GameStrategy& operator=(const GameStrategy);

			Score_t minMaxTree(GameState gameState, Player player, int level);

			static GameStrategy* mInstance;
			Strategy mStrategy;
			GameExpertLevel mExpertLevel;

	};
}

#endif /* GAMESTRATEGY_H_ */
