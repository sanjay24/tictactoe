/*
 * Board.h
 *      Author: Sanjay Kumar
 */

#ifndef BOARD_H_
#define BOARD_H_
#include "constants.h"
#include "gamestate.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <vector>

namespace Game {
	class Board {
		public:
			Board();
			void play();

		protected:
			void processEvents(sf::Event& event);
			std::pair<int, int> toCellId(int x, int y);
			std::pair<int, int> playerMove(sf::Event& event);
			void getGridLines(sf::Vertex lines[]);
			void renderMove(Player player, std::pair<int, int> cellId);
			// graphics window
			sf::RenderWindow mDisplayWindow;
			const int mWidthHeight = 200;
			int mGridHeight;
			int mGridWidth;
			// tic-tac-toe board in a row major fashion
			GameState mGameState;
			std::vector<sf::Shape *> mRenderedShapes;
	};
}

#endif /* BOARD_H_ */
