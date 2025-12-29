//
// Created by piotr on 16.12.2025.
//

#include "../../include/game/map.h"
using json = nlohmann::json;

bool Map::loadFromTiledJSON(const std::string& jsonFile)
{
    std::ifstream file(jsonFile);
    if (!file) return false;

    json j;
    file >> j;

    if (j.find("layers") == j.end() || j["layers"].empty())
        return false;

    // m_tileWidth  = j["tilewidth"];
    // m_tileHeight = j["tileheight"];
    // m_mapWidth   = j["width"];
    // m_mapHeight  = j["height"];
    m_tileWidth  = j.value("tilewidth", 0);
    m_tileHeight = j.value("tileheight", 0);
    m_mapWidth   = j.value("width", 0);
    m_mapHeight  = j.value("height", 0);

    if (!m_tileWidth || !m_tileHeight || !m_mapWidth || !m_mapHeight)
        return false;

    // Load tileset
    if (!j.contains("tilesets") || j["tilesets"].empty())
        return false;

    auto tileset = j["tilesets"][0];
    if (tileset.contains("source"))
        throw std::runtime_error("External TSX not supported yet");

    unsigned int firstGid = tileset["firstgid"];
    unsigned int columns = tileset["columns"];

    //znaczy ze column=null
    if (!tileset.contains("columns") || tileset["columns"].is_null())
        throw std::runtime_error("Tileset has no 'columns' – probably image collection or external TSX");


    // Znajdź folder, w którym jest JSON
    std::string directory = jsonFile.substr(0, jsonFile.find_last_of("/\\") + 1);
    std::string imagePath = tileset["image"];

    // Łączymy ścieżkę folderu z nazwą pliku graficznego
    if (!m_tileset.loadFromFile(directory + imagePath))
        return false;


    // Get tile layer
    // for (const auto& layer : j["layers"]) {
    //     if (layer["type"] != "tilelayer")
    //         continue;
    //     auto data  = layer["data"];
    //     // rysowanie tile’i
    // }

    auto layer = j["layers"][0];
    if (layer["type"] != "tilelayer")
        return false;

    // data=null
    if (!layer.contains("data") || layer["data"].is_null())
        throw std::runtime_error("Tile layer has no 'data' (probably chunked/infinite map)");

    auto data  = layer["data"];

   // m_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
    m_vertices.resize(m_mapWidth * m_mapHeight * 4);

    for (unsigned int y = 0; y < m_mapHeight; y++) {
        for (unsigned int x = 0; x < m_mapWidth; x++)
        {
            int tileNumber = data[x + y * m_mapWidth];
            if (tileNumber == 0) {
                sf::Vertex* quad = &m_vertices[(x + y * m_mapWidth) * 4];
                for (int i = 0; i < 4; ++i) {
                    quad[i].position = {0, 0}; // Przenieś w niebyt (opcjonalne)
                    quad[i].color = sf::Color::Transparent; // Ustaw jako całkowicie przezroczyste
                }
                continue;
            }



            tileNumber -= firstGid;

            int tu = tileNumber % columns;
            int tv = tileNumber / columns;

            sf::Vertex* quad = &m_vertices[(x + y * m_mapWidth) * 4];

            // Positions
            quad[0].position = {
                static_cast<float>(x * m_tileWidth),
                static_cast<float>(y * m_tileHeight)
            };

            quad[1].position = {
                static_cast<float>((x + 1) * m_tileWidth),
                static_cast<float>(y * m_tileHeight)
            };
            quad[2].position = {
                static_cast<float>((x + 1) * m_tileWidth),
                static_cast<float>((y + 1) * m_tileHeight)
            };
            quad[3].position = {
                static_cast<float>(x * m_tileWidth),
                static_cast<float>((y + 1) * m_tileHeight)
            };

            // Texture coords
            quad[0].texCoords = {
                static_cast<float>(tu * m_tileWidth),
                static_cast<float>(tv * m_tileHeight)
            };
            quad[1].texCoords = {
                static_cast<float>((tu + 1) * m_tileWidth),
                static_cast<float>(tv * m_tileHeight)
            };
            quad[2].texCoords = {
                static_cast<float>((tu + 1) * m_tileWidth),
                static_cast<float>((tv + 1) * m_tileHeight)
            };
            quad[3].texCoords = {
                static_cast<float>(tu * m_tileWidth),
                static_cast<float>((tv + 1) * m_tileHeight)
            };


        }
    }
    return true;
}

//NOWE
void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_tileset;
    target.draw(m_vertices, states);
}