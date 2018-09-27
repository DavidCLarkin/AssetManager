#pragma once
#ifndef TextureHolder_hpp
#define TextureHolder_hpp

#include <SFML/Graphics.hpp>

class TextureHolder
{
public:
	TextureHolder(sf::Sprite sprite);
	TextureHolder();
	~TextureHolder();

	sf::Sprite m_sprite;

	void setChosenTile(const int &chosenTile) { m_chosenTile = chosenTile; }
	int getChosenTile() { return m_chosenTile; }

private:
	int m_chosenTile;

};
#endif /* TextureHolder_hpp */
