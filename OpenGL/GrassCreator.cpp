#include "GrassCreator.h"

GrassCreator::GrassCreator(DefToGameObject def, float xpos, float yPos, float size, uint32_t nrOfPlates)
{
	for(int i = 0; i < nrOfPlates; i++)
	{
		grassplates.push_back(new GameObject(def));
	}
	def.rm->getModel("grass.fbx");
}
void GrassCreator::render()
{
	for(int i = 0; i < grassplates.size(); i++)
	{
		grassplates[i]->instanceRender(200);
	}
}
