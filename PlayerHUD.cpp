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
    //scoreText.setOrigin(scoreText.getLocalBounds().size / 2.f + scoreText.getLocalBounds().position);
    scoreText.setString("00");
    sf::FloatRect bounds = scoreText.getLocalBounds();
    scoreText.setPosition(sf::Vector2f(144.f - bounds.size.x, 65.f));

    bombText.setFont(font);
    bombText.setCharacterSize(24);
    bombText.setFillColor(sf::Color::Yellow);
    bombText.setPosition(sf::Vector2f(10.f, 35.f));
    bombText.setString("EMPTY ");

    ScorePoints::OnScoreChange.AddListener(this, std::bind(&PlayerHUD::SetScore, this, std::placeholders::_1));
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
    scoreText.setString(std::to_string(score));
    sf::FloatRect bounds = scoreText.getLocalBounds();
    scoreText.setPosition(sf::Vector2f(144.f - bounds.size.x, 65.f));
}

void PlayerHUD::Render(sf::RenderWindow& window)
{
    window.draw(scoreText);
    window.draw(bombText);
}
