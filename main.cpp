#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

//Window
#define WIDE 800
#define HIGH 640

#define TILESIZE 32

bool testColl(sf::Sprite a, sf::Sprite b)
{
  return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

bool testWallColl(sf::Sprite a, std::vector<sf::Sprite> walls)
{
  for(int i=0; i<walls.size(); i++)
  {
    if(a.getGlobalBounds().intersects(walls[i].getGlobalBounds()))
    {
      return true;
    }
  }
  return false;
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDE,HIGH),"Block Adventure");

  int tileW = WIDE/TILESIZE;
  int tileH = HIGH/TILESIZE;

  std::vector<std::vector<bool> > map;

  for(int i=0; i<tileH; i++)
  {
    std::vector<bool> temp;
    for(int j=0; j<tileW; j++)
    {
      temp.push_back(false);
    }
    map.push_back(temp);
  }

  map[3][6] = true;
  map[4][6] = true;
  map[5][6] = true;
  map[6][6] = true;
  map[7][6] = true;
  map[8][6] = true;
  map[3][7] = true;
  map[3][8] = true;
  map[3][9] = true;
  map[3][10] = true;
  map[3][11] = true;
  map[3][12] = true;
  map[8][7] = true;
  map[8][8] = true;
  map[8][9] = true;
  map[8][10] = true;
  map[8][11] = true;
  map[8][12] = true;
  map[3][12] = true;
  map[4][12] = true;
  map[7][12] = true;
  map[8][12] = true;

  for(int i=0; i<map.size(); i++)
  {
    for(int j=0; j<map[i].size(); j++)
    {
      if(map[i][j] == true)
      {
        std::cout << 'O';
      }
      else
      {
        std::cout << ' ';
      }
    }
    std::cout << std::endl;
  }

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

sf::Texture stone_texture;
if(!stone_texture.loadFromFile("Assets/stone.png"))
{
  std::cout << "Error Loading Texture" << std::endl;
}

sf::Sprite enemy;
enemy.setScale(sf::Vector2f(3,3));
enemy.setTexture(enemy_texture);
enemy.setPosition(0,500);

sf::Sprite hero;
hero.setTexture(hero_texture);
hero.setScale(sf::Vector2f(2,2));

std::vector<sf::Sprite> wallArr;
for(int i=0; i<map.size(); i++)
{
  for(int j=0; j<map[i].size(); j++)
  {
    if(map[i][j] == true)
    {
      sf::Sprite temp;
      temp.setTexture(wall_texture);
      temp.setScale(sf::Vector2f(2,2));
      temp.setPosition(j*TILESIZE,i*TILESIZE);
      wallArr.push_back(temp);
    }
  }
}

sf::Sprite stone;
stone.setTexture(stone_texture);
stone.setScale(sf::Vector2f(2,2));
stone.setPosition(0,0);

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
      if(testWallColl(hero, wallArr))
      {
        hero.move(0,heroSpeed);
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && hero.getPosition().y < HIGH-TILESIZE)
    {
      hero.move(0,heroSpeed);
      if(testWallColl(hero, wallArr))
      {
        hero.move(0,-heroSpeed);
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && hero.getPosition().x < WIDE-TILESIZE)
    {
      hero.move(heroSpeed,0);
      if(testWallColl(hero, wallArr))
      {
        hero.move(-heroSpeed,0);
      }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && hero.getPosition().x > 0)
    {
      hero.move(-heroSpeed,0);
      if(testWallColl(hero, wallArr))
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
      for(int i=0; i<tileH; i++)
      {
        for(int j=0; j<tileW; j++)
        {
          stone.setPosition(j*TILESIZE, i*TILESIZE);
          window.draw(stone);
        }
      }

    for(int i=0; i<wallArr.size(); i++)
    {
      window.draw(wallArr[i]);
    }
    window.draw(hero);
    window.draw(enemy);
    window.draw(livesDisp);
    window.display();
  }
}
