#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#define N 100

class Pelota {

    private:

    sf::CircleShape shape;
    int x = 0;
    int y = 0;
    int u = 1;
    int v = 1;
    int enfermo = 0;
    bool anticuerpos = false;

    public:
    static std::vector<Pelota*> allShapes;

    Pelota(int x0, int y0, int u0, int v0, bool enfermo) : shape(6.f), x(x0), y(y0), u(u0), v(v0) {
        shape.setFillColor(sf::Color::Green);
        this->enfermo = enfermo? 400 : 0;
        allShapes.push_back(this);
    }

    void update() {
        x+=u;
        y+=v;

        if (x < 0 || x > 800) u=-u;
        if (y < 0 || y > 500) v=-v;

        shape.setPosition(x,y);

        const sf::FloatRect r = shape.getGlobalBounds();

        for (Pelota* other : allShapes) {
            if (this == other) continue;

            if (enfermo && shape.getGlobalBounds().intersects(other->shape.getGlobalBounds())) {
                if (!other->anticuerpos) contagiar(other);

                // u = -u;
                // v = -v;
                // x+=u;
                // y+=v;
            }
        }

        if (enfermo > 0) {        
            shape.setFillColor(sf::Color::Red);
            anticuerpos = true;
            --enfermo;
        } else if (anticuerpos) {
            shape.setFillColor(sf::Color::Cyan);
        } else {
            shape.setFillColor(sf::Color::Green);
        }


    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }


    void contagiar(Pelota* otro) {
        otro->enfermo = 400;
    }
};


std::vector<Pelota*> Pelota::allShapes;





int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "SFML works!");
    window.setVerticalSyncEnabled(true);

    sf::Color colors[6] = {sf::Color::Blue, sf::Color::Red, sf::Color::Green, sf::Color::Yellow, sf::Color::Cyan, sf::Color::Magenta};
    int vectors[8][2] = {{-2,-1}, {-1,-2},{2,-1},{-1,2},{-2,1},{1,-2},{2,1},{1,2}};

    Pelota* p[N];

    for (size_t i = 0; i < N; i++)
    {
        int dir = rand()%8;
        p[i] = new Pelota(rand()%800, rand()%500, vectors[dir][0], vectors[dir][1], i==0);
    }
    

    // sf::CircleShape shape(10.f);
    // shape.setFillColor(sf::Color::Green);



    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (size_t i = 0; i < N; i++) {
            p[i]->update();
        }
        

        window.clear();

        for (size_t i = 0; i < N; i++) {
            p[i]->draw(window);
        }

        window.display();
    }


        for (size_t i = 0; i < N; i++) {
            delete p[i];
        }

        //delete[] p;

    return 0;
}
