#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <string>
#include <core/Cfg.h>
#include <core/rec.h>
#include <memory>
extern sf::RenderWindow gWnd;
extern sf::ContextSettings gWndSettings;
extern sf::Vector2f mpos;
extern unsigned int gWW;
extern unsigned int gWH;
extern bool gWndFull;

extern float gTime;
extern float gPrevTime;

extern sf::View gameView;
extern std::stack<std::unique_ptr<sf::Sprite> > bgLayers;
extern std::stack<std::unique_ptr<sf::Sprite> > loopLayers;

extern std::unique_ptr<GameStateMgr> gStateMgr;
extern std::stack< std::unique_ptr<sf::Text> > gDamageNumbers;
extern std::stack< float > gDmgElapsed;
extern float gDmgDelay;



extern bool gGroundMoved;
extern float gDistGroundMoved;

namespace wndw
{
	extern void CreateWindow(std::string title_, unsigned int w_, unsigned int h_);
	
}

namespace snd
{
	extern void PlayDieSound();
}




namespace phys
{
	extern std::unique_ptr<sf::Sprite> spr(rec& r);

	extern bool PointVsRect(const sf::Vector2f& p, const rec& r);

	extern bool RectVsRect(const rec& r1, const rec& r2);

	extern bool RayVsRect(const sf::Vector2f& ray_origin, const sf::Vector2f& ray_dir, const rec& target, sf::Vector2f& contact_point, sf::Vector2f& contact_normal, float& t_hit_near);

	extern bool DynamicRectVsRect(const rec& in, const rec& target, sf::Vector2f& contact_point, sf::Vector2f& contact_normal, float& contact_time, float fElapsedTime);
}
