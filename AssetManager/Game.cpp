#include "Game.h"

Game::Game() : m_window("Tiling", sf::Vector2u(1280, 800))
{
	m_clock.restart();
	srand(time(nullptr));

	m_elapsed = 0.0f;

	spriteHolder = map.sliceTileset("tileset.png", sf::Vector2u(32, 32), 4, 32, 32);

	setTilables();
}

Game::~Game(){}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }
void Game::RestartClock(){ m_elapsed += m_clock.restart().asSeconds(); }
Window* Game::GetWindow(){ return &m_window; }


/*	Method to load the "map.xml" file into the program and load the textures	*/
bool Game::loadXML()
{
	placedSprites.clear();
	XMLDocument xml_doc;

	XMLError eResult = xml_doc.LoadFile("map.xml");
	if (eResult != tinyxml2::XML_SUCCESS) return false;

	XMLNode* root = xml_doc.FirstChildElement("Root");
	if (root == nullptr) return false;

	XMLElement* element = root->FirstChildElement("Map");
	if (element == nullptr) return false;

	for (XMLElement* e = element->FirstChildElement("Tile"); e != NULL; e = e->NextSiblingElement("Tile"))
	{
		const char* positionX = e->Attribute("x");
		const char* positionY = e->Attribute("y");
		const char* index = e->Attribute("index");

		int posX = atoi(positionX), posY = atoi(positionY), in = atoi(index);
		//std::cout << posX << ", " << posY << ", " << in << std::endl;
		if (posX <= 0 || posY <= 0 || in < 0) // Program can fail here if not checked
			return false;
			

		std::cout << atoi(index) << ", "<< positionX << ", " << positionY << std::endl;
		if (spriteHolder.size() > 0)
		{
			spriteHolder.at(in).m_sprite.setPosition(posX, posY); //changing all characters to integers with atoi --- ->m_sprite
			spriteHolder.at(in).setChosenTile(in);
			placedSprites.push_back(spriteHolder.at(in)); 
		}

	}

	return true;
}

void Game::HandleInput()
{

	sf::Event event;

	// Moused Button Pressed is better so you only click once rather than holding it down and drawing the same sprite multiple times etc.
	while (m_window.GetRenderWindow()->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left) { placeTile(); }
			else if (event.mouseButton.button == sf::Mouse::Right) { chooseTile(); } 
			else if (event.mouseButton.button == sf::Mouse::Middle) { eraseTile(); std::cout << "size " << placedSprites.size() << std::endl;	} 
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::S) { saveXML(); }
			else if (event.key.code == sf::Keyboard::L) { loadXML(); }
			break;
		default:
			break;
		}
	}
}

/*
* Method to save the map to a file
*/
void Game::saveXML()
{
	XMLDocument saveFile;
	XMLNode *pRoot = saveFile.NewElement("Root");
	saveFile.InsertFirstChild(pRoot);
	XMLElement *pElement = saveFile.NewElement("Map");
	for (int i = 0; i < placedSprites.size(); i++)
	{
		sf::Sprite spr = placedSprites.at(i).m_sprite;
		XMLElement *pListElement = saveFile.NewElement("Tile");

		pListElement->SetAttribute("index", placedSprites.at(i).getChosenTile());
		pListElement->SetAttribute("x", spr.getPosition().x);
		pListElement->SetAttribute("y", spr.getPosition().y);

		pElement->InsertEndChild(pListElement);
	}
	pRoot->InsertEndChild(pElement);
	saveFile.SaveFile("map.xml");
	std::cout << "saved file" << std::endl;
}

/*
* Method to erase a tile from the map
*/
void Game::eraseTile()
{
	sf::Window &window = *m_window.GetRenderWindow();
	sf::Vector2i position = sf::Mouse::getPosition(window);

	int posX = position.x - (position.x % 32);
	int posY = position.y - (position.y % 32);
	sf::Vector2f vec(posX, posY);

	for (int i = 0; i < placedSprites.size(); i++)
	{
		if (placedSprites.at(i).m_sprite.getPosition() == vec) 
		{
			placedSprites.erase(placedSprites.begin() + i);
		}
	}
}

/*
* Method to choose a tile from rendered tiles
*/
void Game::chooseTile()
{
	sf::Window &window = *m_window.GetRenderWindow();
	sf::Vector2i position = sf::Mouse::getPosition(window);
	for (auto spr : tilesToChoose)
	{
		if (spr.second.m_sprite.getGlobalBounds().contains(position.x, position.y)) // changed to ->m_sprite
		{
			//std::cout << "inside" << std::endl;
			chosenTile = spr.first;
			std::cout << chosenTile << std::endl;
		}
	}
}

/*
Method to place tiles with valid chechking for duplicates etc. TODO - make sure tiles get deleted before placing
*/
void Game::placeTile()
{
	sf::Window &window = *m_window.GetRenderWindow();
	sf::Vector2i position = sf::Mouse::getPosition(window);

	//Make it so the tiles are place in a grid, so % 32 gives this effect
	int posX = position.x - (position.x % 32);
	int posY = position.y - (position.y % 32);
	sf::Vector2f vec(posX, posY);
	if(!placedSprites.empty())
	{
		for (auto i : placedSprites)
		{
			//std::cout << "here";
			if (vec == i.m_sprite.getPosition()) //->
			{
				if (i.getChosenTile() == chosenTile)//->
				{
					break;
				}
				else
				{
					eraseTile();
					spriteHolder.at(chosenTile).m_sprite.setPosition(vec);
					spriteHolder.at(chosenTile).setChosenTile(chosenTile);
					placedSprites.push_back(spriteHolder.at(chosenTile));
					break;
				}
			}
			else
			{
				spriteHolder.at(chosenTile).m_sprite.setPosition(vec);
				spriteHolder.at(chosenTile).setChosenTile(chosenTile);
				placedSprites.push_back(spriteHolder.at(chosenTile)); //added bracket and &
			}
			break;
		}
	}
	else
	{
		spriteHolder.at(chosenTile).m_sprite.setPosition(vec);
		spriteHolder.at(chosenTile).setChosenTile(chosenTile);
		placedSprites.push_back(spriteHolder.at(chosenTile));
	}

}

void Game::Update()
{
	m_window.Update();
	
}

/*	Draw the Tiles to Choose From On Screen	*/
void Game::setTilables()
{
	int space = 0;
	for (std::map<int, TextureHolder>::iterator it = spriteHolder.begin(); it != spriteHolder.end(); ++it)
	{
		sf::Sprite spr = it->second.m_sprite;
		space += 40;
		spr.setPosition(sf::Vector2f(m_window.GetWindowSize().x - 50, space));
		//std::cout << spr.getPosition().x << ", " << spr.getPosition().y << std::endl;
		tilesToChoose.insert(std::pair<int, sf::Sprite>(it->first, spr));
		//::cout << "size: " << tilesToChoose.size();
	}
}

void Game::Render()
{
	m_window.BeginDraw();

    m_window.GetRenderWindow()->draw(this->map);

	for (const auto& spr : placedSprites)
		m_window.GetRenderWindow()->draw(spr.m_sprite);

	for (std::map<int, TextureHolder>::iterator it = tilesToChoose.begin(); it != tilesToChoose.end(); ++it)
		m_window.GetRenderWindow()->draw((it->second.m_sprite));

	m_window.EndDraw();
}
