#include <SFML/Graphics.hpp>
#include <ctime>
using namespace sf;

const int W = 600;
const int H = 480;
int speed = 4;
bool field[W][H] = {0};

struct player {
    int x, y, dir;
    Color color;
    
    player(Color c) {
        x = rand() % W;
        y = rand() % H;
        color = c;
        dir = rand() % 4;
    }
    
    void tick() {
        if (dir == 0) y += 1;
        if (dir == 1) x -= 1;
        if (dir == 2) x += 1;
        if (dir == 3) y -= 1;
        if (x >= W) x = 0;
        if (x < 0) x = W - 1;
        if (y >= H) y = 0;
        if (y < 0) y = H - 1;
    }
    
    Vector3f getColor() {
        return Vector3f(color.r, color.g, color.b);
    }
};

int main() {
    srand(time(0));
    
    RenderWindow window(VideoMode(Vector2u(W, H)), "Tron");
    window.setFramerateLimit(60);
    
    Texture texture;
    if (!texture.loadFromFile("background.jpg")) {
        return -1;
    }
    
    Sprite sBackground(texture);
    player p1(Color::Red), p2(Color::Green);
    
    RenderTexture t(Vector2u(W, H));
    t.clear();
    t.draw(sBackground);
    t.display();
    
    Sprite sprite(t.getTexture());
    
    bool Game = true;
    
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }
        
        // Usar Keyboard estático, no de ventana
        if (Keyboard::isKeyPressed(Keyboard::Key::Left))
            if (p1.dir != 2) p1.dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Key::Right))
            if (p1.dir != 1) p1.dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Key::Up))
            if (p1.dir != 0) p1.dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Key::Down))
            if (p1.dir != 3) p1.dir = 0;
        
        if (Keyboard::isKeyPressed(Keyboard::Key::A))
            if (p2.dir != 2) p2.dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Key::D))
            if (p2.dir != 1) p2.dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Key::W))
            if (p2.dir != 0) p2.dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Key::S))
            if (p2.dir != 3) p2.dir = 0;
        
        if (!Game) continue;
        
        for (int i = 0; i < speed; i++) {
            p1.tick();
            p2.tick();
            
            if (field[p1.x][p1.y]) Game = false;
            if (field[p2.x][p2.y]) Game = false;
            
            field[p1.x][p1.y] = true;
            field[p2.x][p2.y] = true;
            
            CircleShape c(3.f);
            c.setPosition(Vector2f(p1.x, p1.y));
            c.setFillColor(p1.color);
            t.draw(c);
            
            c.setPosition(Vector2f(p2.x, p2.y));
            c.setFillColor(p2.color);
            t.draw(c);
            
            t.display();
        }
        
        window.clear();
        window.draw(sprite);
        window.display();
    }
    
    return 0;
}