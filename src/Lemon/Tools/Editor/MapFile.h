#ifndef _MapFile
#define _MapFile

// -----------------------------------------------------------------
// This file contains various types used in map file saving/loading
// -----------------------------------------------------------------

// current file type version for compatibility
static const int LEMON_MAP_FILE_VERSION = 3;

using LevelTypeID = unsigned int;

// file header
struct LemonMapFileHeader
{
	int version = LEMON_MAP_FILE_VERSION;
	int objectCount;
};

// level object property bit flags
enum class LevelObjectFlagValue : uint8_t
{
	DRAWABLE = 1 << 0,
	UPDATABLE = 1 << 1,
	COLLIDABLE = 1 << 2
};

// bit flag value operators
LevelObjectFlagValue operator|(LevelObjectFlagValue lhs, LevelObjectFlagValue rhs);
LevelObjectFlagValue operator&(LevelObjectFlagValue lhs, LevelObjectFlagValue rhs);

// to store and manipulate flags
struct LevelObjectFlags
{
	uint8_t flags = 0;

	// comparison operators
	bool operator==(LevelObjectFlags other) { return flags == other.flags; }
	bool operator!=(LevelObjectFlags other) { return flags != other.flags; }

	// from other flags
	void Set(LevelObjectFlags in) { flags |= in.flags; }
	void Unset(LevelObjectFlags in) { flags &= ~in.flags; }
	void Flip(LevelObjectFlags in) { flags ^= in.flags; }
	bool Check(LevelObjectFlags in) { return (flags & in.flags) == in.flags; }

	// from raw values
	void Set(LevelObjectFlagValue in) { flags |= (uint8_t)in; }
	void Unset(LevelObjectFlagValue in) { flags &= ~(uint8_t)in; }
	void Flip(LevelObjectFlagValue in) { flags ^= (uint8_t)in; }
	bool Check(LevelObjectFlagValue in) { return (flags & (uint8_t)in) == (uint8_t)in; }
};

// level object headers
struct LevelObjectHeader
{
	LevelTypeID ID;
	LevelObjectFlags flags;
};

#endif _MapFile