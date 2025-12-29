//
// Created by piotr on 16.12.2025.
//

#ifndef GAME_PI_MAP_H
#define GAME_PI_MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "../utils/json.hpp"
#include <fstream>


class Map : public sf::Drawable, public sf::Transformable {
public:
    bool loadFromTiledJSON(const std::string& jsonFile);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    unsigned int m_mapWidth = 0;
    unsigned int m_mapHeight = 0;
    unsigned int m_tileWidth = 0;
    unsigned int m_tileHeight = 0;
};



#endif //GAME_PI_MAP_H