#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <filesystem>
#include <set>

class CollisionMap {
public:
    bool loadFromSpriteFusion(
        const std::filesystem::path& jsonPath,
        const std::set<std::string>& collidableLayers, // Zmieniam na set dla szybszego wyszukiwania
         const std::set<std::string>& overrideLayers
    );

    const std::vector<sf::FloatRect>& getColliders() const;

private:
    std::vector<sf::FloatRect> colliders;
};
