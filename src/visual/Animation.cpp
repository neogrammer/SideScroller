#include <visual/Animation.h>
#include <core/globals.h>
void Animation::animate()
{
	if (data.playing)
	{
		animTimer += gTime;
		if (animTimer > data.frameDelay)
		{
			animTimer = 0.f;
		
		data.frameIdx++;
		if (data.frameIdx >= data.numFrames)
		{
			if (data.looping)
			{
				data.frameIdx = 0U;
			}
			else
			{
				// TO BE IMPLEMENTED
				data.frameIdx -= 1;
				data.playing = false;
			}
		}
		}
	}
}
bool Animation::isOnLastFrame()
{
	return (data.frameIdx == data.numFrames - 1);
}
void Animation::LoadAnim(std::ifstream& animData)
{
		
	std::string tmp = {""};
	int tmpT = {};

	int tmpX = {};
	int tmpY = {};
	animData >> data.name >> data.numFrames >> tmpX >> tmpY;
	data.frameSize = { (int)(tmpX), (int)(tmpY) };
	
	tmp = { "" };
	animData >> tmp;
	data.textureSheetType = Cfg::textureLookupTable[tmp];
	
	
	tmpX = {}; tmpY = {};
	animData >> tmpX >> tmpY;
	data.texSheetStartFramePos = {int(tmpX),int(tmpY)};
	
	
	tmpX = {}; tmpY = {};
	animData >> tmpX >> tmpY;
	data.texSheetEndFramePos = { int(tmpX),int(tmpY) };
	
	
	tmpT = {};
	animData >> data.firstRowInnerOffset >> data.texSheetPitch >> data.animPitch >> tmpT;
	data.firstFrameIsOffset = (tmpT == 1) ? true : false;
	
	
	tmp = {""};
	animData >> tmp;
	if (tmp == "block")
		data.layoutType = AnimLayoutType::Block;
	else if (tmp == "horizontal")
		data.layoutType = AnimLayoutType::Horizontal;
	else if (tmp == "vertical")
		data.layoutType = AnimLayoutType::Vertical;
	
	
	tmpT = {};
	animData >> tmpT;
	data.frameDelay = {(float)(tmpT / 1000.f)};
	
	
	tmpT = {};
	animData >> tmpT;
	data.animStartDelay = { (float)(tmpT / 1000.f) };
	
	
	tmpT = {};
	animData >> tmpT;
	data.animEndDelay = { (float)(tmpT / 1000.f) };
	
	
	tmpT = {};
	animData >> tmpT;
	data.startDelayIsAlways = (tmpT == 1) ? true : false;
	
	
	tmpT = {};
	animData >> tmpT;
	data.endDelayIsAlways = (tmpT == 1) ? true : false;
	animData >> data.numRepeats;
	
	
	tmpT = {};
	animData >> tmpT;
	data.looping = (tmpT == 1) ? true : false;

	data.repeats = (data.numRepeats > 0 ? true : false);
	float numRowsReal = ((float)data.numFrames + data.firstRowInnerOffset) / (float)data.animPitch;
	int numRows = (int)numRowsReal;
	data.colsInFirstRow = data.animPitch - data.firstRowInnerOffset;
	data.colsInLastRow = data.numFrames + data.firstRowInnerOffset % data.animPitch;
	data.hasMultipleCols = (data.numFrames > 1) ? true : false;
	data.hasMultipleRows = (numRowsReal > 1.0f) ? true : false;
	data.playing = {true};
	data.stopped = {false};
	data.paused = {false};
	data.frameIdx = {0U};
	animRects.clear();

	int startX = data.texSheetStartFramePos.x * data.frameSize.x;
	int startY = data.texSheetStartFramePos.y * data.frameSize.y;
	for (int y = data.texSheetStartFramePos.y; y < data.texSheetStartFramePos.y + numRows + 1; y++)
	{
		for (int x = ((y == data.texSheetStartFramePos.y) ? data.texSheetStartFramePos.x : 0); x < (int)data.animPitch; x++)
		{
			if ((y - data.texSheetStartFramePos.y )* data.animPitch + (x - data.texSheetStartFramePos.x) >= data.numFrames)
			{
				break;
			}
			animRects.push_back({ {x * data.frameSize.x,y* data.frameSize.y},{data.frameSize.x, data.frameSize.y} });
		}
	}
}


unsigned int Animation::getCurrentFrame()
{
	return data.frameIdx;
}

sf::IntRect Animation::getCurrentRect()
{
	int i = getCurrentFrame();
	return animRects[i];
}

std::variant<PlayerState> Animation::getName()
{
	return Cfg::animStateLookup[std::pair(data.animType, data.name)];
}

Cfg::Textures Animation::getTexType()
{
	return data.textureSheetType;
}

void Animation::play()
{
	data.playing = true;
}

void Animation::stop()
{
	data.playing = false;
	data.frameIdx = 0U;

}

void Animation::pause()
{
	data.playing = false;
}
