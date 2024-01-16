#pragma once
#include "BufferCreator.h"
#include "ShaderHandler.h"
#include <fstream>
#include <glm.hpp>

struct PiUpdate {
	//These are constant through out the whole program
	uint32_t textureWidth;//4
	uint32_t textureHeight;//8
	//
	uint32_t currentWidth;//12
	uint32_t groupsOf;//16 (done)
	uint32_t color;
	uint32_t offset;
	float zoom;
	uint32_t padding[1];
};

class PiClass {
public:
	PiClass(const std::string& readFile, ShaderHandler* sh, ResourceManager* rm, const glm::ivec2& windowSize = glm::ivec2(1920, 1080));
	void writeToBinaryFile(const std::string& fileName);
	void update();
	uint32_t getTexture();
	PiUpdate& getPiUpdateData();
private:
	void readTextFile(const std::string& readFile);
	void readBinaryFile(const std::string& readFile);
	void imguiManager();
	void createTexture(const glm::ivec2& windowSize);

	std::vector<uint8_t> data;
	ShaderHandler* sh;

	uint32_t texture;
	uint32_t VAO;

	PiUpdate PiConstantBufferData;
	uint32_t PiConstantBuffer;
	uint32_t computeShader;
};