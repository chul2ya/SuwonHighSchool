#pragma once

class Scene
{
public:

	ObjectManager mObjectManager;

	virtual void Create() = 0;
	virtual void Release() = 0;
	virtual void Init() = 0;
	virtual void Term() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
};

class SceneManager : public Singleton<SceneManager>
{
private:

	map<wstring, Scene*> mScenes;
	Scene* mCurScene;
	Scene* mNextScene;

public:

	~SceneManager();

	void AddObject(Object* object);
	void AddScene(wstring sceneName, Scene* scene);
	void DelScene(wstring sceneName);
	void ChangeScene(wstring sceneName);
	void UpdateScene(float deltaTime);
	void RenderScene();
};