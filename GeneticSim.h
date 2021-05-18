#pragma once

#include <SFML/Graphics.hpp>
#include "Fighter.h"
#include "NeuralNet.h"
#include "Renderer.h"
#include "math.h"

class GeneticSim {
public:
	GeneticSim();

private:
	std::vector<Fighter*> fighters;
	std::vector<int> scores;

	sf::RenderWindow window;
	Renderer renderer;

	void init();
	void update();
	void draw();
};