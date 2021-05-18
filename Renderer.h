#pragma once

#include <SFML/Graphics.hpp>
#include "math.h"
#include "Fighter.h"

class Renderer {
public:

	Renderer() {
		if (!scoreFont.loadFromFile("arial.ttf")) {
			std::cout << "failed to load!" << std::endl;
		}
	}

	sf::RenderWindow *window;

	void setWindowRef(sf::RenderWindow *windowRef) { window = windowRef; }
	void draw(std::vector<Fighter*> fighters);
	void draw(std::vector<Bullet*> bullets);
	void draw(std::vector<int> scores);

	sf::CircleShape shape;

	sf::Text scoreText;
	sf::Font scoreFont;
};