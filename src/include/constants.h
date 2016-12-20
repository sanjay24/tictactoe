/*
 * constants.h
 *
 *  Created on: Dec 5, 2016
 *      Author: Sanjay Kumar
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

namespace Game {
	const int ROW_SIZE = 3;
	const int COL_SIZE = 3;
	int const MAX_LEVEL = 9;

	enum GameExpertLevel {
		BEGINNER = 2,
		INTERMEDIATE = 4,
		EXPERT = 9
	};
	enum Strategy {
		RANDOM_MOVE,
		BEST_MOVE
	};
	enum Player {
		NONE,
		COMPUTER,
		HUMAN
	};

	//const char* pnames[] = {"NONE", "COMPUTER", "HUMAN"};
}

#endif /* CONSTANTS_H_ */
