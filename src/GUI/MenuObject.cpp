#include "MenuObject.h"
#include <SFML/Graphics/Sprite.hpp>

sf::Texture* MenuObject::patchedGuiSpr = nullptr;
sf::Sprite MenuObject::patches[(unsigned int)PatchPiece::Count] = { sf::Sprite{}, };

MenuObject::MenuObject()
	: name{"root"}
	, builtMenuTexture{std::make_unique<sf::Texture>()}
	, builtSpr{std::make_unique<sf::Sprite>()}
{
	
	
}

MenuObject::MenuObject(const std::string& name_)
	: name{name_}
	, builtMenuTexture{ std::make_unique<sf::Texture>() }
	, builtSpr{ std::make_unique<sf::Sprite>() }
{
	
}

void MenuObject::onUp()
{
	cellCursor.y--;
	if (cellCursor.y < 0) cellCursor.y = 0;

	if (cellCursor.y < topVisibleRow)
	{
		topVisibleRow--;
		if (topVisibleRow < 0) topVisibleRow = 0;
	}

	clampCursor();
}

void MenuObject::onDown()
{
	cellCursor.y++;
	if (cellCursor.y == totalRows) cellCursor.y = totalRows - 1;

	if (cellCursor.y > topVisibleRow + cellTable.y - 1)
	{
		topVisibleRow++;
		if (topVisibleRow > totalRows - cellTable.y)
			topVisibleRow = totalRows - cellTable.y;
	}

	clampCursor();
}

void MenuObject::onLeft()
{
	cellCursor.x--;
	if (cellCursor.x < 0) cellCursor.x = 0;
	clampCursor();
}

void MenuObject::onRight()
{
	cellCursor.x++;
	if (cellCursor.x > cellTable.x - 1) cellCursor.x = cellTable.x - 1;
	clampCursor();
}

void MenuObject::onBack()
{
}

MenuObject* MenuObject::onConfirm()
{
	if (items[cursorItem].hasItems())
	{
		return &items[cursorItem];
	}
	else
	{
		return this;
	}
}

MenuObject& MenuObject::setTable(int cols_, int rows_)
{
	cellTable = { cols_, rows_ };
	return *this;
}



MenuObject& MenuObject::setID(int32_t id_)
{
	id = id_;
	return *this;
}

MenuObject& MenuObject::enable(bool b_)
{
	enabled = b_;
	return *this;
}

bool MenuObject::isEnabled()
{
	return enabled;
}

std::string MenuObject::getName()
{
	return name;
}

uint32_t MenuObject::getID()
{
	return id;
}

sf::Vector2i MenuObject::getSize()
{
	int num = (int)name.length();
	int wid = num * Cfg::fonts.get((int)Cfg::Fonts::Mickey).getGlyph(sf::Uint32(41), 24U, false).textureRect.width;
	float widF = std::ceilf((float)wid / (float)gGuiPatch);
	return { (int)widF, 1};
}

void MenuObject::setName(const std::string& name_)
{
	name = name_;
}

bool MenuObject::hasItems()
{
	return !items.empty();
}



void MenuObject::build()
{
	for (auto& i : items)
	{
		if (i.hasItems())
		{
			i.build();
		}

		// longest child name determines cell width
		cellSize.x = std::max(i.getSize().x, cellSize.x);
		cellSize.y = std::max(i.getSize().y, cellSize.y);

	}

	//if (cellSize.x == 0 || cellSize.y == 0)
	//{
	//	cellSize = { 3, 3 };
	//}
	

	// Adjust size of this object (in patches) if it rendered as a panel
	sizeInPatches.x = cellTable.x * cellSize.x + (cellTable.x - 1) * cellPadding.x + 2;

		//cellTable.x * cellSize.x + (cellTable.x - 1) * cellPadding.x + 2;
	sizeInPatches.y = cellTable.y * cellSize.y + (cellTable.y - 1) * cellPadding.y + 2;
		//cellTable.y * cellSize.y + (cellTable.y - 1) * cellPadding.y + 2;
	
	totalRows = (int32_t)((items.size() / cellTable.x) + (((items.size() % cellTable.x) > 0) ? 1 : 0));
	/*if (totalRows == 0)
		totalRows = 1;*/

	
	builtMenuTexture = std::move(gui::makeGuiTex(sizeInPatches, cellTable.x));
	builtSpr->setTexture(*builtMenuTexture);
}

void MenuObject::setupPatches()
{
	patchedGuiSpr = &Cfg::textures.get((int)Cfg::Textures::RetroMenu);

	for (unsigned int i = 0; i < (unsigned int)PatchPiece::Count; i++)
	{
		patches[i].setTexture(Cfg::textures.get((int)Cfg::Textures::RetroMenu));

		switch ((PatchPiece)i)
		{
		case PatchPiece::TL:
		{
			patches[i].setTextureRect({ {0,0},{24,24} });
		}
		break;
		case PatchPiece::T:
		{
			patches[i].setTextureRect({ {24,0},{24,24} });

		}
		break;
		case PatchPiece::TR:
		{
			patches[i].setTextureRect({ {48,0},{24,24} });

		}
		break;
		case PatchPiece::R:
		{
			patches[i].setTextureRect({ {48,24},{24,24} });

		}
		break;
		case PatchPiece::BR:
		{
			patches[i].setTextureRect({ {48,48},{24,24} });

		}
		break;
		case PatchPiece::B:
		{
			patches[i].setTextureRect({ {24,48},{24,24} });

		}
		break;
		case PatchPiece::BL:
		{
			patches[i].setTextureRect({ {0,48},{24,24} });

		}
		break;
		case PatchPiece::L:
		{
			patches[i].setTextureRect({ {0,24},{24,24} });

		}
		break;
		case PatchPiece::C:
		{
			patches[i].setTextureRect({ {24,24},{24,24} });

		}
		break;
		break;
		default:
			break;
		}
	}
}

sf::Sprite& MenuObject::getPatch(PatchPiece piece_)
{
	return (patches[(unsigned int)piece_]);
}

void MenuObject::clampCursor()
{
	cursorItem = cellCursor.y * cellTable.x + cellCursor.x;
	if (cursorItem >= int32_t(items.size()))
	{
		cellCursor.y = ((int)items.size() / cellTable.x);
		cellCursor.x = ((int)items.size() % cellTable.x) - 1;
		cursorItem = (int32_t)(items.size() - 1);
	}
}

sf::Vector2i MenuObject::getCursorPos()
{
	return cursorPos;
}

MenuObject* MenuObject::getSelectedItem()
{
	return &items[cursorItem];
}

void MenuObject::render(sf::Vector2i screenOffset_)
{

		builtSpr->setPosition({ (float)screenOffset_.x,(float)screenOffset_.y });
		gWnd.draw(*builtSpr);

		sf::Text txt{ sf::Text{} };
		txt.setFont(Cfg::fonts.get((int)Cfg::Fonts::Mickey));
		txt.setFillColor(sf::Color::White);
		txt.setOutlineColor(sf::Color::Black);
		txt.setOutlineThickness(2);
		txt.setCharacterSize(24U);
		sf::Vector2i patchPos{ 1,1 };
		sf::Vector2i cell{ 0,0 };
		//for (auto& m : items)
		//{
		//	// Patch location (including border offset and padding)
		//	patchPos.x = cell.x * (cellSize.x + cellPadding.x) + 1;
		//	patchPos.y = cell.y * (cellSize.y + cellPadding.y) + 1;
		//	// Actual screen location in pixel
		//	sf::Vector2i screenLocation = patchPos * gGuiPatch + screenOffset_;
		//	txt.setString(m.getName());
		//	txt.setPosition(sf::Vector2f(screenLocation));
		//	gWnd.draw(txt);
		//	cell.y++;
		//}
		
		// work out visible items
		int32_t topLeftItem = topVisibleRow * cellTable.x;
		int32_t bottomRightItem = cellTable.y * cellTable.x + topLeftItem;

		// clamp to stay in bounds
		bottomRightItem = std::min(int32_t(items.size()), bottomRightItem);
		int32_t visibleItems = bottomRightItem - topLeftItem;

		// scroll markers
		if (topVisibleRow > 0)
		{
			patchPos = { sizeInPatches.x - 1, 0 };
			sf::Vector2f screenLocation = sf::Vector2f{ (float)(patchPos.x * gGuiPatch + (int)screenOffset_.x), (float)(patchPos.y * gGuiPatch + (int)screenOffset_.y) };
			sf::Vector2i sourcePatch = { 3,0 };
			sf::Sprite markerSpr{ sf::Sprite{} };
			markerSpr.setTexture(Cfg::textures.get((int)Cfg::Textures::RetroMenu));
			markerSpr.setTextureRect({ {sourcePatch.x * gGuiPatch, sourcePatch.y * gGuiPatch},{gGuiPatch,gGuiPatch} });
			markerSpr.setPosition(screenLocation);
			gWnd.draw(markerSpr);
		}

		if ((totalRows - topVisibleRow) > cellTable.y)
		{
			patchPos = { sizeInPatches.x - 1, sizeInPatches.y - 1 };
			sf::Vector2f screenLocation = sf::Vector2f{ (float)(patchPos.x * gGuiPatch + (int)screenOffset_.x ), (float)(patchPos.y * gGuiPatch + (int)screenOffset_.y) };
			sf::Vector2i sourcePatch = { 3,2 };
			sf::Sprite markerSpr{ sf::Sprite{} };
			markerSpr.setTexture(Cfg::textures.get((int)Cfg::Textures::RetroMenu));
			markerSpr.setTextureRect({ {sourcePatch.x * gGuiPatch, sourcePatch.y * gGuiPatch},{gGuiPatch,gGuiPatch} });
			markerSpr.setPosition(screenLocation);
			gWnd.draw(markerSpr);
		}


		for (int32_t i = 0; i < visibleItems; i++)
		{
			cell.x = i % cellTable.x;
			cell.y = i / cellTable.x;


			patchPos.x = cell.x * (cellSize.x + cellPadding.x) * 1;
			patchPos.y = cell.y * (cellSize.y + cellPadding.y) + 1;

			sf::Vector2f screenLocation{ (float)(patchPos.x * gGuiPatch + screenOffset_.x) , (float)(patchPos.y * gGuiPatch + screenOffset_.y) };

			txt.setString(items[i + topLeftItem].name);
			txt.setPosition( sf::Vector2f(screenLocation.x + gGuiPatch, screenLocation.y));

			if (items[topLeftItem + i].enabled)
			{
				txt.setFillColor(sf::Color::White);
				txt.setOutlineColor(sf::Color::Black);
			}
			else
			{
				txt.setFillColor(sf::Color(55, 55, 55, 255));
				txt.setOutlineColor(sf::Color(55, 55, 55, 255));
			}

			gWnd.draw(txt);

			if (items[topLeftItem + i].hasItems())
			{
				patchPos.x = cell.x * (cellSize.x + cellPadding.x) + 1 + cellSize.x;
				patchPos.x = cell.y * (cellSize.y + cellPadding.y) + 1;
				sf::Vector2i sourcePatch = { 3, 1 };
				screenLocation = { (float)patchPos.x * (float)gGuiPatch + (float)screenOffset_.x + (items[topLeftItem + i].getSize().x * gGuiPatch) ,(float)patchPos.y* (float)gGuiPatch + (float)screenOffset_.y };

				sf::Sprite markerSpr{ sf::Sprite{} };
				markerSpr.setTexture(Cfg::textures.get((int)Cfg::Textures::RetroMenu));
				markerSpr.setTextureRect({ {sourcePatch.x * gGuiPatch, sourcePatch.y * gGuiPatch},{gGuiPatch,gGuiPatch} });
				markerSpr.setPosition(screenLocation);
				gWnd.draw(markerSpr);

			}

			
		}

		cursorPos.x = (cellCursor.x * (cellSize.x + cellPadding.x)) * gGuiPatch + screenOffset_.x - gGuiPatch;
		cursorPos.y = ((cellCursor.y - topVisibleRow) * (cellSize.y + cellPadding.y)) * gGuiPatch + screenOffset_.y + gGuiPatch;
	

}
	

	//sf::Sprite& spr0{ MenuObject::patches[(unsigned int)PatchPiece::TL]};
	//sf::Sprite& spr1{ MenuObject::patches[(unsigned int)PatchPiece::T] };
	//sf::Sprite& spr2{ MenuObject::patches[(unsigned int)PatchPiece::TR] };
	//sf::Sprite& spr3{ MenuObject::patches[(unsigned int)PatchPiece::R] };
	//sf::Sprite& spr4{ MenuObject::patches[(unsigned int)PatchPiece::BR] };
	//sf::Sprite& spr5{ MenuObject::patches[(unsigned int)PatchPiece::B] };
	//sf::Sprite& spr6{ MenuObject::patches[(unsigned int)PatchPiece::BL] };
	//sf::Sprite& spr7{ MenuObject::patches[(unsigned int)PatchPiece::L] };
	//sf::Sprite& spr8{ MenuObject::patches[(unsigned int)PatchPiece::C] };

	//spr0.setPosition(0, 0);
	//spr1.setPosition(24,0);
	//spr2.setPosition(48,0);
	//spr3.setPosition(48, 24);
	//spr4.setPosition(48, 48);
	//spr5.setPosition(24, 48);
	//spr6.setPosition(0, 48);
	//spr7.setPosition(0, 24);
	//spr8.setPosition(24, 24);



	//gWnd.draw(spr0);
	//gWnd.draw(spr1);
	//gWnd.draw(spr2);
	//gWnd.draw(spr3);
	//gWnd.draw(spr4);
	//gWnd.draw(spr5);
	//gWnd.draw(spr6);
	//gWnd.draw(spr7);
	//gWnd.draw(spr8);
	//change


MenuObject& MenuObject::operator[](const std::string& name_)
{
	if (itemPointer.count(name_) == 0)
	{
		itemPointer[name_] = items.size();
		items.push_back(MenuObject(name_));
	}

	return items[itemPointer[name_] ];
}

std::unique_ptr<sf::Texture> gui::makeGuiTex(sf::Vector2i sizeInPatches_, int numCols)
{
	sf::RenderTexture builtMenuTexture = {};
	std::unique_ptr<sf::Texture> tex{ nullptr };
	if (numCols <= 1)
		numCols = 2;
	sizeInPatches_.x += numCols - 1;

	builtMenuTexture.create(unsigned int(sizeInPatches_.x * gGuiPatch), unsigned int(sizeInPatches_.y * gGuiPatch));

	builtMenuTexture.clear(sf::Color::Transparent);


	sf::Vector2i patchPos{ 0,0 };
	for (patchPos.x = 0; patchPos.x < sizeInPatches_.x; patchPos.x++)
	{
		for (patchPos.y = 0; patchPos.y < sizeInPatches_.y; patchPos.y++)
		{
			// determine position in screen space

			sf::Vector2i sourcePatch{ 0,0 };
			if (patchPos.x > 0) sourcePatch.x = 1;
			if (patchPos.x == sizeInPatches_.x - 1) sourcePatch.x = 2;
			if (patchPos.y > 0) sourcePatch.y = 1;
			if (patchPos.y == sizeInPatches_.y - 1) sourcePatch.y = 2;

			PatchPiece currentOneToCopy = PatchPiece::Count;
			switch (sourcePatch.x)
			{
			case 0:
			{
				if (sourcePatch.y == 0)
				{
					currentOneToCopy = PatchPiece::TL;
				}
				else if (sourcePatch.y == 1)
				{
					currentOneToCopy = PatchPiece::L;
				}
				else if (sourcePatch.y == 2)
				{
					currentOneToCopy = PatchPiece::BL;
				}

			}
			break;
			case 1:
			{
				if (sourcePatch.y == 0)
				{
					currentOneToCopy = PatchPiece::T;
				}
				else if (sourcePatch.y == 1)
				{
					currentOneToCopy = PatchPiece::C;
				}
				else if (sourcePatch.y == 2)
				{
					currentOneToCopy = PatchPiece::B;
				}

			}
			break;
			case 2:
			{
				if (sourcePatch.y == 0)
				{
					currentOneToCopy = PatchPiece::TR;
				}
				else if (sourcePatch.y == 1)
				{
					currentOneToCopy = PatchPiece::R;
				}
				else if (sourcePatch.y == 2)
				{
					currentOneToCopy = PatchPiece::BR;
				}

			}
			break;
			default:
				break;
			}

			sf::Sprite& sprToDraw = MenuObject::getPatch(currentOneToCopy);
			sprToDraw.setPosition({ (float)(patchPos.x * gGuiPatch),(float)(patchPos.y * gGuiPatch) });
			builtMenuTexture.draw(sprToDraw);
			//sf::Sprite test{};
			//test.setTexture(builtMenuTexture.getTexture());
			//test.setTextureRect({ { (int)(patchPos.x * gGuiPatch),(int)(patchPos.y * gGuiPatch)}, {24,24}});
			//test.setPosition({ (float)(patchPos.x * gGuiPatch),(float)(patchPos.y * gGuiPatch) });
			//gWnd.clear();
			//gWnd.draw(test);
			//gWnd.display();

		}
	}

	tex = std::make_unique<sf::Texture>();
	tex->create(builtMenuTexture.getTexture().getSize().x, builtMenuTexture.getTexture().getSize().y);
	tex->swap(*const_cast<sf::Texture*>(&builtMenuTexture.getTexture()));
	return std::move(tex);
}
