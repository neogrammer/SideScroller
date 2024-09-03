#include <core/ResourceManager.h>
#include <core/globals.h>

ResourceManager<sf::Texture, int> Cfg::textures = {};
ResourceManager<sf::Font, int> Cfg::fonts = {};
ResourceManager<sf::Music, int> Cfg::music = {};
ResourceManager<sf::SoundBuffer, int> Cfg::sounds = {};

ActionMap<int> Cfg::playerInputs = {};
std::map<std::string, Cfg::Textures> Cfg::textureLookupTable =  {
	{"logo",Textures::Logo},
	{"player",Textures::PlayerAtlas}
};

std::map<std::pair<AnimType, std::string>, std::variant<PlayerState, GoblinState> > Cfg::animStateLookup = {
	{ std::pair{AnimType::Player,"idleRt"}, PlayerState::Idle },
	{ std::pair{AnimType::Player,"runRt"}, PlayerState::Running },
	{ std::pair{AnimType::Player,"attackRt"}, PlayerState::Attacking },
	{ std::pair{AnimType::Player,"deathRt"}, PlayerState::Dying },
	{ std::pair{AnimType::Player,"hurtRt"}, PlayerState::Damaged },
	{ std::pair{AnimType::Player,"jumpRt"}, PlayerState::Jumping },
	{ std::pair{AnimType::Player,"upToFallRt"}, PlayerState::PeakingJump },
	{ std::pair{AnimType::Player,"fallRt"}, PlayerState::Falling },
	{ std::pair{AnimType::Player,"edgeGrabRt"}, PlayerState::GrabbingEdge },
	{ std::pair{AnimType::Player,"idleEdgeRt"}, PlayerState::HangingFromEdge },
	{ std::pair{AnimType::Player,"wallSlideRt"}, PlayerState::WallSliding },
	{ std::pair{AnimType::Player,"crouchRt"}, PlayerState::Crouching },
	{ std::pair{AnimType::Player,"dashRt"}, PlayerState::Dashing },
	{ std::pair{AnimType::Player,"dashAttackRt"}, PlayerState::DashAttacking },
	{ std::pair{AnimType::Player,"slideRt"}, PlayerState::Sliding },
	{ std::pair{AnimType::Player,"ladderGrabRt"}, PlayerState::LadderClimbing },
	{ std::pair{AnimType::Player,"idleLt"}, PlayerState::Idle },
	{ std::pair{AnimType::Player,"runLt"}, PlayerState::Running },
	{ std::pair{AnimType::Player,"attackLt"}, PlayerState::Attacking },
	{ std::pair{AnimType::Player,"deathLt"}, PlayerState::Dying },
	{ std::pair{AnimType::Player,"hurtLt"}, PlayerState::Damaged },
	{ std::pair{AnimType::Player,"jumpLt"}, PlayerState::Jumping },
	{ std::pair{AnimType::Player,"upToFallLt"}, PlayerState::PeakingJump },
	{ std::pair{AnimType::Player,"fallLt"}, PlayerState::Falling },
	{ std::pair{AnimType::Player,"edgeGrabLt"}, PlayerState::GrabbingEdge },
	{ std::pair{AnimType::Player,"idleEdgeLt"}, PlayerState::HangingFromEdge },
	{ std::pair{AnimType::Player,"wallSlideLt"}, PlayerState::WallSliding },
	{ std::pair{AnimType::Player,"crouchLt"}, PlayerState::Crouching },
	{ std::pair{AnimType::Player,"dashLt"}, PlayerState::Dashing },
	{ std::pair{AnimType::Player,"dashAttackLt"}, PlayerState::DashAttacking },
	{ std::pair{AnimType::Player,"slideLt"}, PlayerState::Sliding },
	{ std::pair{AnimType::Player,"ladderGrabLt"}, PlayerState::LadderClimbing }
};

std::map<std::pair<std::variant<PlayerState, GoblinState>, bool>, std::string> Cfg::playerStateStringLookup = {
	{ std::pair(PlayerState::Idle, true), "idleRt"},
	{ std::pair(PlayerState::Running, true), "runRt"},
		{ std::pair(PlayerState::Attacking, true), "attackRt"},
	{ std::pair(PlayerState::Dying, true), "deathRt"},
		{ std::pair(PlayerState::Damaged, true), "hurtRt"},
	{ std::pair(PlayerState::Jumping, true), "jumpRt"},
		{ std::pair(PlayerState::PeakingJump, true), "upToFallRt"},
	{ std::pair(PlayerState::Falling, true), "fallRt"},
		{ std::pair(PlayerState::GrabbingEdge, true), "edgeGrabRt"},
	{ std::pair(PlayerState::HangingFromEdge, true), "idleEdgeRt"},
		{ std::pair(PlayerState::WallSliding, true), "wallSlideRt"},
	{ std::pair(PlayerState::Crouching, true), "crouchRt"},
		{ std::pair(PlayerState::Dashing, true), "dashRt"},
		{ std::pair(PlayerState::DashAttacking, true), "dashAttackRt"},
	{ std::pair(PlayerState::Sliding, true), "slideRt"},
		{ std::pair(PlayerState::LadderClimbing, true), "ladderGrabRt"},
		{ std::pair(PlayerState::Idle, false), "idleLt"},
	{ std::pair(PlayerState::Running, false), "runLt"},
		{ std::pair(PlayerState::Attacking, false), "attackLt"},
	{ std::pair(PlayerState::Dying, false), "deathLt"},
		{ std::pair(PlayerState::Damaged, false), "hurtLt"},
	{ std::pair(PlayerState::Jumping, false), "jumpLt"},
		{ std::pair(PlayerState::PeakingJump, false), "upToFallLt"},
	{ std::pair(PlayerState::Falling, false), "fallLt"},
		{ std::pair(PlayerState::GrabbingEdge, false), "edgeGrabLt"},
	{ std::pair(PlayerState::HangingFromEdge, false), "idleEdgeLt"},
		{ std::pair(PlayerState::WallSliding, false), "wallSlideLt"},
	{ std::pair(PlayerState::Crouching, false), "crouchLt"},
		{ std::pair(PlayerState::Dashing, false), "dashLt"},
		{ std::pair(PlayerState::DashAttacking, false), "dashAttackLt"},
	{ std::pair(PlayerState::Sliding, false), "slideLt"},
		{ std::pair(PlayerState::LadderClimbing, false), "ladderGrabLt"}
};



std::map<std::pair<AnimType, std::string>, std::variant<PlayerState, GoblinState> > Cfg::goblinAnimStateLookup = {
	{ std::pair{AnimType::Goblin,"idleRt"}, GoblinState::Idle },
	{ std::pair{AnimType::Goblin,"runRt"}, GoblinState::Running },
	{ std::pair{AnimType::Goblin,"attackRt"}, GoblinState::Attacking },
	{ std::pair{AnimType::Goblin,"hurtRt"}, GoblinState::Damaged },
	{ std::pair{AnimType::Goblin,"deathRt"}, GoblinState::Dying },
	{ std::pair{AnimType::Goblin,"idleLt"}, GoblinState::Idle },
	{ std::pair{AnimType::Goblin,"runLt"}, GoblinState::Running },
	{ std::pair{AnimType::Goblin,"attackLt"}, GoblinState::Attacking },
	{ std::pair{AnimType::Goblin,"hurtLt"}, GoblinState::Damaged },
	{ std::pair{AnimType::Goblin,"deathLt"}, GoblinState::Dying }
};

std::map<std::pair<std::variant<PlayerState, GoblinState>, bool>, std::string> Cfg::goblinStateStringLookup = {
	{ std::pair(GoblinState::Idle, true), "idleRt"},
	{ std::pair(GoblinState::Running, true), "runRt"},
		{ std::pair(GoblinState::Attacking, true), "attackRt"},
		{ std::pair(GoblinState::Damaged, true), "hurtRt"},
	{ std::pair(GoblinState::Dying, true), "deathRt"},
		{ std::pair(GoblinState::Idle, false), "idleLt"},
	{ std::pair(GoblinState::Running, false), "runLt"},
		{ std::pair(GoblinState::Attacking, false), "attackLt"},
		{ std::pair(GoblinState::Damaged, false), "hurtLt"},
	{ std::pair(GoblinState::Dying, false), "deathLt"},
};


void Cfg::Initialize()
{
    initTextures();
    initFonts();
    initMusic();
    initSounds();
	initPlayerInputs();


 
}

void Cfg::initMusic()
{
	music.load((int)Music::Intro, "assets/music/Intro.mp3");
}

void Cfg::initSounds()
{
	
	sounds.load((int)Sounds::Sword1, "assets/sound/combat/Sword1.ogg");
	sounds.load((int)Sounds::Sword2, "assets/sound/combat/Sword2.ogg");
	sounds.load((int)Sounds::GoblinAtk1, "assets/sound/combat/goblin/attack.mp3");
	sounds.load((int)Sounds::GoblinDeath, "assets/sound/combat/goblin/death.ogg");
	sounds.load((int)Sounds::GoblinHurt, "assets/sound/combat/goblin/hurt.ogg");
	sounds.load((int)Sounds::GoblinDie1, "assets/sound/combat/goblin/die1.wav");
	sounds.load((int)Sounds::GoblinYell, "assets/sound/combat/goblin/hit.wav");
	sounds.load((int)Sounds::GoblinScream, "assets/sound/combat/goblin/scream.mp3");
	sounds.load((int)Sounds::Sword3, "assets/sound/combat/Sword3.ogg");
	sounds.load((int)Sounds::PlayerHit, "assets/sound/combat/SwordHit2.ogg");
	sounds.load((int)Sounds::GoblinHit, "assets/sound/combat/SwordHit3.ogg");
	sounds.load((int)Sounds::FootstepDirt, "assets/sound/environment/Footsteps.ogg");


}

void Cfg::initTextures()
{
	textures.load((int)Cfg::Textures::PlayerAtlas, "assets/textures/actors/player/WarriorBig3_229x132.png");
	textures.get((int)Textures::PlayerAtlas).setSmooth(true);
	textures.load((int)Cfg::Textures::GoblinAtlas, "assets/textures/actors/enemies/goblinAtlas300x300.png");
	textures.get((int)Textures::GoblinAtlas).setSmooth(true);
	textures.load((int)Cfg::Textures::BG1_1, "assets/textures/bgs/bg1/bgLayer1.png");
	textures.load((int)Cfg::Textures::BG1_2, "assets/textures/bgs/bg1/bgLayer2.png");
	textures.load((int)Cfg::Textures::BG1_3, "assets/textures/bgs/bg1/bgLayer3.png");
	textures.load((int)Cfg::Textures::BG1_4, "assets/textures/bgs/bg1/bgLayer4.png");
	textures.load((int)Cfg::Textures::BG1_5, "assets/textures/bgs/bg1/bgLayer5.png");
	textures.load((int)Cfg::Textures::Logo, "assets/textures/bgs/logoImg.png");
	textures.load((int)Cfg::Textures::RetroMenu, "assets/textures/GUI/RetroMenu.png");



}

void Cfg::initPlayerInputs()
{
	// realtime events
	// Keyboard pressed commands
	playerInputs.map(Cfg::PlayerInputs::X, Action(sf::Keyboard::Num9));
	playerInputs.map(Cfg::PlayerInputs::Y, Action(sf::Keyboard::X));
	playerInputs.map(Cfg::PlayerInputs::A, Action(sf::Keyboard::Num0));
	playerInputs.map(Cfg::PlayerInputs::B, Action(sf::Keyboard::Space));
	playerInputs.map(Cfg::PlayerInputs::L1, Action(sf::Keyboard::Num7));
	playerInputs.map(Cfg::PlayerInputs::R1, Action(sf::Keyboard::Add));
	// menu controls
	playerInputs.map(Cfg::PlayerInputs::Start, Action(sf::Keyboard::Enter));
	playerInputs.map(Cfg::PlayerInputs::Select, Action(sf::Keyboard::Backspace));
	// direction controls
	playerInputs.map(Cfg::PlayerInputs::Up, Action(sf::Keyboard::Up));
	playerInputs.map(Cfg::PlayerInputs::Down, Action(sf::Keyboard::Down));
	playerInputs.map(Cfg::PlayerInputs::Left, Action(sf::Keyboard::Left));
	playerInputs.map(Cfg::PlayerInputs::Right, Action(sf::Keyboard::Right));

	// Joystick Controls
	// Axis mappings
	playerInputs.map(Cfg::PlayerInputs::AxisX, Action(sf::Joystick::Axis::X, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map(Cfg::PlayerInputs::AxisY, Action(sf::Joystick::Axis::Y, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map(Cfg::PlayerInputs::DPadX, Action(sf::Joystick::Axis::PovX, Action::Type::RealTime | Action::Type::Tilted));
	playerInputs.map(Cfg::PlayerInputs::DPadY, Action(sf::Joystick::Axis::PovY, Action::Type::RealTime | Action::Type::Tilted));
	// Button mappings
	playerInputs.map(Cfg::PlayerInputs::JoyA, Action(JoystickBtn::A, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyB, Action(JoystickBtn::B, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyX, Action(JoystickBtn::X, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyY, Action(JoystickBtn::Y, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyL1, Action(JoystickBtn::L1, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyR1, Action(JoystickBtn::R1, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoyStart, Action(JoystickBtn::Start, Action::Type::RealTime | Action::Type::Pressed));
	playerInputs.map(Cfg::PlayerInputs::JoySelect, Action(JoystickBtn::Select, Action::Type::RealTime | Action::Type::Pressed));

}

void Cfg::initFonts()
{
	fonts.load((int)Cfg::Fonts::Font1, "assets/fonts/frisky_puppy.ttf");
	fonts.load((int)Cfg::Fonts::Mickey, "assets/fonts/MM.otf");

}