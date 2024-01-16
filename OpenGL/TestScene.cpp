#include "TestScene.h"
#include <iostream>

#include <chrono>


TestScene::TestScene()
{
	std::cout << "Run Test Scene" << std::endl;

}

TestScene::~TestScene()
{
	delete dq;
	delete piClass;
}

void TestScene::init()
{
	gfx->vSync(false);
	dq = new DrawQuad(rm, basic.shaderHandler);
	piClass = new PiClass("../1_BillionPi.dat", basic.shaderHandler, rm);

	basic.imGuiManager->setPiUpdate(&piClass->getPiUpdateData());

	dq->setTexture(piClass->getTexture());
}

SceneHandlerCalls TestScene::update(float dt)
{
	SceneHandlerCalls theReturn = SceneHandlerCalls::NOTHING;

	if (keyboard->getKeyDown('F'))
	{
		piClass->update();
	}

	return theReturn;
}

void TestScene::render()
{
	dq->render();
}
