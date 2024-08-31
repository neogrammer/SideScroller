#ifndef MENUOBJECT_H__
#define MENUOBJECT_H__
#include <unordered_map>
#include <string>
#include <core/globals.h>
#include <memory>

enum class PatchPiece : unsigned int
{
	TL=0,
	T=1,
	TR=2,
	R=3,
	BR=4,
	B=5,
	BL=6,
	L=7,
	C=8,
	Count=9
};

class MenuObject
{
protected:
	static sf::Texture* patchedGuiSpr;
	static sf::Sprite patches[(unsigned int)PatchPiece::Count];

	std::unique_ptr<sf::Texture> builtMenuTexture;
	std::unique_ptr<sf::Sprite> builtSpr;
	std::string name;
	bool enabled{ true };
	int32_t id{ -1 };
	int32_t totalRows{ 0 };
	int32_t topVisibleRow{ 0 };

	sf::Vector2i cellTable{ 1,0 };
	sf::Vector2i cellSize{ 0,0 };
	sf::Vector2i cellPadding{ 2,0 };

	const sf::Vector2i patchSize{ gGuiPatch, gGuiPatch };
	sf::Vector2i sizeInPatches{ 0,0 };

	std::unordered_map<std::string, size_t> itemPointer;
	std::vector<MenuObject> items;
public:
	MenuObject();
	MenuObject(const std::string& name_);
	~MenuObject() = default;
	MenuObject(const MenuObject&) = default;
	MenuObject& operator=(const MenuObject&) = default;
	MenuObject(MenuObject&&) = default;
	MenuObject& operator=(MenuObject&&) = default;

	MenuObject& setTable(int cols_, int rows_);
	MenuObject& setID(int32_t id_);
	MenuObject& enable(bool b_);
	std::string& getName();
	uint32_t getID();
	sf::Vector2i getSize();
	void setName(const std::string& name_);

	bool hasItems();
	void render(sf::Vector2i screenOffset_);
	void build();
	static void setupPatches();
	static sf::Sprite& getPatch(PatchPiece piece_);

	MenuObject& operator[](const std::string& name_);

};

namespace gui
{
	std::unique_ptr<sf::Texture> makeGuiTex(sf::Vector2i sizeInPatches_, int numCols = 1);
}

#endif