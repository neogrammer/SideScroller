#include "MenuObject.h"
#include <SFML/Graphics/Sprite.hpp>

sf::Texture* MenuObject::patchedGuiSpr = nullptr;
sf::Sprite MenuObject::patches[(unsigned int)PatchPiece::Count] = { sf::Sprite{}, };

MenuObject::MenuObject()
	: name{"root"}
	, builtMenuTexture{}
	, builtSpr{std::make_unique<sf::Sprite>()}
{
	
	
}

MenuObject::MenuObject(const std::string& name_)
	: name{name_}
	, builtMenuTexture{}
	, builtSpr{ std::make_unique<sf::Sprite>() }
{
	
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

std::string& MenuObject::getName()
{
	return name;
}

uint32_t MenuObject::getID()
{
	return id;
}

sf::Vector2i MenuObject::getSize()
{
	return { int(int32_t(name.size())), 1 };
}

bool MenuObject::hasItems()
{
	return !items.empty();
}



void MenuObject::build()
{
	for (auto& i : items)
	{
		if (i.second.hasItems())
		{
			i.second.build();
		}

		// longest child name determines cell width
		cellSize.x = std::max(i.second.getSize().x, cellSize.x);
		cellSize.y = std::max(i.second.getSize().y, cellSize.y);

	}

	//if (cellSize.x == 0 || cellSize.y == 0)
	//{
	//	cellSize = { 3, 3 };
	//}

	// Adjust size of this object (in patches) if it rendered as a panel
	sizeInPatches.x = cellTable.x * cellSize.x + (cellTable.x - 1) * cellPadding.x + 2;
	sizeInPatches.y = cellTable.y * cellSize.y + (cellTable.y - 1) * cellPadding.y + 2;

	totalRows = (int32_t)((items.size() / cellTable.x) + (((items.size() % cellTable.x) > 0) ? 1 : 0));
	if (totalRows == 0)
		totalRows = 1;

	builtMenuTexture.create(unsigned int(sizeInPatches.x * gGuiPatch) , unsigned int(sizeInPatches.y * gGuiPatch));

	builtMenuTexture.clear(sf::Color::Transparent);


	sf::Vector2i patchPos{ 0,0 };
	for (patchPos.x = 0; patchPos.x < sizeInPatches.x; patchPos.x++)
	{
		for (patchPos.y = 0; patchPos.y < sizeInPatches.y; patchPos.y++)
		{
			// determine position in screen space
			sf::Vector2i textureLocation = patchPos * gGuiPatch;
			sf::Vector2i sourcePatch{ 0,0 };
			if (patchPos.x > 0) sourcePatch.x = 1;
			if (patchPos.x == sizeInPatches.x - 1) sourcePatch.x = 2;
			if (patchPos.y > 0) sourcePatch.y = 1;
			if (patchPos.y == sizeInPatches.y - 1) sourcePatch.y = 2;

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

			sf::Sprite& sprToDraw = getPatch(currentOneToCopy);
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
	builtSpr->setTexture(builtMenuTexture.getTexture());
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

void MenuObject::render(sf::Vector2i screenOffset_)
{
	builtSpr->setPosition({ (float)screenOffset_.x,(float)screenOffset_.y });

	gWnd.draw(*builtSpr);

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

}

MenuObject& MenuObject::operator[](const std::string& name_)
{
	return items[name_];
}

