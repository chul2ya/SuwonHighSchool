#pragma once

template <typename T>
class Singleton
{
protected:

	Singleton() {};

public:

	static T* GetInstance()
	{
		static T* inst = new T();
		return inst;
	}

};

template <typename T>
class SingletonDX
{
protected:

	SingletonDX() {};

	virtual void OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void OnReset() = 0;
	virtual void OnLost() = 0;

public:

	static T* GetInstance()
	{
		static T* inst = new T();
		return inst;
	}
};