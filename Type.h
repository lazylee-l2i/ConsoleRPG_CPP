#pragma once

#define MAP_WIDTH 21
#define MAP_HEIGHT 11

#define AUTO_MOB_GEN_PERCENT 1
#define AUTO_OTC_GEN_PERCENT 10

enum class EMapTileType
{
	ROAD,
	WALL,
	EXIT,
	ATTACK,
	PLAYER,
	MONSTER,
	HEART,
	QUEST,
	UNDEFINE
};

enum class EItemType
{
	HEART,
	QUEST,
	MAXHEART,
	BOMB,
	UNDEFINE
};

enum class EInputType
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	QUIT,
	ATTACKCALL,
	UNDEFINE
};



enum class EEntityType
{
	PLAYER,
	MONSTER,
	NPC,
	ITEM,
	UNDEFINE
};



struct Pos
{
	int x = 0;
	int y = 0;
	Pos() {}
	Pos(int x, int y);

	Pos& operator=(const Pos& other);
};

Pos operator+(const Pos& left, const Pos& right);

Pos operator-(const Pos& left, const Pos& right);

bool operator==(const Pos& left, const Pos& right);
bool operator!=(const Pos& left, const Pos& right);

int GetLengthAboutTwoPoint(const Pos& left, const Pos& right);

#define DECLARE_SINGLE(classname)					\
private:											\
	classname() {}									\
	classname(const classname& ref)	{}				\
	classname& operator=(const classname& ref) {}	\
	~classname() {}									\
public:												\
	static classname& GetInstance()					\
	{												\
		static classname s_instance;				\
		return s_instance;							\
	}														


#define GET_SINGLE(classname) classname::GetInstance()

#define SAFE_DELETE(_obj)	\
if (_obj)					\
{							\
	delete _obj;			\
	_obj = nullptr;			\
}							
