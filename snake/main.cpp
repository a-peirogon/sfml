#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

int N = 30, M = 20;
int size = 16;
int w = size * N;
int h = size * M;
int dir, num = 4;

struct Snake {
    int x, y;
} s[100];

struct Fruit {
    int x, y;
} f;

void Tick() {
    for (int i = num; i > 0; --i) {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }
    if (dir == 0) s[0].y += 1;
    if (dir == 1) s[0].x -= 1;
    if (dir == 2) s[0].x += 1;
    if (dir == 3) s[0].y -= 1;
    
    if ((s[0].x == f.x) && (s[0].y == f.y)) {
        num++;
        f.x = rand() % N;
        f.y = rand() % M;
    }
    
    if (s[0].x > N) s[0].x = 0;
    if (s[0].x < 0) s[0].x = N;
    if (s[0].y > M) s[0].y = 0;
    if (s[0].y < 0) s[0].y = M;
    
    for (int i = 1; i < num; i++)
        if (s[0].x == s[i].x && s[0].y == s[i].y) num = i;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(w, h)), "Snake Game!");
    
    sf::Texture t1, t2;
    if (!t1.loadFromFile("images/white.png")) return -1;
    if (!t2.loadFromFile("images/red.png")) return -1;
    
    sf::Sprite sprite1(t1);
    sf::Sprite sprite2(t2);
    
    sf::Clock clock;
    float timer = 0, delay = 0.1f;
    
    f.x = 10;
    f.y = 10;
    
    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        
        auto event = window.pollEvent();
        while (event) {
            if (event->is<sf::Event::Closed>())
                window.close();
            event = window.pollEvent();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) dir = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) dir = 2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) dir = 3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) dir = 0;
        
        if (timer > delay) {
            timer = 0;
            Tick();
        }
        
        // Draw
        window.clear();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) {
                sprite1.setPosition(sf::Vector2f(i * size, j * size));
                window.draw(sprite1);
            }
        
        for (int i = 0; i < num; i++) {
            sprite2.setPosition(sf::Vector2f(s[i].x * size, s[i].y * size));
            window.draw(sprite2);
        }
        
        sprite2.setPosition(sf::Vector2f(f.x * size, f.y * size));
        window.draw(sprite2);
        window.display();
    }
    
    return 0;
}