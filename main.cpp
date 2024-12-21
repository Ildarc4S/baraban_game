#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Tiled Texture Example");

    sf::Texture texture;
    if (!texture.loadFromFile("three.png")) {
        return -1;
    }
    texture.setRepeated(true);
    texture.setSmooth(true);

    sf::RectangleShape rectangle(sf::Vector2f(250.f, 600.f));
    rectangle.setTexture(&texture);

    sf::RectangleShape rectangle_two(sf::Vector2f(250.f, 600.f));
    rectangle_two.setTexture(&texture);
    rectangle_two.setPosition(rectangle.getPosition().x + rectangle.getSize().x + 10, rectangle.getPosition().y);


    sf::RectangleShape button(sf::Vector2f(200.f, 200.f));
    button.setFillColor(sf::Color(0, 255, 0));

    button.setPosition(rectangle_two.getPosition().x + rectangle_two.getSize().x + 10, rectangle_two.getPosition().y);

    sf::Clock clock;
    float i = 0.0f;
    float speed = 100.0f;
    int d = -1;
    float speed_kof = 1.0f;
    int stop = 0;
    while (window.isOpen()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    if(button.getGlobalBounds().contains(mousePos.x, mousePos.y)){
                        if(d == -1) {
                            button.setFillColor(sf::Color(255, 0, 0));
                            speed = 100.0f;
                            speed_kof = 1.0f;
                            d = -d;
                        }
                        else {
                            button.setFillColor(sf::Color(0, 255, 0));
                            speed_kof = -speed_kof;
                        }
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        window.clear();
        rectangle.setTextureRect(sf::IntRect(0, i+2*795/3, 300, 795));
        // if(i >= 795) {
        //     i = 0;
        // }
        
        // rectangle.setTextureRect(sf::IntRect(0, i, 300, 550));
        // rectangle_two.setTextureRect(sf::IntRect(0, i, 300, 550));
        // if(d == 1) {
        //     i += speed * deltaTime;
        //     speed += speed_kof;
        // }

        // if(speed <= 100.0f && d == 1) {
        //     d = -d;
        //     stop = 1;
        // }
        
        // if(stop && i < 794/3) {
        //     i += speed * deltaTime;
        // }

        // std::cout << speed << " " << d << " " << i << std::endl;
        window.draw(rectangle); 
        window.draw(rectangle_two);
        window.draw(button);
        window.display();
    }

    return 0;
}
