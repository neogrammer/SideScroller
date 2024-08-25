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

std::map<std::pair<AnimType, std::string>, std::variant<PlayerState> > Cfg::animStateLookup = {
	{ std::pair{AnimType::Player,"idleRt"}, PlayerState::Idle },
	{ std::pair{AnimType::Player,"runRt"}, PlayerState::Running },
	{ std::pair{AnimType::Player,"attackRt"}, PlayerState::Attacking },
	{ std::pair{AnimType::Player,"deathRt"}, PlayerState::Dying },
	{ std::pair{AnimType::Player,"hurtRt"}, PlayerState::Damaged },
	{ std::pair{AnimType::Player,"jumpRt"}, PlayerState::Jumping },
	{ std::pair{AnimType::Player,"upToFallRt"}, PlayerState::Falling },
	{ std::pair{AnimType::Player,"fallRt"}, PlayerState::Falling },
	{ std::pair{AnimType::Player,"edgeGrabRt"}, PlayerState::HangingFromEdge },
	{ std::pair{AnimType::Player,"idleEdgeRt"}, PlayerState::HangingFromEdge },
	{ std::pair{AnimType::Player,"wallSlideRt"}, PlayerState::WallKicking },
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
	{ std::pair{AnimType::Player,"upToFallLt"}, PlayerState::Falling },
	{ std::pair{AnimType::Player,"fallLt"}, PlayerState::Falling },
	{ std::pair{AnimType::Player,"edgeGrabLt"}, PlayerState::HangingFromEdge },
	{ std::pair{AnimType::Player,"idleEdgeLt"}, PlayerState::HangingFromEdge },
	{ std::pair{AnimType::Player,"wallSlideLt"}, PlayerState::WallKicking },
	{ std::pair{AnimType::Player,"crouchLt"}, PlayerState::Crouching },
	{ std::pair{AnimType::Player,"dashLt"}, PlayerState::Dashing },
	{ std::pair{AnimType::Player,"dashAttackLt"}, PlayerState::DashAttacking },
	{ std::pair{AnimType::Player,"slideLt"}, PlayerState::Sliding },
	{ std::pair{AnimType::Player,"ladderGrabLt"}, PlayerState::LadderClimbing }
};

std::map<std::variant<PlayerState>, std::string> Cfg::stateStringLookup = {
	{ PlayerState::Idle, "idle"},
	{ PlayerState::Running, "running"}
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
   
}

void Cfg::initSounds()
{
	

}

void Cfg::initTextures()
{
	textures.load((int)Cfg::Textures::PlayerAtlas, "assets/textures/actors/player/WarriorBig3.png");
	textures.load((int)Cfg::Textures::BG1_1, "assets/textures/bgs/bg1/bgLayer1.png");
	textures.load((int)Cfg::Textures::BG1_2, "assets/textures/bgs/bg1/bgLayer2.png");
	textures.load((int)Cfg::Textures::BG1_3, "assets/textures/bgs/bg1/bgLayer3.png");
	textures.load((int)Cfg::Textures::BG1_4, "assets/textures/bgs/bg1/bgLayer4.png");
	textures.load((int)Cfg::Textures::BG1_5, "assets/textures/bgs/bg1/bgLayer5.png");
	textures.load((int)Cfg::Textures::Logo, "assets/textures/bgs/logoImg.png");


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
}