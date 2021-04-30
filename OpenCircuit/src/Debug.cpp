#ifdef DRAWDEBUGMENU

#include <SFML/Window.hpp>
#include <Queue>

#include "Rendering/Renderers/ChunkRenderer.h"
#include "Rendering/Window/SFMLWindow.h"
#include "Simulation/Chunk.h"

class Debug {
public:
	static void drawUpdateOverlay(SFMLWindow& w, Chunk* c, int uo) {
		auto jobs = c->getJobQueue();

		sf::VertexArray updates(sf::Quads, jobs.size() * 4);
		sf::VertexArray directions(sf::Triangles, jobs.size() * 3);

		int i = 0;

#define JOBC sf::Color(255, 255, 255, 100)
#define DIRC sf::Color(25, 100, 200, 100)

		while (!jobs.empty() && i <  uo) {
			Job& j = jobs.front();

			updates[i*4].position = sf::Vector2f(j.x * VERTDIST, j.y * VERTDIST);
			updates[i*4 + 1].position = sf::Vector2f((j.x + 1) * VERTDIST, j.y * VERTDIST);
			updates[i*4 + 2].position = sf::Vector2f((j.x + 1) * VERTDIST, (j.y + 1) * VERTDIST);
			updates[i*4 + 3].position = sf::Vector2f(j.x * VERTDIST, (j.y + 1) * VERTDIST);

			updates[i*4].color = JOBC;
			updates[i*4 + 1].color = JOBC;
			updates[i*4 + 2].color = JOBC;
			updates[i*4 + 3].color = JOBC;

			switch (j.d) {
			case UP:
				directions[i * 3].position = sf::Vector2f(j.x * VERTDIST + VERTDIST / 3, j.y * VERTDIST + 1 * VERTDIST / 3);
				directions[i * 3 + 1].position = sf::Vector2f(j.x * VERTDIST + 2 * VERTDIST / 3, j.y * VERTDIST + VERTDIST / 3);
				directions[i * 3 + 2].position = sf::Vector2f(j.x * VERTDIST + VERTDIST / 2, j.y * VERTDIST - 1 * VERTDIST / 3);
				break;
			case RIGHT:
				directions[i * 3].position = sf::Vector2f(j.x * VERTDIST + 2 * VERTDIST / 3, j.y * VERTDIST + VERTDIST / 3);
				directions[i * 3 + 1].position = sf::Vector2f(j.x * VERTDIST + 2 * VERTDIST / 3, j.y * VERTDIST + 2 * VERTDIST / 3);
				directions[i * 3 + 2].position = sf::Vector2f(j.x * VERTDIST + 4 * VERTDIST / 3, j.y * VERTDIST + VERTDIST / 2);

				break;
			case DOWN:
				directions[i * 3].position = sf::Vector2f(j.x * VERTDIST + VERTDIST / 3, j.y * VERTDIST + 2 * VERTDIST / 3);
				directions[i * 3 + 1].position = sf::Vector2f(j.x * VERTDIST + 2 * VERTDIST / 3, j.y * VERTDIST + 2 * VERTDIST / 3);
				directions[i * 3 + 2].position = sf::Vector2f(j.x * VERTDIST + VERTDIST / 2, j.y * VERTDIST + 4 * VERTDIST / 3);
				break;
			case LEFT:
				directions[i * 3].position = sf::Vector2f(j.x * VERTDIST + VERTDIST / 3, j.y * VERTDIST + VERTDIST / 3);
				directions[i * 3 + 1].position = sf::Vector2f(j.x * VERTDIST + VERTDIST / 3, j.y * VERTDIST + 2 * VERTDIST / 3);
				directions[i * 3 + 2].position = sf::Vector2f(j.x * VERTDIST - VERTDIST / 3, j.y * VERTDIST + VERTDIST / 2);

				break;
			default:
				directions[i * 3].position = sf::Vector2f(j.x * VERTDIST + VERTDIST / 2, j.y * VERTDIST + VERTDIST / 3);
				directions[i * 3 + 1].position = sf::Vector2f(j.x * VERTDIST + VERTDIST / 3, j.y * VERTDIST + 2 * VERTDIST / 3);
				directions[i * 3 + 2].position = sf::Vector2f(j.x * VERTDIST + 2 * VERTDIST / 3, j.y * VERTDIST + 2 * VERTDIST / 3);

			}
			
			directions[i * 3].color = DIRC;
			directions[i * 3 + 1].color = DIRC;
			directions[i * 3 + 2].color = DIRC;
			
			i++;

			jobs.pop();
		}

		w.renderVerts(updates);
		w.renderVerts(directions);
	}
};

#endif