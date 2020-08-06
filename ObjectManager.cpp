#include "Game.h"

void ObjectManager::AddObject(Object * object)
{
	mAddObjects.push_back(object);
}

void ObjectManager::Init()
{
}

void ObjectManager::Term()
{
	for (auto it = mObjects.begin(); it != mObjects.end(); ++it)
		delete (*it);

	mObjects.clear();
}

void ObjectManager::Update(float deltaTime)
{
	auto addObjects = mAddObjects;
	mAddObjects.clear();
	mObjects.insert(mObjects.begin(), addObjects.begin(), addObjects.end());
	for (auto& addObject : addObjects)
		addObject->Init();

	sort(mObjects.begin(), mObjects.end(), [](const Object* lhs, const Object* rhs) { return lhs->mLayer < rhs->mLayer; });

	for (auto it = mObjects.begin(); it != mObjects.end();)
	{
		if ((*it)->mDestroy)
		{
			(*it)->Term();
			delete (*it);
			it = mObjects.erase(it);
		}
		else
			++it;
	}

	for (auto& obj : mObjects)
	{
		obj->Update(deltaTime);
	}

	for (auto& obj : mObjects)
	{
		obj->LateUpdate(deltaTime);
	}
}

void ObjectManager::Render()
{
	for (auto& obj : mObjects)
	{
		obj->Render();
	}
}
