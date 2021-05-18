#include "GeneticSim.h"

GeneticSim::GeneticSim() {
    window.create(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");
    window.setFramerateLimit(120);
    renderer.setWindowRef(&window);

    init();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::W)
                    fighters[0]->movingForward = true;
                if (event.key.code == sf::Keyboard::A)
                    fighters[0]->turningCW = true;
                if (event.key.code == sf::Keyboard::D)
                    fighters[0]->turningCCW = true;
                if (event.key.code == sf::Keyboard::Space)
                    fighters[0]->firing = true;
                if (event.key.code == sf::Keyboard::R)
                    init();
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::W)
                    fighters[0]->movingForward = false;
                if (event.key.code == sf::Keyboard::A)
                    fighters[0]->turningCW = false;
                if (event.key.code == sf::Keyboard::D)
                    fighters[0]->turningCCW = false;
                if (event.key.code == sf::Keyboard::Space)
                    fighters[0]->firing = false;
                break;
            }
        }
        update();
        draw();
    }
}

void GeneticSim::init() {
    // clear fighters and scores from previous runs
    for (Fighter *f : fighters) delete f;
    fighters.clear();
    scores.clear();

    fighters.push_back(new Fighter(0, 0, 0));
    fighters.push_back(new Fighter(400, 400, 45));

    for (int i = 0; i < fighters.size(); i++) {
        scores.push_back(0);
    }
}

void GeneticSim::update() {
    for (int fighterIdx = 0; fighterIdx < fighters.size(); fighterIdx++) {
        auto f = fighters[fighterIdx];
        f->update();

        float c1 = f->x + cosf((f->angle - f->fov) * M_PI / 180) * 1000;
        float s1 = f->y + sinf((f->angle - f->fov) * M_PI / 180) * 1000;
        float c2 = f->x + cosf((f->angle + f->fov) * M_PI / 180) * 1000;
        float s2 = f->y + sinf((f->angle + f->fov) * M_PI / 180) * 1000;


        // set fighter flags
        bool enemyFlag = false;
        bool bullFlag = false;
        for (Fighter* f2 : fighters) {
            if (f != f2) {
                if (circleTriangle(f->x, f->y, c1, s1, c2, s2, f2->x, f2->y, f2->radius)) {
                    enemyFlag = true;
                }

                for (Bullet* b : f2->bullets) {
                    if (circleTriangle(f->x, f->y, c1, s1, c2, s2, b->x, b->y, 2)) {
                        bullFlag = true;
                        break;
                    }
                }
            }

            if (enemyFlag) f->col = sf::Color(255, 0, 0);
            else if (bullFlag) f->col = sf::Color(255, 255, 0);
            else f->col = sf::Color(100, 100, 50);
        }


        // update all bullets and update scores
        for (int i = 0; i < f->bullets.size(); i++) {
            f->bullets[i]->update();

            float px = f->bullets[i]->x;
            float py = f->bullets[i]->y;

            for (Fighter* f2 : fighters) {
                if (f != f2) {
                    float p2x = f2->x;
                    float p2y = f2->y;

                    auto r2 = pow(px - p2x, 2) + pow(py - p2y, 2);
                    if (r2 <= pow(2 + f2->radius, 2)) {
                        f->bullets[i]->del = true;

                        scores[fighterIdx]++;
                    }
                }
            }

            if (f->bullets[i]->del) {
                delete f->bullets[i];

                f->bullets[i] = f->bullets.back();
                f->bullets.pop_back();
                i--;
            }
        }
    }
}

void GeneticSim::draw() {
    window.clear();
    for (Fighter* f : fighters)
        renderer.draw(f->bullets);
    renderer.draw(fighters);
    renderer.draw(scores);
    window.display();
}

int main() {
    /*Matrix mat({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });

    std::cout << mat << std::endl;

    for (int i = 0; i < mat.getRows(); i++) {
        for (int j = 0; j < mat.getCols(); j++) {
            std::cout << mat(i, j) << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    Matrix mat2({ {10, 11, 12}, {13, 14, 15}, {16, 17, 18} });

    for (int i = 0; i < mat2.getRows(); i++) {
        for (int j = 0; j < mat2.getCols(); j++) {
            std::cout << mat2(i, j) << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    Matrix mat3 = mat * mat2;
    for (int i = 0; i < mat3.getRows(); i++) {
        for (int j = 0; j < mat3.getCols(); j++) {
            std::cout << mat3(i, j) << ", ";
        }
        std::cout << std::endl;
    }*/

    NeuralNet nn(4, { 5, 6, 4 }, 3);
    nn.forward(Matrix({ { 5, 1, 2, 3 } }));

    GeneticSim g;

    return 0;
}