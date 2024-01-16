#pragma once
#include "ShaderHandler.h"

class DrawQuad {
public:
	DrawQuad(ResourceManager* rm, ShaderHandler* sh);
	void render();
	void setTexture(uint32_t tex);
private:
	uint32_t texture;

	uint32_t VAO;
	uint32_t VBO;
	uint32_t indecies;

	ResourceManager* rm;
	ShaderHandler* sh;
};