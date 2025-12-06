#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Gierka PI");
    window.setFramerateLimit(144);

    Player player({800,600});
    sf::Texture texture("../../Grafika/map.png");
    sf::Sprite obiekt(texture);
    obiekt.setPosition({0,0});
    sf::View view({player.position.x+16, player.position.y+16}, {400.f, 300.f});


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(obiekt);
        player.update(window);

        view.setCenter({player.position.x+16, player.position.y+16});
        window.setView(view);

        player.draw(window);


        window.display();
    }
}