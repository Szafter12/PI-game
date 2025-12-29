#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(const std::filesystem::path& tileset,
          sf::Vector2u tileSize,
          const std::vector<int>& tiles,
          unsigned width,
          unsigned height)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        m_vertices.resize(width * height * 6);

        // populate the vertex array, with two triangles per tile
        for (unsigned int i = 0; i < width; ++i)
        {
            for (unsigned int j = 0; j < height; ++j)
            {
                const int tileNumber = tiles[i + j * width];
                if (tileNumber < 0)
                    continue;

                const int tilesPerRow = m_tileset.getSize().x / tileSize.x;
                const int tu = tileNumber % tilesPerRow;
                const int tv = tileNumber / tilesPerRow;

                sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

                triangles[0].position = { sf::Vector2f(i * tileSize.x,       j * tileSize.y)};
                triangles[1].position = { sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y)};
                triangles[2].position = { sf::Vector2f(i * tileSize.x,       (j + 1) * tileSize.y)};
                triangles[3].position = triangles[2].position;
                triangles[4].position = triangles[1].position;
                triangles[5].position = { sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y)};

                triangles[0].texCoords = { sf::Vector2f(tu * tileSize.x,       tv * tileSize.y)};
                triangles[1].texCoords = { sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y)};
                triangles[2].texCoords = { sf::Vector2f(tu * tileSize.x,       (tv + 1) * tileSize.y)};
                triangles[3].texCoords = triangles[2].texCoords;
                triangles[4].texCoords = triangles[1].texCoords;
                triangles[5].texCoords = { sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y)};
            }
        }

        return true;
    }

    bool loadFromJsonLayer(const std::filesystem::path& jsonPath,
                                const std::string& layerName,
                                const std::filesystem::path& tilesetPath)
    {
        std::ifstream file(jsonPath);
        if (!file.is_open())
            return false;

        nlohmann::json j;
        file >> j;

        const unsigned tileSize = j.at("tileSize").get<unsigned>();
        const unsigned width    = j.at("mapWidth").get<unsigned>();
        const unsigned height   = j.at("mapHeight").get<unsigned>();

        // Pusta mapa
        std::vector<int> tiles(width * height, -1);

        bool layerFound = false;

        for (const auto& layer : j.at("layers"))
        {
            if (layer.at("name").get<std::string>() != layerName)
                continue;

            layerFound = true;

            for (const auto& tile : layer.at("tiles"))
            {
                int x = tile.at("x").get<int>();
                int y = tile.at("y").get<int>();

                if (x < 0 || x >= static_cast<int>(width) ||
                    y < 0 || y >= static_cast<int>(height))
                    continue;

                int id = -1;
                try
                {
                    id = std::stoi(tile.at("id").get<std::string>());
                }
                catch (...)
                {
                    continue;
                }

                tiles[x + y * width] = id;
                // tiles[y + x * height] = id;
            }

            break;
        }

        if (!layerFound)
            return false;

        return load(
            tilesetPath,
            { tileSize, tileSize },
            tiles,
            width,
            height
        );
    }


private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture     m_tileset;
};