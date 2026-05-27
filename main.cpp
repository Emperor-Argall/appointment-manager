#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

int state{1};

using namespace std;

void read() {

}

void write() {

}

struct vec2 {
        float x,y;
};

class textBox {
private:
        vec2 pos;
        vec2 size;
        bool visible;
        bool selected{false};
        string text;
        int menu_loc{};

public:
        textBox(vec2 _pos, vec2 _size, int _m) : pos(_pos), size(_size), menu_loc(_m) {this->visible = true;}

        vec2 getPos() const { return pos; }
        vec2 getSize() const { return size; }

        void use() { if (::state == menu_loc) visible = true; }

        void select(sf::RenderWindow& window) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                vec2 mouse{float(mousePos.x), float(mousePos.y)};
                if (visible ) {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                                if ((mouse.x >= pos.x && mouse.x <= pos.x + size.x) && (mouse.y >= pos.y && mouse.y <= pos.y + size.y)) {
                                        selected = true;
                                }
                                else {
                                        selected = false;
                                }

                        }

                }
        }

        void input(char32_t c) {
                const int BACKSPACE{8};
                const int SPACE{32};

                int d = static_cast<int>(c);;

                if ((d >= 65 && d <= 90) || (d >= 97 && d <= 122) || d == SPACE) {
                        text+=static_cast<char>(c);
                }
                else if (d == BACKSPACE) {
                        if (text.length() > 0) {text.pop_back();}
                }

                 cout << text << "|\n" << std::flush;
        }


        void displayText(sf::Font& font, float size, sf::RenderWindow& window) {
                sf::Text t(font);
                t.setCharacterSize(size);
                t.setFillColor(sf::Color::Black);
                t.setString(text);
                t.setPosition({std::floor(pos.x + 10.f), std::floor(pos.y + 10.f)});

                window.draw(t);


        }

        bool isSelected() const {return selected;}



        void Draw(sf::RenderWindow& window) {
                sf::ConvexShape shape;
                shape.setFillColor(sf::Color::White);
                shape.setOutlineThickness(3);
                if (selected) {
                        shape.setOutlineColor(sf::Color::Green);
                }
                else {
                        shape.setOutlineColor(sf::Color::Black);
                }
                shape.setPointCount(4);
                shape.setPoint(0, {pos.x, pos.y});
                shape.setPoint(1, {pos.x + size.x, pos.y});
                shape.setPoint(2, {pos.x + size.x, pos.y + size.y});
                shape.setPoint(3, {pos.x, pos.y + size.y});
                shape.setFillColor(sf::Color::White);

                window.draw(shape);

        }


};

void boxes(vector<textBox>& boxes) {

}







int main() {

        sf::ContextSettings settings;
        settings.antiAliasingLevel = 8;


        sf::RenderWindow window(sf::VideoMode({640, 480}), "Service",sf::State::Windowed, settings);



        // Boxes

        vector<textBox> boxes;
        boxes.push_back(textBox({100,100}, {100, 100}, 1));


        sf::Font font;
        if (!font.openFromFile("../assets/regular.OTF")) cerr << "Error loading font." << endl;





        while (window.isOpen()) {
                while (auto event = window.pollEvent()) {
                        if (event->is<sf::Event::Closed>()) {
                                window.close();
                        }
                        if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
                                if (boxes[0].isSelected()) {
                                        boxes[0].input(textEvent->unicode);
                                }
                        }
                }
                window.clear(sf::Color::Black);
                boxes[0].use();
                boxes[0].select(window);
                boxes[0].Draw(window);
                boxes[0].displayText(font, 18,window);


                window.display();

        }




        return 0;
}