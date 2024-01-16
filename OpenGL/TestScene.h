#pragma once
#include "Scene.h"
#include "Player.h"
#include "TestBeahvior.h"

#include "DrawQuad.h"
#include "PiClass.h"

class TestScene : public Scene{
public:
	TestScene();
	virtual ~TestScene();
	void init();
	SceneHandlerCalls update(float dt);
	void render();
private:
	DrawQuad* dq;
	PiClass* piClass;
};
