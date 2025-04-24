#include "PlayerHUD.h"

PlayerHUD::PlayerHUD(sf::Font font, const sf::Texture& shipTexture) : font(font), shipTexture(shipTexture)
{
    scoreText.setFont(font);
    scoreText.setCharacterSize(18);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(10.f, 85.f));
    scoreText.setString("SCORE: 000000");

    bombText.setFont(font);
    bombText.setCharacterSize(18);
    bombText.setFillColor(sf::Color::Yellow);
    bombText.setPosition(sf::Vector2f(10.f, 35.f));
}

void PlayerHUD::SetHealth(int health)
{
    lifeIcons.clear();
    for (int i = 0; i < health; ++i)
    {
        sf::Sprite icon(shipTexture);
        icon.setScale(sf::Vector2f(0.5f, 0.5f));
        icon.setPosition(sf::Vector2f((float)(10 + i) * 30.f, 60.f));
        lifeIcons.push_back(icon);
    }
}

void PlayerHUD::SetBombCount(int bombs)
{
    bombText.setString("BOMBS: " + std::to_string(bombs));
}

void PlayerHUD::SetScore(int score) 
{
    std::stringstream ss;
    ss << "SCORE: " << std::setw(6) << std::setfill('0') << score;
    scoreText.setString(ss.str());
}

void PlayerHUD::Render(sf::RenderWindow& window)
{
    window.draw(scoreText);
    //window.draw(bombText);
}
