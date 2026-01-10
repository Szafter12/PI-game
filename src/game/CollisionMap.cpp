#include "game/CollisionMap.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>
#include <set> // Upewnij się, że masz ten nagłówek

using json = nlohmann::json;

bool CollisionMap::loadFromSpriteFusion(
    const std::filesystem::path& jsonPath,
    const std::set<std::string>& collidableLayers,
    const std::set<std::string>& overrideLayers)
{
    colliders.clear();

    std::ifstream file(jsonPath);
    if (!file.is_open())
        return false;

    nlohmann::json j;
    file >> j;

    const unsigned tileSize = j.at("tileSize").get<unsigned>();
    const unsigned width    = j.at("mapWidth").get<unsigned>();
    const unsigned height   = j.at("mapHeight").get<unsigned>();

    // Tworzymy siatkę logiczną całej mapy (false = wolne, true = ściana)
    std::vector<bool> grid(width * height, false);

    // -----------------------------------------------------------------
    // PRZEBIEG 1: Nanosimy WSZYSTKIE kolizje (Woda, Ściany, Drzewa)
    // -----------------------------------------------------------------
    for (const auto& layer : j.at("layers"))
    {
        const std::string name = layer.at("name").get<std::string>();

        // Jeśli ta warstwa jest na liście blokujących
        if (collidableLayers.count(name))
        {
            for (const auto& tile : layer.at("tiles"))
            {
                int x = tile.at("x").get<int>();
                int y = tile.at("y").get<int>();

                if (x >= 0 && x < width && y >= 0 && y < height) {
                    grid[x + y * width] = true; // Ustawiamy blokadę
                }
            }
        }
    }

    // -----------------------------------------------------------------
    // PRZEBIEG 2: Nanosimy WSZYSTKIE wyjątki (Mosty) - to ma priorytet
    // -----------------------------------------------------------------
    for (const auto& layer : j.at("layers"))
    {
        const std::string name = layer.at("name").get<std::string>();

        // Jeśli ta warstwa jest na liście odblokowujących (Override)
        if (overrideLayers.count(name))
        {
            for (const auto& tile : layer.at("tiles"))
            {
                int x = tile.at("x").get<int>();
                int y = tile.at("y").get<int>();

                if (x >= 0 && x < width && y >= 0 && y < height) {
                    grid[x + y * width] = false; // USUWAMY blokadę (nawet jak była tu woda)
                }
            }
        }
    }

    // -----------------------------------------------------------------
    // KROK 3: Generujemy prostokąty kolizji na podstawie siatki
    // -----------------------------------------------------------------
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            if (grid[x + y * width]) {
                colliders.emplace_back(
                    sf::Vector2f(static_cast<float>(x * tileSize), static_cast<float>(y * tileSize)),
                    sf::Vector2f(static_cast<float>(tileSize), static_cast<float>(tileSize))
                );
            }
        }
    }

    return true;
}

const std::vector<sf::FloatRect>& CollisionMap::getColliders() const
{
    return colliders;
}