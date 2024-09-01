#ifndef SCRIPT_TYPES_H__
#define SCRIPT_TYPES_H__

namespace ai
{
	enum class Direction
	{
		D,
		DR,
		R,
		UR,
		U,
		UL,
		L,
		DL,
		NotSet
	};

	enum class GameStateType
	{
		Splash,
		Title,
		Sandbox,
		Count
	};

	enum class AnimName
	{
		IdleD,
		IdleDR,
		IdleR,
		IdleUR,
		IdleU,
		IdleUL,
		IdleL,
		IdleDL,

		WalkD,
		WalkDR,
		WalkR,
		WalkUR,
		WalkU,
		WalkUL,
		WalkL,
		WalkDL,

		AttackD,
		AttackDR,
		AttackR,
		AttackUR,
		AttackU,
		AttackUL,
		AttackL,
		AttackDL,
		Count
	};

	enum class FrameSizeType
	{
		Idle,
		Walk,
		Attack,
		Count
	};

	enum class TexName
	{
		Tileset1,
		Player,
		Count
	};
}
#endif