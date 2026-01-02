#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <filesystem>

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
        // Load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        m_tileset.setSmooth(false);

        // Resize vertex array
        m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        m_vertices.resize(width * height * 6);

        float tsx = static_cast<float>(tileSize.x);
        float tsy = static_cast<float>(tileSize.y);

        for (unsigned int i = 0; i < width; ++i)
        {
            for (unsigned int j = 0; j < height; ++j)
            {
                int tileNumber = tiles[i + j * width];
                if (tileNumber < 0) continue;

                int tilesPerRow = m_tileset.getSize().x / tileSize.x;
                int tu = tileNumber % tilesPerRow;
                int tv = tileNumber / tilesPerRow;

                sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

                // Pixel-perfect positions
                float x0 = static_cast<float>(i * tileSize.x);
                float y0 = static_cast<float>(j * tileSize.y);
                float x1 = static_cast<float>((i + 1) * tileSize.x);
                float y1 = static_cast<float>((j + 1) * tileSize.y);

                triangles[0].position = { x0, y0 };
                triangles[1].position = { x1, y0 };
                triangles[2].position = { x0, y1 };
                triangles[3].position = triangles[2].position;
                triangles[4].position = triangles[1].position;
                triangles[5].position = { x1, y1 };

                // Half-pixel offset texCoords → usuwa bleeding
                float u = tu * tsx + 0.5f;
                float v = tv * tsy + 0.5f;
                float u2 = u + tsx - 1.f;
                float v2 = v + tsy - 1.f;

                triangles[0].texCoords = { u,  v  };
                triangles[1].texCoords = { u2, v  };
                triangles[2].texCoords = { u,  v2 };
                triangles[3].texCoords = triangles[2].texCoords;
                triangles[4].texCoords = triangles[1].texCoords;
                triangles[5].texCoords = { u2, v2 };
            }
        }

        float mapWidthPx  = width  * tileSize.x;
        float mapHeightPx = height * tileSize.y;

        this->setOrigin(sf::Vector2f(mapWidthPx / 2.f, mapHeightPx / 2.f));

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

        unsigned tileSize = j.at("tileSize").get<unsigned>();
        unsigned width    = j.at("mapWidth").get<unsigned>();
        unsigned height   = j.at("mapHeight").get<unsigned>();

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
        states.transform *= getTransform();
        states.texture = &m_tileset;
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture     m_tileset;
};
