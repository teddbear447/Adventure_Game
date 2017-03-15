#include <SFML/Graphics.hpp>
#include <iostream>

//Window
#define WIDE 800
#define HIGH 600

#define TILESIZE 32

int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDE,HIGH),"FROUGER");

//Characters and Backgrounds and whatever else can fit in this category
sf::Font font;
if(!font.loadFromFile("Assets/ARCADECLASSIC.TTF"))
{
  std::cout << "Error Loading Font" << std::endl;
}
sf::Text livesDisp;
livesDisp.setPosition(760,0);
livesDisp.setFont(font);
livesDisp.setCharacterSize(24);
livesDisp.setColor(sf::Color::Red);


sf::Texture wall_texture;
if(!wall_texture.loadFromFile("Assets/stone_wall.png"))
{
  std::cout << "Error Loading Texture" << std::endl;
}


sf::Texture hero_texture;
if(!hero_texture.loadFromFile("Assets/hero.png"))
{
  std::cout << "Error Loading Texture" << std::endl;
}

sf::Texture enemy_texture;
if(!enemy_texture.loadFromFile("Assets/enemy1.png"))
{
  std::cout << "Error Loading Texture" << std::endl;
}

sf::Sprite enemy;
enemy.setScale(sf::Vector2f(3,3));
enemy.setTexture(enemy_texture);

sf::Sprite hero;
hero.setTexture(hero_texture);
hero.setScale(sf::Vector2f(2,2));

sf::Sprite wall;
wall.setTexture(wall_texture);
wall.setScale(sf::Vector2f(2,2));
wall.setPosition(400,300);

//Variables and such
int enemyDir = 0;

double heroSpeed = 0.5;

int lives = 5;

bool takingDamage = false;

//Game Loop
  while(window.isOpen())
  {
    sf::Event event;
    while(window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && hero.getPosition().y > 0)
    {
      hero.move(0,-heroSpeed);
      if(hero.getGlobalBounds().intersects(wall.getGlobalBounds()))
      {
        hero.move(0,heroSpeed);
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && hero.getPosition().y < HIGH-TILESIZE)
    {
      hero.move(0,heroSpeed);
      if(hero.getGlobalBounds().intersects(wall.getGlobalBounds()))
      {
        hero.move(0,-heroSpeed);
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && hero.getPosition().x < WIDE-TILESIZE)
    {
      hero.move(heroSpeed,0);
      if(hero.getGlobalBounds().intersects(wall.getGlobalBounds()))
      {
        hero.move(-heroSpeed,0);
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && hero.getPosition().x > 0)
    {
      hero.move(-heroSpeed,0);
      if(hero.getGlobalBounds().intersects(wall.getGlobalBounds()))
      {
        hero.move(heroSpeed,0);
      }
    }


    //Update Every Single Thing
    window.clear(sf::Color::White);
    if(enemyDir == 0)
    {
      enemy.move(2,0);
    }
    else
    {
      enemy.move(-800,0);
    }
    if(enemy.getPosition().x > 800)
    {
      enemyDir = 1;
    }
    if(enemy.getPosition().x < 0)
    {
      enemyDir = 0;
    }

    if(hero.getGlobalBounds().intersects(enemy.getGlobalBounds()))
    {
      if(takingDamage == false)
      {
        lives--;
        takingDamage = true;
      }
    }
    else
    {
      takingDamage = false;
    }

    livesDisp.setString(std::to_string(lives));

    //RENDER THE SCREEN!
    window.draw(wall);
    window.draw(enemy);
    window.draw(hero);
    window.draw(livesDisp);
    window.display();
  }
}
