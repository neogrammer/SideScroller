#ifndef CFG_H__
#define CFG_H__

#include <SFML/Graphics.hpp>
#include <core/ResourceManager.h>
#include <action/ActionMap.h>
#include <vector>
#include <variant>
#include <utility>

enum class MachineType
{
	Player
};

enum class OriginPtType
{
	Center,
	TL,
	TR,
	TopCenter,
	BottomCenter,
	BR,
	BL,
	RightCenter,
	LeftCenter
};

enum class RayDirType
{
	Velocity,
	Target,
	ReflectedVelocity,
	ReflectedTarget
};

enum class AnimDirType
{
	Left,
	Right,
	Uni,
	NotSet
};

enum class TravelDir
{
	Horizontal,
	Vertical,
	Directed,
	Scripted,
	Path,
	NotSet
};

enum class ProjectileType
{
	Base,
	BusterBullet
};

enum class ResolutionDir : int
{
	Up,
	Down,
	Left,
	Right,
	None
};

enum class SpriteType
{
	Player,
	Projectile,
	Platform,
	Enemy,
	Tile,
	Basic
};

enum class CmdType
{
	Move,
	Count
};

enum class TexType
{
	Player,
	Tile,
	NotSet
};


enum class GameStateType
{
	None,
	Splash,
	Title,
	Play,
	Gameover,
	Menu,
	Pause,
	StageSelect,
	StageClearState
};

enum class GameEvent
{
	StoppedRunning,
	StartedRunning,
	StartedAttacking,
	StoppedAttacking,
	ContinuedAttacking,
	DamageCooldownEnded,
	LifeDepleted,
	Damaged,
	Jumped,
	PeakingJump,
	Fell,
	GrabbingForLedge,
	HoldingOntoLedge,
	StartedToRepel,
	JumpedOffWall,
	Crouched,
	Dashed,
	StartedDashAttack,
	ContinuedDashAttack,
	StoppedDashAttack,
	Slid,
	GrabbedOntoLadder,
	Count
};

enum class AnimType
{
	Player,
	Goblin,
	Count
};

enum class PlayerState
{
	Idle,
	Running,
	Attacking,
	Dying,
	Damaged,
	Jumping,
	PeakingJump,
	Falling,
	GrabbingEdge,
	HangingFromEdge,
	WallSliding,
	Crouching,
	Dashing,
	DashAttacking,
	Sliding,
	LadderClimbing,
	Count
};

enum class GoblinState
{
	Idle,
	Running,
	Attacking,
	Damaged,
	Dying,
	Count
};

enum class Dir
{
	Right,
	Left,
	Count
};

struct Cfg
{
	Cfg() = delete;
	Cfg(const Cfg&) = delete;
	Cfg& operator=(const Cfg&) = delete;


	//globals 
	//static sol::state lua; // globals are bad, but we'll use it for simpler implementation
	static void Initialize();

	// Resource Enums 
	enum class Textures : int { Logo, Title, LifeBar, RetroMenu, PlayerAtlas, GoblinAtlas, BG1_1, BG1_2, BG1_3, BG1_4, BG1_5, Count };
	enum class Fonts : int { Font1, Mickey, Count };
	enum class Music : int { Intro, Count };
	enum class Sounds : int { Sword1, FootstepDirt, Sword2, Sword3, PlayerHit, GoblinHit, GoblinAtk1, GoblinDeath, GoblinDie1, GoblinYell, GoblinHurt, GoblinScream, Count };

	// inputs the player will be able to use
	enum PlayerInputs : int
	{
		// Keyboard mappable Keypresses
		Up, Down, Left, Right, A, X, Y, B, Start, Select, R1, L1,

		//// Joystick input, like a ps5 controller, DPad* and Axis* are handled differently than the rest of the joystick
		DPadX, DPadY, AxisX, AxisY,
		JoyA, JoyB, JoyX, JoyY, JoyR1, JoyL1, JoyStart, JoySelect
	};

	// resource buckets for each type of resource
	static ResourceManager<sf::Texture, int> textures;
	static ResourceManager<sf::Music, int> music;
	static ResourceManager<sf::SoundBuffer, int> sounds;
	static ResourceManager<sf::Font, int> fonts;
	
	static ActionMap<int> playerInputs;

	static std::map<std::string, Textures> textureLookupTable;
	static std::map<std::pair<AnimType, std::string>, std::variant<PlayerState, GoblinState> > animStateLookup;
	static std::map<std::pair<std::variant<PlayerState, GoblinState>, bool>, std::string> playerStateStringLookup;

	static std::map<std::pair<AnimType, std::string>, std::variant<PlayerState, GoblinState> > goblinAnimStateLookup;
	static std::map<std::pair<std::variant<PlayerState, GoblinState>, bool>, std::string> goblinStateStringLookup;
private:
    // initalize the resources for the entire game
    static void initFonts();
    static void initMusic();
    static void initSounds();
    static void initTextures();
	static void initPlayerInputs();
};


#endif