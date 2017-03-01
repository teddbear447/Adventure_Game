#include <SFML/Graphics.hpp>
#include <iostream>

//Window
#define WIDE 800
#define HIGH 600

int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDE,HIGH),"FROUGER");

//Characters
sf::CircleShape circle(15);
circle.setFillColor(sf::Color::Yellow);
circle.setPosition(0,300);

sf::RectangleShape hero(sf::Vector2f(10, 10));
hero.setFillColor(sf::Color::Blue);
hero.setPosition(0,0);

//Variables and stuff
int circleDir = 0;

double heroSpeed = 0.5;

int score = 10;


//Game Loop
  while(window.isOpen())
  //Event Handler
  {
    sf::Event event;
    while(window.pollEvent(event))
    //Event Closer
    {
      if(event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && hero.getPosition().y > 0)
    {
      hero.move(0,-heroSpeed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && hero.getPosition().y < HIGH-hero.getSize().y)
    {
      hero.move(0,heroSpeed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && hero.getPosition().x < WIDE-hero.getSize().x)
    {
      hero.move(heroSpeed,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && hero.getPosition().x > 0)
    {
      hero.move(-heroSpeed,0);
    }


    //Update Every Single Thing
    window.clear(sf::Color::Black);
    if(circleDir == 0)
    {
      circle.move(1,0);
    }
    else
    {
      circle.move(-800,0);
    }
    if(circle.getPosition().x > 800)
    {
      circleDir = 1;
    }
    if(circle.getPosition().x < 0)
    {
      circleDir = 0;
    }

    if(hero.getGlobalBounds().intersects(circle.getGlobalBounds()))
    {
      std::cout << "You touched the circle!" << std::endl;
    }
    else
    {
      std::cout << "Don't touch the circle!" << std::endl;
    }




    //RENDER THE SCREEN!
    window.draw(hero);
    window.draw(circle);
    window.display();
  }
}
