#pragma once
#ifdef DRAWDEBUGMENU

#include <string>

class Chunk;
class SFMLWindow;

class Debug {
public:
	static Chunk* getSubcircuitChunk(Chunk* c, int i);
	static std::string getSubcircuitName(Chunk* c, int i);
	static void drawUpdateOverlay(SFMLWindow& w, Chunk* c, int uo);
};

#endif