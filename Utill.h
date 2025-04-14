#pragma once
#include <unordered_map>
#include <mutex>

// ================= GAME SETTING CONST VALUE DECLARE =================
// Map Size Desicion
#define MAP_HEIGHT 21
#define MAP_WIDTH 31

// Auto Generate Percentage Decision
#define AUTO_MOB_GEN_PERCENT 2
#define AUTO_OTC_GEN_PERCENT 10

// Player Spawn Point Decision
#define PLAYER_SPAWNPOINT_X MAP_WIDTH / 2
#define PLAYER_SPAWNPOINT_Y MAP_HEIGHT / 2

// Game Speed Decision
#define GAME_FPS 10
#define UPDATE_DURATION_FRAME 10 

// Player State Decision
#define PLAYER_DEFAULT_MAXHP 10
#define PLAYER_TARGET_QUEST_COUNT 5

// ================= IN-GAME TYPE ENUMERATE DECLARE =================
// Map Tile Type Enumerate
enum class EMapTileType
{
	ROAD,
	WALL,
	EXIT,
	ATTACK,
	PLAYER,
	PLAYER_GETHIT,
	PLAYER_DEAD,
	MONSTER,
	HEART,
	QUEST,
	MAXHEART,
	UNDEFINE
};

// Item Type Enumerate
enum class EItemType
{
	HEART,
	QUEST,
	MAXHEART,
	BOMB,
	UNDEFINE
};

// Input Type Enumerate
enum class EInputType
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	QUIT,
	ATTACKCALL,
	UNDEFINE,
	COMMAND_MODE
};

// Entity TYpe Enumerate
enum class EEntityType
{
	PLAYER,
	MONSTER,
	NPC,
	ITEM,
	UNDEFINE
};

// ================= TILE SYMBOL STATIC MAP DECLARE =================
// Entity Symbol Hash
static std::unordered_map<EMapTileType, const char*> tileSymbols = {
	{EMapTileType::ROAD,     "  "},
	{EMapTileType::WALL,     "¡á"},
	{EMapTileType::EXIT,     "¢Ë"},
	{EMapTileType::PLAYER,   "¡Ù"},
	{EMapTileType::MONSTER,  "¡Þ"},
	{EMapTileType::HEART,    "¢¾"},
	{EMapTileType::MAXHEART, "¢½"},
	{EMapTileType::QUEST,    "¢Ý"},
	{EMapTileType::PLAYER_GETHIT, "¡Ú"},
	{EMapTileType::PLAYER_DEAD, "¢Í"}
};

// Item Type TO Tile Type Hash
static std::unordered_map<EItemType, EMapTileType> itemSymbols = {
	{EItemType::HEART, EMapTileType::HEART},
	{EItemType::MAXHEART, EMapTileType::MAXHEART},
	{EItemType::QUEST, EMapTileType::QUEST}
};

// Input Type TO Symbol Hash
static std::unordered_map<EInputType, const char*> attackSymbols = {
	{EInputType::UP,"¡â"},
	{EInputType::DOWN, "¡ä"},
	{EInputType::LEFT, "¢·"}	,
	{EInputType::RIGHT,"¢¹"}
};

// ================= ENTITY POS STRUCT DELCARE =================
struct Pos
{
	int x = 0;
	int y = 0;
	Pos() {}
	Pos(int x, int y);

	Pos& operator=(const Pos& other);
};

// POS OPERATOR
Pos operator+(const Pos& left, const Pos& right);

Pos operator-(const Pos& left, const Pos& right);

bool operator==(const Pos& left, const Pos& right);
bool operator!=(const Pos& left, const Pos& right);

int GetLengthAboutTwoPoint(const Pos& left, const Pos& right);


// ================= MAKE SINGLETON MACRO DECLARE =================

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
