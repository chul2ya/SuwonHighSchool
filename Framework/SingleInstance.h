#pragma once

template<typename T>
class SingleInstance {
public:
	SingleInstance() {};
	~SingleInstance() {};

	static T* GetInstance() {
		static T* _inst = new T();
		return _inst;
	}
};