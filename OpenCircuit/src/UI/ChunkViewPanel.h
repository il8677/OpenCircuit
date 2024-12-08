#include <SFML/Graphics.hpp>

#include "UIPanel.h"
#include <imgui.h>

class Chunk;

class ChunkViewPanel : public UIPanel {
public:
	ChunkViewPanel(Chunk& chunk);

	void setSchematic(Schematic* schematic);
	void setClipView(bool clipView) { m_clipView = clipView; }
protected:
	virtual void onImGuiDraw() override;

private:
	void drawPopup();
	void pinPopup();

	Chunk& m_chunk;

	Chunk* m_popupChunk=nullptr;

	// Rendering stuff
	ImVec2 m_viewportSize;
	sf::RenderTexture m_texture;
	sf::RenderTexture m_popupTexture;

	bool m_clipView = false;
};