#include "ChunkRenderer.h"
#include "DebugRenderer.h"
#include "../../Simulation/Chunk.h"
#include <iostream>

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

void ChunkRenderer::Render(sf::RenderTarget& renderTarget, Chunk* c, bool doClip) {
	static bool initialized = false;

	if (!initialized) {
		initialized = true;
		
		const sf::Color GRIDCOLOUR(255, 255, 255, 75);
		for (int x = 0; x < CHUNK_Y+1; x++) {
			int index = x * 2;
			grid[index].position = sf::Vector2f(x * VERTDIST+1, 0.0f);
			grid[index + 1].position = sf::Vector2f(x * VERTDIST+1, CHUNK_Y*VERTDIST);

			grid[index].color = GRIDCOLOUR;
			grid[index + 1].color = GRIDCOLOUR;
		}

		for (int y = 0; y < CHUNK_X+1; y++) {
			int index = (CHUNK_Y*2+2) + y * 2;
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

    int startX = 0, startY = 0;
    int endX = CHUNK_X, endY = CHUNK_Y;

    if(doClip){
		std::tie(startX, startY, endX, endY) = getChunkBounds(*c);
	}

    for (int x = 0; x < CHUNK_X-startX; x++) {
        for (int y = 0; y < CHUNK_Y-startY; y++) {
			int cellId = c->schematic->getCellId(x+startX, y+startY);
			int index = ((x)*CHUNK_X + (y))*4;

			sf::Color vColour = vec4ToSf( getComponentColour(cellId) );
			
			if (!c->getOutput(x+startX, y+startY, NONE)) {
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

	if(Debug::drawDebugChunks){
		Debug::drawUpdateOverlay(renderTarget, c, vec4<int>(startX, startY, endX, endY), 10);
	}
}

std::tuple<int, int, int, int>  ChunkRenderer::getChunkBounds(Chunk& c) {
	int startX = CHUNK_X, startY = CHUNK_Y;
	int endX = 0, endY = 0;

	for(int y = 0; y < CHUNK_Y; y++){
		for(int x = 0; x < CHUNK_X; x++){
			if(c.schematic->getCellId(x, y)){
				startX = std::min(x, startX);
				startY = std::min(y, startY);
				endX = std::max(x, endX);
				endY = std::max(x, endY);
			}
		}
	}

	if(startX > endX){
		startX = 0;
		endX = CHUNK_X;
	}

	if(startY > endY){
		startY = 0;
		endY = CHUNK_Y;
	}

	return {startX, startY, endX, endY};
}

void ChunkRenderer::worldToGrid(int& x, int& y) {
	x = x / VERTDIST;
	y = y / VERTDIST;
}


void ChunkRenderer::worldToGridClip(int& x, int& y, Chunk& c) {
	auto [startX, startY, endX, endY] = getChunkBounds(c);

	worldToGrid(x, y);

	x += startX;
	y += startY;
}

sf::VertexArray ChunkRenderer::cells(sf::Quads, (CHUNK_X) * (CHUNK_Y) * 4);
sf::VertexArray ChunkRenderer::grid(sf::Lines, 2 * CHUNK_X + 2 * CHUNK_Y + 4);
