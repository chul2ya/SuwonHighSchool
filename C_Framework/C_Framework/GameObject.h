#pragma once
class Room;

class GameObject : public Object
{
public:
	Room* NowRoom = nullptr;

	virtual void FileSave(FILE* fp);
	virtual void FileLoad(std::string buffer);
};

