#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <random>

enum class TypeState { Wait, Rotation, CountResult };

class Baraban {
public:
  Baraban(float x, float y, float width, float heigth, const sf::Texture* texture): x(x), y(y), width(width), heigth(heigth) {
    baraban_shape.setSize(sf::Vector2(width, heigth));
    baraban_shape.setPosition(x, y);
    baraban_shape.setTexture(texture);
  }

  void draw(sf::RenderWindow& window) {
    window.draw(baraban_shape);
  }

  void setTextureRect(const sf::IntRect& rect) {
    baraban_shape.setTextureRect(rect);
  }

  void setTexturePositionY(float texture_pos_y){
    texture_position_y = texture_pos_y;
  }  

  float getTexturePositionY(){
    return texture_position_y;
  }
  
  void setSpining(bool spiping) {
    this->spining = spining;
  }
  bool getSpining() {
    return spining;
  }

  void setSpeed(bool speed) {
    this->speed = speed;
  }
  bool getSpeed() {
    return speed;
  }

  float getX(){
    return x;
  }

  float getY(){
    return y;
  }

   float getWidth(){
    return width;
  }

  float getHeigth(){
    return heigth;
  }

private:
  sf::RectangleShape baraban_shape;
  float speed;
  bool spining;
  float x, y;
  float width, heigth;
  float texture_position_x, texture_position_y;
};

class Button {
public:
  Button(float x, float y, float width, float heigth) {
    button_shape.setSize(sf::Vector2(width, heigth));
    button_shape.setPosition(x, y);
  }
  void draw(sf::RenderWindow &window) { window.draw(button_shape); }
  bool isClickedMouseLeft(sf::RenderWindow &window, const sf::Event &event) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
    return (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left &&
            button_shape.getGlobalBounds().contains(mouse_position.x,
                                                    mouse_position.y));
  }

  void setColor(const sf::Color &color) { button_shape.setFillColor(color); }

private:
  sf::RectangleShape button_shape;
};

class State {
public:
  virtual void handleInput(sf::RenderWindow &window, sf::Event &event) {};
  virtual void draw(sf::RenderWindow &window, std::vector<Baraban>& barabans, std::vector<Button>& buttons) = 0;
  virtual void update(std::vector<Baraban>& barabans, float delta_time) = 0;
  virtual ~State(){};
};

class StateMachine {
public:
  StateMachine() { setState(TypeState::Wait); }
  void run(sf::RenderWindow &window);
  void setState(TypeState type_state);

private:
  std::unique_ptr<State> current_state;
};

class WaitState : public State {
  void handleInput(sf::RenderWindow &window, sf::Event &event) override {
    State::handleInput(window, event);
  }
 void draw(sf::RenderWindow &window, std::vector<Baraban>& barabans, std::vector<Button>& buttons) override {
  }

  void update(std::vector<Baraban>& barabans, float delta_time) override {}
};

class RotateState : public State {
  void handleInput(sf::RenderWindow &window, sf::Event &event) override {
    State::handleInput(window, event);
  }


  void draw(sf::RenderWindow &window, std::vector<Baraban>& barabans, std::vector<Button>& buttons) {
    for(auto& baraban : barabans) {
        baraban.draw(window);
    }
    for(auto& button : buttons) {
        button.draw(window);
    }
  }

  void update(std::vector<Baraban>& barabans, float delta_time) override {
    for(auto& baraban : barabans) {
        baraban.setTextureRect(sf::IntRect(baraban.getTexturePositionY(), 0, 200, 200));
        baraban.setTexturePositionY(baraban.getTexturePositionY()+1);
    }
  }
};

class CountResultState : public State {
  void handleInput(sf::RenderWindow &window, sf::Event &event) override {
    State::handleInput(window, event);
  }

 void draw(sf::RenderWindow &window, std::vector<Baraban>& barabans, std::vector<Button>& buttons) {}

  void update(std::vector<Baraban>& barabans, float delta_time) override {}
};

void StateMachine::run(sf::RenderWindow &window) {
  sf::Event event;

  sf::Texture texture;
  texture.setRepeated(true);
  texture.loadFromFile("shapes.png");
  int i  = 0;
  StateMachine::setState(TypeState::Rotation);
  
  std::vector<Button> buttons = {Button(0, 0, 100, 100), Button(200, 0, 100, 100)};
  std::vector<Baraban> barabans;
  for(int i = 0; i < 3; i++) {
    if(i == 0) {
        barabans.push_back(Baraban(0, 0, 200, 200, &texture));
    } else {
        barabans.push_back(Baraban(barabans[i-1].getX() + barabans[i-1].getWidth(), 0, 200, 200, &texture));
    }
  }

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (buttons[0].isClickedMouseLeft(window, event)) {
        buttons[0].setColor(sf::Color(255, 0, 0));
      }
    }
    window.clear();
    current_state->draw(window, barabans, buttons);
    current_state->update(barabans, 1.0f);
    window.display();
  }
}

void StateMachine::setState(TypeState type_state) {
  switch (type_state) {
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
