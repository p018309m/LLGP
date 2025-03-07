#include <SFML/Graphics.hpp>

/*
    This version of the SFML "hello world" is statically linked, you may wish to try the dynamically linked version as well.
*/
int WinMain()
{
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Sinistar");
    sf::ConvexShape convex;

    //Set Convex Shape Points Here
    convex.setFillColor(sf::Color::White);
    convex.setPointCount(6);
    convex.setPoint(0, { 75.f, 25.f });
    convex.setPoint(1, { 50.f,50.f });
    convex.setPoint(2, { 50.f,100.f });
    convex.setPoint(3, { 75.f,125.f });
    convex.setPoint(4, { 100.f,100.f });
    convex.setPoint(5, { 100.f,50.f });
    convex.setScale({ 2.f,2.f });

    //Set Convex Shape Transform here
    sf::Vector2f shapePosition(500.f, 500.f);
    convex.setPosition(shapePosition);
    convex.setOrigin({ 75.f,75.f });

    //Movement Variables
    float speed = 20.f;

    enum LastDirection 
    {
        Left,
        Right,
        Up,
        Down,
        None
    };

    sf::Vector2f playerPos;

    LastDirection playerDirection = None;

    sf::Clock clock;
    float accumulator = 0;
    const float timestep = 1.f / 60.f;

    while (window.isOpen())
    {
        // Event polling section of code - this must be done in the thread which created the window
        // we will talk about threading later, but essentially this must be done here
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        accumulator += clock.restart().asSeconds();
        while (accumulator >= timestep)
        {
            accumulator -= timestep;
            playerDirection = None;

            //Movement within bounds of the window
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {
                playerPos.x += speed;
                playerDirection = Right;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            {
                playerPos.x -= speed;
                playerDirection = Left;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            {
                playerPos.y -= speed;
                playerDirection = Up;
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            {
                playerPos.y += speed;
                playerDirection = Down;
            }
        }
        
        sf::Vector2f position = playerPos;
        switch (playerDirection)
        {
        case Left:
            position.x -= speed;
            break;
        case Right:
            position.x += speed;
            break;
        case Up:
            position.y -= speed;
            break;
        case Down:
            position.y += speed;
            break;
        default:
            break;
        }

        convex.setPosition(position + ((position - playerPos) * (accumulator / timestep)));

        if (playerPos.x > 1280 + 100)
            playerPos.x = 0;
        else if (playerPos.x < 0)
            playerPos.x = 1280 + 100;
        if (playerPos.y > 720 + 150)
            playerPos.y = 0;
        else if (playerPos.y < 0)
            playerPos.y = 720 + 150;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        window.clear();
        window.draw(convex);
        window.display();
    }
}