#include "PlayerHUD.h"

PlayerHUD::PlayerHUD()
{
    if (!shipTexture.loadFromImage(sf::Image("assets/spaceship.png")))
        return;
    if (!font.openFromFile("assets/font/Run, Coward.ttf"))
        return;

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition(sf::Vector2f(100.f, 65.f));
    scoreText.setString("00");

    bombText.setFont(font);
    bombText.setCharacterSize(18);
    bombText.setFillColor(sf::Color::Yellow);
    bombText.setPosition(sf::Vector2f(10.f, 35.f));
    bombText.setString("EMPTY ");
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
    window.draw(bombText);
}
