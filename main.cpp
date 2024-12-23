#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <memory>

enum class TypeState {
    Wait,
    Rotation,
    CountResult
};

class Button {
public:
    Button(float x, float y, float width, float heigth) {
        button_shape.setSize(sf::Vector2(width, heigth));
        button_shape.setPosition(x, y);
        button_shape.setFillColor(sf::Color(0, 255, 0));
    }
    void draw(sf::RenderWindow& window) {
        window.draw(button_shape);
    }
private:
    sf::RectangleShape button_shape;
};

class State {
public:
    virtual void handleInput(sf::RenderWindow& window, sf::Event& event) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    };
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(float delta_time) = 0;
    virtual ~State() {};
};

class StateMachine {
public:
    StateMachine() {
        setState(TypeState::Wait);
    }
    void run(sf::RenderWindow& window);
    void setState(TypeState type_state);
private:
    std::unique_ptr<State> current_state;
};

class WaitState: public State {
    void handleInput(sf::RenderWindow& window, sf::Event& event) override {
        State::handleInput(window, event);
    }
    void draw(sf::RenderWindow& window) override {

    }

    void update(float delta_time) {

    }
};

class RotateState: public State {
    void handleInput(sf::RenderWindow& window, sf::Event& event) override {
        State::handleInput(window, event);
    }
    
    void draw(sf::RenderWindow& window) override {

    }

    void update(float delta_time) {
        
    }
};

class CountResultState: public State {
    void handleInput(sf::RenderWindow& window, sf::Event& event) override {
        State::handleInput(window, event); 
    }

    void draw(sf::RenderWindow& window) override {

    }

    void update(float delta_time) {
        
    }
};


void StateMachine::run(sf::RenderWindow& window) {
    sf::Event event;
    Button b(0, 0, 100, 100);
    while(window.isOpen()) {
        current_state->handleInput(window, event);
        window.clear();
        b.draw(window);
        window.display();
    }
}

void StateMachine::setState(TypeState type_state) {
    switch(type_state) {
        case TypeState::Wait:
            current_state = std::make_unique<WaitState>();
            break;
        case TypeState::Rotation:
            current_state = std::make_unique<RotateState>();
            break;
        case TypeState::CountResult:
            current_state = std::make_unique<CountResultState>();
            break;
    }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(1000, 1000), "MBG");
  StateMachine state_machine;
  state_machine.run(window);

  return 0;
}
