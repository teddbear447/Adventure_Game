#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <MATH.h>

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
  map[8][10] = true;
  map[8][11] = true;
  map[8][12] = true;
  map[3][12] = true;
  map[4][12] = true;
  map[7][12] = true;
  map[8][13] = true;
  map[8][14] = true;
  map[8][15] = true;
  map[8][16] = true;
  map[8][17] = true;
  map[8][18] = true;
  map[7][18] = true;
  map[6][18] = true;
  map[5][18] = true;
  map[4][18] = true;
  map[3][18] = true;
  map[3][17] = true;
  map[3][16] = true;
  map[3][15] = true;
  map[9][6] = true;
  map[10][6] = true;
  map[11][6] = true;
  map[12][6] = true;
  map[12][7] = true;
  map[12][8] = true;
  map[12][9] = true;
  map[12][10] = true;
  map[12][11] = true;
  map[12][12] = true;
  map[11][12] = true;
  for(int i=0; i<tileH; i++)
  {
    map[i][0] = true;
    map[i][tileW-1] = true;
  }
  for(int i=0; i<tileW; i++)
  {
    map[0][i] = true;
    map[tileH-1][i] = true;
  }

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

sf::SoundBuffer theme_buffer;
if(!theme_buffer.loadFromFile("Assets/theme.wav"))
{
  std::cout << "Error Loading Theme Sound!" << std::endl;
}

sf::SoundBuffer grunt_buffer;
if(!grunt_buffer.loadFromFile("Assets/grunt.wav"))
{
  std::cout << "Error Loading Grunt Sound!" << std::endl;
}

sf::Texture wall_texture;
if(!wall_texture.loadFromFile("Assets/stone_wall.png"))
{
  std::cout << "Error Loading Wall Texture!" << std::endl;
}

sf::Texture hero_texture;
if(!hero_texture.loadFromFile("Assets/hero.png"))
{
  std::cout << "Error Loading Hero Texture!" << std::endl;
}

sf::Texture enemy_texture;
if(!enemy_texture.loadFromFile("Assets/enemy1.png"))
{
  std::cout << "Error Loading Enemy Texture!" << std::endl;
}

sf::Texture enemy2_texture;
if(!enemy2_texture.loadFromFile("Assets/enemy2.png"))
{
  std::cout << "Error Loading Enemy2 Texture!" << std::endl;
}

sf::Texture stone_texture;
if(!stone_texture.loadFromFile("Assets/stone.png"))
{
  std::cout << "Error Loading Stone Texture!" << std::endl;
}

sf::Sound grunt;
grunt.setBuffer(grunt_buffer);
grunt.setPitch(0.8);

sf::Sound theme;
theme.setBuffer(theme_buffer);
theme.setPitch(0.6);
theme.setLoop(true);

sf::Sprite enemy;
enemy.setScale(sf::Vector2f(3,3));
enemy.setTexture(enemy_texture);
enemy.setPosition(TILESIZE*0, TILESIZE*7);

sf::Sprite enemy2;
enemy2.setScale(sf::Vector2f(2,2));
enemy2.setTexture(enemy2_texture);
enemy2.setPosition(TILESIZE*5, TILESIZE*15);

sf::Sprite hero;
hero.setTexture(hero_texture);
hero.setScale(sf::Vector2f(2,2));
hero.setPosition(TILESIZE*1, TILESIZE*1);

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

double enemy2X = 0.5;
double enemy2Y = 0.5;
double enemy2Dist = 0;

int lives = 5;

bool takingDamage = false;

theme.play();

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

    enemy2Dist = sqrt(pow(hero.getPosition().x - enemy2.getPosition().x, 2)
    + pow(hero.getPosition().y - enemy2.getPosition().y, 2));
    enemy2X = (hero.getPosition().x - enemy2.getPosition().x)/enemy2Dist;
    enemy2Y = (hero.getPosition().y - enemy2.getPosition().y)/enemy2Dist;
    enemy2.move(enemy2X/3, enemy2Y/3);

    if(hero.getGlobalBounds().intersects(enemy.getGlobalBounds()))
    {
      if(takingDamage == false)
      {
        lives--;
        grunt.play();
        takingDamage = true;
      }
    }
    else
    {
      takingDamage = false;
    }

    if(hero.getGlobalBounds().intersects(enemy2.getGlobalBounds()))
    {
      if(takingDamage == false)
      {
        lives--;
        grunt.play();
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
    window.draw(enemy2);
    window.draw(livesDisp);
    window.display();
  }
}
