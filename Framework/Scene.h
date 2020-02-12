#pragma once
class Scene
{
	vector<Object*> addObjects;
	vector<Object*> objects;
public:

	void AddObject(Object* obj);

	virtual void Init() = 0;
	virtual void Term() = 0;
	virtual void Update(float deltaTime);
	virtual void CollisionUpdate(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render();
};

class SceneManager : public SingleInstance<SceneManager>
{
	map<string, Scene*> sceneMap;

public:
	Scene* curScene = nullptr;

	void AddScene(string name, Scene * scene) 
	{
		sceneMap.insert(make_pair(name, scene));
	}

	void ChangeScene(string Name)
	{
		if (curScene != nullptr)
		{
			curScene->Term();
			curScene = nullptr;
		}
		auto sf = sceneMap.find(Name);
		if (sf != sceneMap.end())
		{
			curScene = sf->second;
			curScene->Init();
		}
	}
	void Update(float deltaTime)
	{
		if (curScene) {
			curScene->Update(deltaTime);
			curScene->CollisionUpdate(deltaTime);
			curScene->LateUpdate(deltaTime);

		}
	}

	void Render()
	{
		if (curScene)
			curScene->Render();
	}
};
