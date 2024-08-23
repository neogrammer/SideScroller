#include <core/Cfg.h>
#include <core/Game.h>
int main()
{
	Cfg::Initialize();

	Game demo;

	demo.run();
	
	return 0;
}