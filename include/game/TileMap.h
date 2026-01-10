#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    const sf::Vector2f& getSize() const {
        return m_mapSize;
    }
    bool load(const std::filesystem::path& tileset,
              sf::Vector2u tileSize,
              const std::vector<int>& tiles,
              unsigned width,
              unsigned height)
    {
        if (!m_tileset.loadFromFile(tileset))
            return false;

        m_tileset.setSmooth(false);

        m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        m_vertices.resize(width * height * 6);

        float tsx = static_cast<float>(tileSize.x);
        float tsy = static_cast<float>(tileSize.y);

        for (unsigned i = 0; i < width; ++i)
        {
            for (unsigned j = 0; j < height; ++j)
            {
                int tileNumber = tiles[i + j * width];
                if (tileNumber < 0)
                    continue;

                int tilesPerRow = m_tileset.getSize().x / tileSize.x;
                int tu = tileNumber % tilesPerRow;
                int tv = tileNumber / tilesPerRow;

                sf::Vertex* t = &m_vertices[(i + j * width) * 6];

                float x0 = static_cast<float>(i * tileSize.x);
                float y0 = static_cast<float>(j * tileSize.y);
                float x1 = x0 + tileSize.x;
                float y1 = y0 + tileSize.y;

                t[0].position = { x0, y0 };
                t[1].position = { x1, y0 };
                t[2].position = { x0, y1 };
                t[3].position = { x0, y1 };
                t[4].position = { x1, y0 };
                t[5].position = { x1, y1 };

                float u  = tu * tsx + 0.5f;
                float v  = tv * tsy + 0.5f;
                float u2 = u + tsx - 1.f;
                float v2 = v + tsy - 1.f;

                t[0].texCoords = { u,  v  };
                t[1].texCoords = { u2, v  };
                t[2].texCoords = { u,  v2 };
                t[3].texCoords = { u,  v2 };
                t[4].texCoords = { u2, v  };
                t[5].texCoords = { u2, v2 };
            }
        }

        float mapWidthPx  = width  * tileSize.x;
        float mapHeightPx = height * tileSize.y;

        m_mapSize = sf::Vector2f(mapWidthPx, mapHeightPx);
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

        std::vector<int> tiles(width * height, -1);

        for (const auto& layer : j.at("layers"))
        {
            if (layer.at("name").get<std::string>() != layerName)
                continue;

            for (const auto& tile : layer.at("tiles"))
            {
                int x = tile.at("x").get<int>();
                int y = tile.at("y").get<int>();

                if (x < 0 || x >= static_cast<int>(width) ||
                    y < 0 || y >= static_cast<int>(height))
                    continue;

                try
                {
                    int id = std::stoi(tile.at("id").get<std::string>());
                    tiles[x + y * width] = id;
                }
                catch (...)
                {
                    continue;
                }
            }
            break;
        }

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
        states.transform *= getTransform();
        states.texture = &m_tileset;
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture     m_tileset;
    sf::Vector2f m_mapSize;
};
