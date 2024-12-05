#include "ChunkRenderer.h"
#include "../../Simulation/Chunk.h"

#define VERTDIST 15

// TODO: Do something better than this
vec4<unsigned char> sfToVec4(sf::Color c) {
	return vec4<unsigned char>(c.r, c.g, c.b, c.a);
}

sf::Color vec4ToSf(vec4<unsigned char> c) {
	return sf::Color(c.r, c.g, c.b, c.a);
}

vec4<unsigned char> ChunkRenderer::getComponentColour(int componenetId)
{
	switch (componenetId)
	{
	case 1:
	case 8:
	case 7:
		return sfToVec4(sf::Color::Yellow);
		break;
	case 2:
		return sfToVec4(sf::Color::Green);
		break;
	case 3:
		return sfToVec4(sf::Color::Magenta);
		break;
	case 4:
		return sfToVec4(sf::Color::Blue);
		break;
	case 5:
		return sfToVec4(sf::Color::Cyan);
		break;
	case 6:
		return sfToVec4(sf::Color::Red);
		break;
	case 999:
		return sfToVec4(sf::Color(255, 255, 255, 255));
		break;
	default:
		return sfToVec4(sf::Color::Black);
		break;
	}
}

void ChunkRenderer::Render(sf::RenderTarget& renderTarget, Chunk* c) {
	static bool initialized = false;

	if (!initialized) {
		initialized = true;
		
		const sf::Color GRIDCOLOUR(255, 255, 255, 75);
		for (int x = 0; x < CHUNK_Y; x++) {
			int index = x * 2;
			grid[index].position = sf::Vector2f(x * VERTDIST, 0.0f);
			grid[index + 1].position = sf::Vector2f(x * VERTDIST, CHUNK_Y*VERTDIST);

			grid[index].color = GRIDCOLOUR;
			grid[index + 1].color = GRIDCOLOUR;
		}

		for (int y = 0; y < CHUNK_X; y++) {
			int index = (CHUNK_X*2) + y * 2;
			grid[index].position = sf::Vector2f(0.0f, y * VERTDIST);
			grid[index + 1].position = sf::Vector2f(CHUNK_X * VERTDIST, y * VERTDIST);

			grid[index].color = GRIDCOLOUR;
			grid[index + 1].color = GRIDCOLOUR;
		}

		for (int y = 0; y < CHUNK_Y; y++) {
			for (int x = 0; x < CHUNK_X; x++) {
				int index = (x * CHUNK_X + y) * 4;

				cells[index].position = sf::Vector2f(x * VERTDIST, y * VERTDIST);
				cells[index + 1].position = sf::Vector2f((x + 1) * VERTDIST, y * VERTDIST);
				cells[index + 2].position = sf::Vector2f((x + 1) * VERTDIST, (y + 1) * VERTDIST);
				cells[index + 3].position = sf::Vector2f(x * VERTDIST, (y + 1) * VERTDIST);
			}
		}
	}

	for (int y = 0; y < CHUNK_Y; y++) {
		for (int x = 0; x < CHUNK_X; x++) {
			int cellId = c->schematic->getCellId(x, y);
			int index = (x*CHUNK_X + y)*4;

			sf::Color vColour = vec4ToSf( getComponentColour(cellId) );
			
			if (!c->getOutput(x, y, NONE)) {
				vColour = vColour * sf::Color(100, 100, 100);;
			}

			cells[index].color = vColour;
			cells[index+1].color = vColour;
			cells[index+2].color = vColour;
			cells[index+3].color = vColour;
		}
	}

	renderTarget.draw(cells);
	renderTarget.draw(grid);
}

void ChunkRenderer::worldToGrid(int& x, int& y)
{
	x = x / VERTDIST;
	y = y / VERTDIST;
}

sf::VertexArray ChunkRenderer::cells(sf::Quads, (CHUNK_X)* (CHUNK_Y) * 4);
sf::VertexArray ChunkRenderer::grid(sf::Lines, 4 * CHUNK_X);
