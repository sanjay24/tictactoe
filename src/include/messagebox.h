/*
 * messagebox.h
 *
 *  Created on: Dec 19, 2016
 *      Author: Sanjay Kumar
 */

#ifndef MESSAGEBOX_H_
#define MESSAGEBOX_H_

#include "constants.h"
#include "gamestate.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <vector>

namespace Game {
	class MessageBox {
		public:
			MessageBox(): mWindow(sf::VideoMode(300,
					100), "Result!" /*sf::Style::Close*/){}
			void setText(std::string message) {
				mText.setString(message.c_str());
			}
			void display();
			void setTitle(std::string title) {
				mWindow.setTitle(title);
			}

			void setEmoji(Player player);
		private:
			sf::Text mText;
			sf::RenderWindow mWindow;
			sf::Sprite mBackground;
			//std::vector<sf::Texture
	};
}

#endif /* MESSAGEBOX_H_ */
