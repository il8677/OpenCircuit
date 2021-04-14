#include "ChunkRenderer.h"
#include "../../Simulation/Chunk.h"

#define VERTDIST 30

ChunkRenderer::ChunkRenderer(Chunk& c) : c(c) {

}

void ChunkRenderer::Render(Window& w) {
	sf::VertexArray va(sf::Quads, (CHUNK_X) * (CHUNK_Y) * 4);

	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			int cellId = c.getCellId(x, y);
			int index = (x*CHUNK_X + y)*4;

			sf::Color vColour;
			switch (cellId)
			{
			case 1:
				vColour = sf::Color::Yellow;
				break;
			case 2:
				vColour = sf::Color::Green;
				break;
			case 3:
				vColour = sf::Color::Magenta;
				break;
			case 4:
				vColour = sf::Color::Blue;
				break;
			case 5:
				vColour = sf::Color::Cyan;
				break;
			default:
				vColour = sf::Color::Black;
				break;
			}

			va[index].color = vColour;
			va[index+1].color = vColour;
			va[index+2].color = vColour;
			va[index+3].color = vColour;

			va[index].position = sf::Vector2f(x * VERTDIST, y * VERTDIST);
			va[index+1].position = sf::Vector2f((x+1) * VERTDIST, y * VERTDIST);
			va[index+2].position = sf::Vector2f((x+1) * VERTDIST, (y+1) * VERTDIST);
			va[index+3].position = sf::Vector2f(x * VERTDIST, (y+1) * VERTDIST);
		}
	}

	w.renderVerts(va);
}