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
    scoreText.setString("00");
    scoreText.setPosition(sf::Vector2f(144.f - scoreText.getLocalBounds().size.x, 65.f));

    bombText.setFont(font);
    bombText.setCharacterSize(24);
    bombText.setFillColor(sf::Color::Yellow);
    bombText.setPosition(sf::Vector2f(10.f, 35.f));
    bombText.setString("EMPTY ");

    SetHealth(3);
    ScorePoints::OnScoreChange.AddListener(this, std::bind(&PlayerHUD::SetScore, this, std::placeholders::_1));
    HealthCall::OnLivesChange.AddListener(this, std::bind(&PlayerHUD::SetHealth, this, std::placeholders::_1));
}

void PlayerHUD::SetHealth(int health)
{
    std::cout << "Lives Reduced" << std::endl;
    lifeIcons.clear();
    for (int i = 0; i < health; ++i)
    {
        sf::Sprite icon(shipTexture);
        icon.setScale(sf::Vector2f(1.f, 1.f));
        icon.setPosition(sf::Vector2f((float)(0.5f + i) * 25.f, 105.f));
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
    scoreText.setPosition(sf::Vector2f(144.f - scoreText.getLocalBounds().size.x, 65.f));
}

void PlayerHUD::Render(sf::RenderWindow& window)
{
    for (int i = 0; i < lifeIcons.size(); ++i)
       window.draw(lifeIcons[i]);
    window.draw(scoreText);
    window.draw(bombText);
}
