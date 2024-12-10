#include "../Window/SFMLWindow.h"
#include "../../Utility/vec4.h"
#include "../../Simulation/Job.h"

#include <queue>

class Chunk;
class Debug {
public:
	static bool drawDebugChunks;

	static void drawUpdateOverlay(sf::RenderTarget& w, Chunk* c, vec4<int> clipData, int uo);
};