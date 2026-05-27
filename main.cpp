#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

int state{0};

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
        textBox(vec2 _pos, vec2 _size, int _m) : pos(_pos), size(_size), menu_loc(_m) {}

        vec2 getPos() const { return pos; }
        vec2 getSize() const { return size; }

        void use() { if (::state == menu_loc) visible = true; }

        void select(sf::RenderWindow& window, bool click) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                vec2 mouse{float(mousePos.x), float(mousePos.y)};
                if (visible ) {
                        if ((mouse.x >= pos.x && mouse.x <= pos.x + size.x) && (mouse.y >= pos.y && mouse.y <= pos.y + size.y)) {
                                if (click) {
                                        selected = true;
                                }
                        }
                }
        }

        void input(char c) {
                const int BACKSPACE{8};
                const int SPACE{32};

                int d = int(c);
                if ((d >= 65 && d <= 90) || (d >= 97 && d <= 122) || d == SPACE) {
                        text+=c;
                }
                else if (d == BACKSPACE) {
                        if (text.length() > 0) {text.pop_back();}
                }
        }




};

void boxes(vector<textBox>& boxes) {

}







int main() {
        sf::RenderWindow window(sf::VideoMode({640, 480}), "Service");


        // Boxes

        








        while (window.isOpen()) {
                while (auto event = window.pollEvent()) {
                        if (event->is<sf::Event::Closed>()) {
                                window.close();
                        }
                }
                window.clear(sf::Color::Black);




                window.display();

        }




        return 0;
}