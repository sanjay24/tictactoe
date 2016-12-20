/*
 * Board.cpp
 *
 *  Created on: Dec 2, 2016
 *      Author: Sanjay Kumar
 */
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "gamestrategy.h"
#include "utility.h"
#include "messagebox.h"

#include <iostream>
#include "Board.h"

namespace Game {
	Board::Board():	mDisplayWindow(sf::VideoMode(600,
		600), "Tic-Tac-Toe", sf::Style::Close) {
		mGridHeight = 3 * mWidthHeight;
		mGridWidth = mGridHeight;
	}

	void Board::getGridLines(sf::Vertex lines[]) {
		lines[0] = sf::Vertex(sf::Vector2f (mWidthHeight, 0));
		lines[1] = sf::Vertex(sf::Vector2f (mWidthHeight, mGridHeight)); // columnar line 1

		lines[2] = sf::Vertex(sf::Vector2f (mWidthHeight * 2, 0));
		lines[3] = sf::Vertex(sf::Vector2f (mWidthHeight * 2, mGridHeight)); // columnar line 2

		lines[4] = sf::Vertex(sf::Vector2f (0, mWidthHeight));
		lines[5] = sf::Vertex(sf::Vector2f (mGridWidth, mWidthHeight)); // row line 1

		lines[6] = sf::Vertex(sf::Vector2f (0, mWidthHeight * 2));
		lines[7] = sf::Vertex(sf::Vector2f (mGridWidth, mWidthHeight * 2)); // row line 2
	}

	void Board::play() {
		// Lets create the grid
		sf::Vertex lines[8];
		getGridLines(lines);
		Player player = Player::HUMAN;
		sf::String message;
		sf::Text text;
		sf::Font font;

		if(!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
			std::cout<<"failed to load the font"<<std::endl;
			exit(1);
		}

		Player winningPlayer = Player::COMPUTER;
		bool isGameOver = false;
		while (mDisplayWindow.isOpen()) {

			// this state will be changed by player
			mGameState.setPlayer(player);
		   //manage the events
			sf::Event event;
			//processEvents(event);
			std::pair<int,int> cellId = std::make_pair(-1, -1);

			while(!isGameOver && mDisplayWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed){
					mDisplayWindow.close();
					break;
				} else if (event.type == sf::Event::MouseButtonPressed) {
					if (player == Player::HUMAN) {
						cellId.first = -1;
						cellId.second = -1;
						cellId = playerMove(event);
						if (!mGameState.isCellEmpty(cellId.first, cellId.second)) {
							// this cell is already occupied. Invalidate input
							cellId.first = -1;
							cellId.second = -1;
						}
					}
				} else {
					if (player == Player::COMPUTER) { //next is computer's move
						cellId.first = -1;
						cellId.second = -1;
						cellId = GameStrategy::instance()->getNextMove(mGameState);
					}
				}
			} //event processed

			if (cellId.first != -1 && cellId.second != -1) {
				renderMove(player, cellId);
				// update the board state
				mGameState.setBoardCell(cellId.first, cellId.second, player);
				mGameState.setPlayer(player);

				if (mGameState.isWinningState()) {
					message = player == Player::COMPUTER? "You Loose!": "You Win!";
					std::string debug = player == Player::COMPUTER? "Computer Wins!": "You Win!";
					//atext.setFont();
					text.setString(message);
					text.setCharacterSize(20);
					text.setStyle(sf::Text::Bold);
					text.setColor(sf::Color::Black);
					text.setPosition(100,100);
					debug_print(debug);
					isGameOver = true;
					std::cout<<debug<<std::endl;
					winningPlayer = player;

				} else if (mGameState.getEmptyCells().empty()) {
					message = "Its a tie!!!";
					std::cout<<"ITS A TIE"<<std::endl;
					text.setString(message);
					debug_print("ITS A TIE\n");
					isGameOver = true;
					winningPlayer = Player::NONE;
				}
				player = player == Player::COMPUTER? Player::HUMAN: Player::COMPUTER;

			}

			mDisplayWindow.clear(sf::Color::Blue);
			mDisplayWindow.draw(lines, 8, sf::Lines);
			for(size_t indx = 0; indx < mRenderedShapes.size(); ++indx ) {
				mDisplayWindow.draw(*mRenderedShapes[indx]);
			}


			text.setPosition(10.0f, 10.0f);

			mDisplayWindow.draw(text);
			mDisplayWindow.display(); //display the result on screen
			if(isGameOver) {
				std::cout<<"GAME OVER!"<<std::endl;
				MessageBox box;
				//box.setEmoji(winningPlayer);
				box.setText(message);
				box.display();
				break;
			}

		} // window open
	}

	void Board::processEvents(sf::Event& event) {
		while(mDisplayWindow.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					mDisplayWindow.close();
					break;
			}
		}
	}


	std::pair<int, int> Board::playerMove(sf::Event& event) {
		std::pair<int, int> cellId = std::make_pair(-1, -1);
		switch (event.type) {
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					cellId = toCellId(event.mouseButton.x, event.mouseButton.y);
				}
			break;
		}
		return cellId;
	}

	void Board::renderMove(Player player, std::pair<int, int> cellId) {
		debug_print("RENDERING FOR PLAYER [%d] at [%d, %d]\n", player,cellId.first, cellId.second);
		switch (player) {
			case Player::HUMAN:	{
				int radius = 40;
				//sf::CircleShape circle = sf::CircleShape(radius);
				sf::Shape* circle = new sf::CircleShape(radius);
				mRenderedShapes.push_back(circle);
				circle->setFillColor(sf::Color::White);
				circle->setPosition(cellId.second * mWidthHeight + (mWidthHeight/2 -  radius),
				cellId.first * mWidthHeight + (mWidthHeight/2 - radius));
				mRenderedShapes.push_back(circle);
				mDisplayWindow.draw(*circle);
			}

			break;
			case Player::COMPUTER: {
				int radius = 40;
				sf::Shape* triangle = new sf::CircleShape(radius, 3);
				triangle->setFillColor(sf::Color::Yellow);
				triangle->setPosition(cellId.second * mWidthHeight + (mWidthHeight/2 -  radius),
				cellId.first * mWidthHeight + (mWidthHeight/2 - radius));
				mRenderedShapes.push_back(triangle);
				mDisplayWindow.draw(*triangle);
			}
			break;
		}

	}

	std::pair<int, int> Board::toCellId(int x, int y) {
		return std::make_pair(y/mWidthHeight, x/mWidthHeight);
	}
}

