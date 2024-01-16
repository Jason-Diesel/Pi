#pragma once
#include "GameObject.h"

class GrassCreator
{
public:
	GrassCreator(DefToGameObject def, float xpos, float yPos, float size, uint32_t nrOfPlates = 1);
	void render();
private:
	std::vector<GameObject*> grassplates;
};