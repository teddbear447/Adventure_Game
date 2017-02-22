#include <SFML/Graphics.hpp>

#define WIDE 800
#define HIGH 600

int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDE,HIGH),"Put On Your Adventure Cap!");

sf::CircleShape circle(20);
circle.setFillColor(sf::Color::Yellow);
circle.setPosition(0,0);

int circleDir = 0;


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
    window.clear(sf::Color::Red);
    //Update Every Single Thing
    if(circleDir == 0)
    {
      circle.move(0.1,0);
    }
    else
    {
      circle.move(-0.1,0);
    }
    if(circle.getPosition().x > 700)
    {
      circle.move(-0.1,0);
    }
    if(circle.getPosition().x < 0)
    {
      circle.move(0.1,0);
    }




    //RENDER THE SCREEN!
    window.draw(circle);
    window.display();
  }
}
