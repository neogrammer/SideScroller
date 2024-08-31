#include <GUI/MenuMgr.h>
#include <core/globals.h>

void MenuMgr::open(MenuObject* mo_)
{
	close();
	panels.push_back(mo_);
}

void MenuMgr::close()
{
	panels.clear();
}

bool MenuMgr::isOpen()
{
	return !panels.empty();
}

void MenuMgr::onUp()
{
	if (!panels.empty()) 
		panels.back()->onUp();
}

void MenuMgr::onDown()
{
	if (!panels.empty())
		panels.back()->onDown();
}

void MenuMgr::onLeft()
{
	if (!panels.empty())
		panels.back()->onLeft();
}

void MenuMgr::onRight()
{
	if (!panels.empty())
		panels.back()->onRight();
}

void MenuMgr::onBack()
{
	if (!panels.empty())
		panels.pop_back();
}

MenuObject* MenuMgr::onConfirm()
{
	if (panels.empty()) return nullptr;

	MenuObject* next = panels.back()->onConfirm();

	if (next == panels.back())
	{
		if (panels.back()->getSelectedItem()->isEnabled())
			return panels.back()->getSelectedItem();
	}
	else
	{
		if (next->isEnabled())
			panels.push_back(next);
	}

	return nullptr;
}

void MenuMgr::render(sf::Vector2i screenOffset_)
{
	if (panels.empty()) return;

	for (auto& p : panels)
	{
		p->render(screenOffset_);
		screenOffset_ += {10, 10};
	}

	sf::Sprite markerSpr{ sf::Sprite{} };
	markerSpr.setTexture(Cfg::textures.get((int)Cfg::Textures::RetroMenu));
	markerSpr.setTextureRect({ { 4 * gGuiPatch, 0},{2 * gGuiPatch,2 * gGuiPatch} });
	markerSpr.setPosition(sf::Vector2f(panels.back()->getCursorPos()));
	gWnd.draw(markerSpr);
}


