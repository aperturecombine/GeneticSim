#include "Renderer.h"

void Renderer::draw(std::vector<Fighter *> fighters) {
	sf::CircleShape shape;

	int smallRadius = 4;

	for (Fighter *fighter : fighters) {
		int radius = fighter->radius;
		sf::RectangleShape line(sf::Vector2f(radius * 1.5, 10));

		float fighterX = fighter->x;
		float fighterY = fighter->y;

		shape.setRadius(radius);
		shape.setFillColor(fighter->col);
		shape.setPosition(fighterX-radius, fighterY-radius);
		window->draw(shape);

		line.setOrigin(0, 5);
		line.setFillColor(sf::Color(150, 150, 150));
		line.setPosition(fighterX, fighterY);
		line.setRotation(fighter->angle);
		window->draw(line);

		shape.setRadius(smallRadius);
		shape.setFillColor(sf::Color(0, 0, 0));
		shape.setPosition(fighterX - smallRadius,
						  fighterY - smallRadius);
		window->draw(shape);

		float c1 = cosf((fighter->angle - fighter->fov) * M_PI / 180);
		float s1 = sinf((fighter->angle - fighter->fov) * M_PI / 180);
		float c2 = cosf((fighter->angle + fighter->fov) * M_PI / 180);
		float s2 = sinf((fighter->angle + fighter->fov) * M_PI / 180);

		sf::Vertex line1[] = {
			sf::Vertex(sf::Vector2f(fighterX, fighterY)),
			sf::Vertex(sf::Vector2f(fighterX + c1*1000, fighterY + s1*1000))
		};
		window->draw(line1, 2, sf::Lines);

		sf::Vertex line2[] = {
			sf::Vertex(sf::Vector2f(fighterX, fighterY)),
			sf::Vertex(sf::Vector2f(fighterX + c2 * 1000, fighterY + s2 * 1000))
		};
		window->draw(line2, 2, sf::Lines);

	}
}

void Renderer::draw(std::vector<Bullet*> bullets) {
	sf::CircleShape shape;
	float radius = 2;
	for (Bullet* b : bullets) {
		float bx = b->x;
		float by = b->y;

		shape.setRadius(2);
		shape.setFillColor(sf::Color(255, 255, 255));
		shape.setPosition(bx - radius, by - radius);
		window->draw(shape);
	}
}

void Renderer::draw(std::vector<int> scores) {
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(24);
	scoreText.setPosition(0, 0);
	scoreText.setFillColor(sf::Color(255, 255, 255));

	std::string scoreStr = "Hello: ";
	for (int i = 0; i < scores.size() - 1; i++) {
		scoreStr += std::to_string(scores[i]) + " : ";
	}
	scoreStr += std::to_string(scores[scores.size()-1]);
	scoreText.setString(scoreStr);
	window->draw(scoreText);
}