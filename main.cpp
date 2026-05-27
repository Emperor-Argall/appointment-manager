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


bool isSquircle(vec2 pos, vec2 origin, float w, float h) {
        float left = pow((2*(pos.x - origin.x)/w - 1), 4);
        float right = pow((2*(pos.y - origin.y)/h - 1), 4);

        return right + left <= 1.f;
}

sf::ConvexShape createSquircle(vec2 topLeft, vec2 size, sf::Color color) {
        sf::ConvexShape squircle;

        // broj tacaka

        const unsigned int pointCount = 64;
        squircle.setPointCount(pointCount);

        // fancy math
        vec2 center = { topLeft.x + (size.x / 2.f), topLeft.y + (size.y / 2.f) };
        float rx = size.x / 2.f;
        float ry = size.y / 2.f;
        const float pi = 3.14159265f;

        for (unsigned int i = 0; i < pointCount; ++i) {
                // trigonometrija sa gugla za ugao
                float angle = (static_cast<float>(i) / pointCount) * 2.f * pi;
                float cosA = std::cos(angle);
                float sinA = std::sin(angle);

                // koordinate za tacke
                float xOffset = rx * (cosA >= 0 ? 1.f : -1.f) * std::sqrt(std::abs(cosA));
                float yOffset = ry * (sinA >= 0 ? 1.f : -1.f) * std::sqrt(std::abs(sinA));

                // postavljanje tacaka
                squircle.setPoint(i, sf::Vector2f(center.x + xOffset, center.y + yOffset));
        }

        squircle.setFillColor(color);
        return squircle;
}





void squircle_failed(sf::RenderWindow& window,vec2 pos, vec2 size, bool selected) {
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


        void displayText(sf::Font& font, unsigned int size, sf::RenderWindow& window) {
                sf::Text t(font);
                t.setCharacterSize(size);
                t.setFillColor(sf::Color::Black);
                t.setString(text);
                t.setPosition({std::floor(pos.x + 10.f), std::floor(pos.y + 10.f)});

                window.draw(t);


        }

        bool isSelected() const {return selected;}



        void Draw(sf::RenderWindow& window) {

                auto shape = createSquircle(pos, size, sf::Color::White);

                window.draw(shape);

        }


};

void ui(vector<textBox>& boxes, sf::RenderWindow& window, sf::Font& font) {
        for (auto& box : boxes) {
                box.use();
                box.select(window);
                box.Draw(window);
                box.displayText(font, 18,window);
        }
}







int main() {

        sf::ContextSettings settings;
        settings.antiAliasingLevel = 8;


        sf::RenderWindow window(sf::VideoMode({640, 480}), "Service",sf::State::Windowed, settings);



        // Boxes

        vector<textBox> boxes;
        boxes.push_back(textBox({100,100}, {100, 50}, 1));


        sf::Font font;
        if (!font.openFromFile("../assets/bold.OTF")) cerr << "Error loading font." << endl;





        while (window.isOpen()) {
                while (auto event = window.pollEvent()) {
                        if (event->is<sf::Event::Closed>()) {
                                window.close();
                        }
                        if (const auto* textEvent = event->getIf<sf::Event::TextEntered>()) {
                                for (auto& box : boxes) {
                                        if (box.isSelected()) {
                                                box.input(textEvent->unicode);
                                        }
                                }

                        }
                }
                window.clear(sf::Color::Black);

                ui(boxes, window, font);


                window.display();

        }




        return 0;
}