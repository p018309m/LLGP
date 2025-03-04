#include <SFML/Graphics.hpp>

/*
    This version of the SFML "hello world" is statically linked, you may wish to try the dynamically linked version as well.
*/
int WinMain()
{
    sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "SFML works!");
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
    float xVelocity = 2.f;
    float yVelocity = 5.f;

    while (window.isOpen())
    {
        // Event polling section of code - this must be done in the thread which created the window
        // we will talk about threading later, but essentially this must be done here
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            //Movement within bounds of the window
            shapePosition.x += xVelocity;
            shapePosition.y += yVelocity;
            convex.setPosition(shapePosition);
            convex.rotate(sf::degrees(10.f));
            if (shapePosition.x > 1280 - 100 || shapePosition.x < 0)
                xVelocity *= -1;
            if (shapePosition.y > 720 - 100 || shapePosition.y < 0)
                yVelocity *= -1;
        }

        window.clear();
        window.draw(convex);
        window.display();
    }
}