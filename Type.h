#pragma once

#define MAP_WIDTH 21
#define MAP_HEIGHT 11

#define AUTO_M_REGEN_NUM 4



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

#define TILE_ROAD 0
#define TILE_WALL 1
#define TILE_EXIT 2
#define TILE_ATTACK 3
#define TILE_PLAYER 4
#define TILE_MONSTER 5
#define TILE_HEART 6
#define TILE_QUEST 7

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

enum class EEntityType
{
	PLAYER,
	MONSTER,
	NPC,
	ITEM,
	UNDEFINE
};

enum class EItemType
{
	HEART,
	QUEST,
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

#define DECLARE_SINGLE(classname)		\
private:								\
	classname() {}						\
public:									\
	static classname* GetInstance()		\
	{									\
		static classname s_instance;	\
		return &s_instance;				\
	}									


#define GET_SINGLE(classname) classname::GetInstance()

#define SAFE_DELETE(_obj)	\
if (_obj)					\
{							\
	delete _obj;			\
	_obj = nullptr;			\
}							
