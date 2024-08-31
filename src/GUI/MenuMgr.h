#ifndef MENUMGR_H__
#define MENUMGR_H__
#include <list>
#include <GUI/MenuObject.h>
class MenuMgr
{

	std::list<MenuObject*> panels;

public:
	MenuMgr() = default;

	void open(MenuObject* mo_);
	void close();
	void onUp();
	void onDown();
	void onLeft();
	void onRight();
	void onBack();
	MenuObject* onConfirm();
	bool isOpen();
	void render(sf::Vector2i screenOffset_);



};

#endif