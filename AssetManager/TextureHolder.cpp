//Simple class to hold a Texture and it's position in the window.
//Necessary to read/write to XML
#include "TextureHolder.h"

TextureHolder::TextureHolder(sf::Sprite sprite)
{
	m_sprite = sprite;
}

TextureHolder::TextureHolder()
{
}

TextureHolder::~TextureHolder()
{
}
