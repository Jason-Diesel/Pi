#pragma once
#include "Graphics.h"
#include "GameObject.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "PiClass.h"

class ImGuiManager{
public:
	ImGuiManager();
	void init();
	void render();

	void addGameObject(GameObject* gameObject, std::string name = "");
	void addLight(Light* light, std::string name = "");
	void setTexture(uint32_t buffer, glm::vec2 size);
	void setPiUpdate(PiUpdate* piUpdate);
private:
	uint32_t Image;
	glm::vec2 textureWidthHeight;

	void renderPiUpdate();
	void renderGameObject();//and Lights
	void renderTexture();
private:
	std::vector<std::pair<GameObject*, std::string>> gameObjects;
	std::vector<std::pair<Light*, std::string>> lights;

	PiUpdate* piUpdate;
};