/*
 * messagebox.cpp
 *
 *  Created on: Dec 19, 2016
 *      Author: Sanjay Kumar
 */

#include "messagebox.h"
#include  <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace Game {

	void MessageBox::setEmoji(Player player) {
		sf::Texture texture;
		switch(player) {
			case Player::COMPUTER: {
				if(texture.loadFromFile("resources/sad.jpg")) {
					mBackground.setTexture(texture);
				}
			}
			break;
			case Player::HUMAN: {
				if(texture.loadFromFile("resources/smiley.png")) {
					mBackground.setTexture(texture);
				}
			}
			break;
			case Player::NONE: {
				if(texture.loadFromFile("resources/straightface.jpg")) {
					mBackground.setTexture(texture);
				}
			}
			break;
		}
	}
	void MessageBox::display() {
		sf::Font font;
		font.loadFromFile("c:/windows/fonts/arial.ttf");
		mText.setFont(font);
		// set the character size
		mText.setCharacterSize(24); // in pixels, not points!
		// set the color
		mText.setColor(sf::Color::Black);
		// set the text style
		mText.setStyle(sf::Text::Bold);



		while (mWindow.isOpen()) {
			sf::Event event;
			while(mWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed){
					mWindow.close();
					break;
				}

			}
			mWindow.clear(sf::Color::White);
			mWindow.draw(mText);
			mWindow.display();
		}
	}

}
