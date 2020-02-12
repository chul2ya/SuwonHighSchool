#include "pch.h"

SceneManager* SceneManager::inst = nullptr;

void Scene::AddObject(Object * obj)
{
	addObjects.push_back(obj);
	if (dynamic_cast<GameObject*>(obj) != nullptr)
	{
		collisionObjects.push_back(static_cast<GameObject*>(obj));
	}
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
	vector<GameObject*> RoomCollision;
	for (auto it = collisionObjects.begin(); it != collisionObjects.end(); ++it)
	{
		if ((*it)->NowRoom != PlayerManager::GetInstance()->NowRoom)
			continue;
		RoomCollision.push_back((*it));
	}

	for (auto it = RoomCollision.begin(); it != RoomCollision.end(); ++it)
	{
		//if ((*it)->collisionLine.size() < 2)
		//	continue;
		if ((*it)->isRemove)
			continue;

		for (auto it2 = it + 1; it2 != RoomCollision.end(); ++it2)
		{
			//if ((*it2)->collisionLine.size() < 2)
			//	continue;
			if ((*it2)->tag == "")
				continue;
			if ((*it2)->isRemove)
				continue;
			for (auto it3 = (*it)->collisionLine.begin(); it3 != (*it)->collisionLine.end();)
			{
				float x1 = (*it3).x + (*it)->position.x;
				float y1 = (*it3).y + (*it)->position.y;

				if (++it3 == (*it)->collisionLine.end())
					break;

				float x2 = (*it3).x + (*it)->position.x;
				float y2 = (*it3).y + (*it)->position.y;				

				for (auto it4 = (*it2)->collisionLine.begin(); it4 != (*it2)->collisionLine.end();)
				{
					float x3 = (*it4).x + (*it2)->position.x;
					float y3 = (*it4).y + (*it2)->position.y;

					if (++it4 == (*it2)->collisionLine.end())
						break;

					float x4 = (*it4).x + (*it2)->position.x;
					float y4 = (*it4).y + (*it2)->position.y;

					float den = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
					if (den == 0)
						continue;

					float ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / den;
					float ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / den;

					if (ua > 0.f && ua < 1.f && ub > 0.f && ub < 1.f)
					{
						(*it)->OnCollisionInprogress((*it2), deltaTime);
						(*it2)->OnCollisionInprogress((*it), deltaTime);
						it3 = (*it)->collisionLine.end();
						break;
					}
				}
			}
			

		}
	}
}

void Scene::LateUpdate(float deltaTime)
{
	for (auto it = collisionObjects.begin(); it != collisionObjects.end();)
	{
		if ((*it)->isRemove)
		{
			it = collisionObjects.erase(it);
		}
		else
		{
			++it;
		}
	}
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
