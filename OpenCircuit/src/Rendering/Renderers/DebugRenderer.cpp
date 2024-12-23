#include "DebugRenderer.h"
#include "ChunkRenderer.h"
#include "../Window/SFMLWindow.h"
#include "../../Simulation/Subcircuit.h"

bool Debug::drawDebugChunks = false;
bool Debug::drawStates = false;

void Debug::drawUpdateOverlay(sf::RenderTarget& w, Chunk* c, vec4<int> clipData, int uo) {
	if(drawDebugChunks){
		auto jobs = c->jobQueue;

		sf::VertexArray updates(sf::Quads, jobs.size() * 4);
		sf::VertexArray directions(sf::Triangles, jobs.size() * 3);


		const auto JOBC = sf::Color(255, 255, 255, 100);
		const auto DIRC = sf::Color(25, 100, 200, 150);

		int sx = clipData.x;
		int sy = clipData.y;
		int ex = clipData.z;
		int ey = clipData.w;

		int i = 0;
		while (!jobs.empty() && i < uo) {
			Job& j = jobs.front();

			const int translatedX = j.x - sx;
			const int translatedY = j.y - sy;

			updates[i * 4].position = sf::Vector2f(translatedX * VERTDIST, translatedY * VERTDIST);
			updates[i * 4 + 1].position = sf::Vector2f((translatedX + 1) * VERTDIST, translatedY * VERTDIST);
			updates[i * 4 + 2].position = sf::Vector2f((translatedX + 1) * VERTDIST, (translatedY + 1) * VERTDIST);
			updates[i * 4 + 3].position = sf::Vector2f(translatedX * VERTDIST, (translatedY + 1) * VERTDIST);

			updates[i * 4].color = JOBC;
			updates[i * 4 + 1].color = JOBC;
			updates[i * 4 + 2].color = JOBC;
			updates[i * 4 + 3].color = JOBC;

			switch (j.d) {
			case UP:
				directions[i * 3].position = sf::Vector2f(translatedX * VERTDIST + VERTDIST / 3, translatedY * VERTDIST - 1 * VERTDIST / 3);
				directions[i * 3 + 1].position = sf::Vector2f(translatedX * VERTDIST + 2 * VERTDIST / 3, translatedY * VERTDIST - 1 * VERTDIST / 3);
				directions[i * 3 + 2].position = sf::Vector2f(translatedX * VERTDIST + VERTDIST / 2, translatedY * VERTDIST + VERTDIST / 3);
				break;
			case RIGHT:
				directions[i * 3].position = sf::Vector2f(translatedX * VERTDIST + 4 * VERTDIST / 3, translatedY * VERTDIST + VERTDIST / 3);
				directions[i * 3 + 1].position = sf::Vector2f(translatedX * VERTDIST + 4 * VERTDIST / 3, translatedY * VERTDIST + 2 * VERTDIST / 3);
				directions[i * 3 + 2].position = sf::Vector2f(translatedX * VERTDIST + 2 * VERTDIST / 3, translatedY * VERTDIST + VERTDIST / 2);

				break;
			case DOWN:
				directions[i * 3].position = sf::Vector2f(translatedX * VERTDIST + VERTDIST / 3, translatedY * VERTDIST + 4 * VERTDIST / 3);
				directions[i * 3 + 1].position = sf::Vector2f(translatedX * VERTDIST + 2 * VERTDIST / 3, translatedY * VERTDIST + 4 * VERTDIST / 3);
				directions[i * 3 + 2].position = sf::Vector2f(translatedX * VERTDIST + VERTDIST / 2, translatedY * VERTDIST + 2 * VERTDIST / 3);
				break;
			case LEFT:
				directions[i * 3].position = sf::Vector2f(translatedX * VERTDIST - VERTDIST / 3, translatedY * VERTDIST + VERTDIST / 3);
				directions[i * 3 + 1].position = sf::Vector2f(translatedX * VERTDIST - VERTDIST / 3, translatedY * VERTDIST + 2 * VERTDIST / 3);
				directions[i * 3 + 2].position = sf::Vector2f(translatedX * VERTDIST + VERTDIST / 3, translatedY * VERTDIST + VERTDIST / 2);

				break;
			default:
				directions[i * 3].position = sf::Vector2f(translatedX * VERTDIST + VERTDIST / 2, translatedY * VERTDIST + VERTDIST / 3);
				directions[i * 3 + 1].position = sf::Vector2f(translatedX * VERTDIST + VERTDIST / 3, translatedY * VERTDIST + 2 * VERTDIST / 3);
				directions[i * 3 + 2].position = sf::Vector2f(translatedX * VERTDIST + 2 * VERTDIST / 3, translatedY * VERTDIST + 2 * VERTDIST / 3);

			}

			directions[i * 3].color = DIRC;
			directions[i * 3 + 1].color = DIRC;
			directions[i * 3 + 2].color = DIRC;

			i++;

			jobs.pop();
		}
		w.draw(updates);
		w.draw(directions);
	}

	if(drawStates) {
		static sf::Font debugFont;
		debugFont.loadFromFile("Vollkorn-Italic.ttf");

		for(int y = 0; y < CHUNK_Y; y++) {
			for(int x = 0; x < CHUNK_X; x++) {
				char chunkState = c->states[x][y];
				sf::Text stateText(std::to_string(chunkState), debugFont);
				stateText.setCharacterSize(15);
				stateText.setPosition(x * VERTDIST+3, y * VERTDIST);

				sf::RenderStates states;
				states.blendMode = sf::BlendMode(sf::BlendMode::SrcAlpha, sf::BlendMode::OneMinusSrcAlpha, sf::BlendMode::ReverseSubtract, 
				sf::BlendMode::One, sf::BlendMode::OneMinusSrcAlpha, sf::BlendMode::Add);
				if(chunkState) w.draw(stateText, states);
			}
		}
	}
}