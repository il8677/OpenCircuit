#include "ChunkRenderer.h"
#include "../../Simulation/Chunk.h"

#define VERTDIST 30

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
	default:
		return sfToVec4(sf::Color::Black);
		break;
	}
}

void ChunkRenderer::Render(Window& w, Chunk* c) {
	sf::VertexArray cells(sf::Quads, (CHUNK_X) * (CHUNK_Y) * 4);
	sf::VertexArray grid(sf::Lines, 4 * CHUNK_X);

	const sf::Color GRIDCOLOUR(255, 255, 255, 75);

	//Theres probably a more efficient way of doing this all seperatley
	for (int x = 0; x < CHUNK_X; x++) {
		int index = x * 2;
		grid[index].position = sf::Vector2f(x * VERTDIST, 0.0f);
		grid[index + 1].position = sf::Vector2f(x * VERTDIST, CHUNK_Y*VERTDIST);

		grid[index].color = GRIDCOLOUR;
		grid[index + 1].color = GRIDCOLOUR;
	}

	for (int y = 0; y < CHUNK_Y; y++) {
		int index = (CHUNK_X*2) + y * 2;
		grid[index].position = sf::Vector2f(0.0f, y * VERTDIST);
		grid[index + 1].position = sf::Vector2f(CHUNK_X * VERTDIST, y * VERTDIST);

		grid[index].color = GRIDCOLOUR;
		grid[index + 1].color = GRIDCOLOUR;
	}

	for (int x = 0; x < CHUNK_X; x++) {
		for (int y = 0; y < CHUNK_Y; y++) {
			int cellId = c->getCellId(x, y);
			int index = (x*CHUNK_X + y)*4;

			sf::Color vColour = vec4ToSf( getComponentColour(cellId) );
			
			if (!c->getState(x, y, NONE)) {
				vColour = vColour * sf::Color(100, 100, 100);;
			}

			cells[index].color = vColour;
			cells[index+1].color = vColour;
			cells[index+2].color = vColour;
			cells[index+3].color = vColour;

			cells[index].position = sf::Vector2f(x * VERTDIST, y * VERTDIST);
			cells[index+1].position = sf::Vector2f((x+1) * VERTDIST, y * VERTDIST);
			cells[index+2].position = sf::Vector2f((x+1) * VERTDIST, (y+1) * VERTDIST);
			cells[index+3].position = sf::Vector2f(x * VERTDIST, (y+1) * VERTDIST);
		}
	}

	w.renderVerts(cells);
	w.renderVerts(grid);
}

void ChunkRenderer::worldToGrid(int& x, int& y)
{
	x = x / VERTDIST;
	y = y / VERTDIST;
}

