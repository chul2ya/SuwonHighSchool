#include "pch.h"

void Scene::AddObject(Object * obj)
{
	addObjects.push_back(obj);
}

void Scene::Update(float deltaTime)
{
	objects.insert(objects.end(), addObjects.begin(), addObjects.end());
	addObjects.clear();
	for (auto it = objects.begin(); it != objects.end(); ++it) 
	{
		(*it)->Update(deltaTime);
	}
}

void Scene::CollisionUpdate(float deltaTime)
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		for (auto it2 = it + 1; it2 != objects.end(); ++it2)
		{
			auto p1 = static_cast<Object*>(*it);
			auto p2 = static_cast<Object*>(*it2);

			FRECT p1Rect, p2Rect;
			p1Rect = p1->CollisionMask + p1->position;
			p2Rect = p2->CollisionMask + p2->position;

			bool IsCollision = p1Rect.IsCollision(p2Rect);

			if (IsCollision)
			{
				p1->OnCollisionInprogress((p2), deltaTime);
				p2->OnCollisionInprogress((p1), deltaTime);
			}
		}
	}
}

void Scene::LateUpdate(float deltaTime)
{
	for (auto it = objects.begin(); it != objects.end();)
	{
		(*it)->LateUpdate(deltaTime);

		if ((*it)->isRemove)
		{
			delete (*it);
			it = objects.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Scene::Render()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		(*it)->Render();
	}
}
