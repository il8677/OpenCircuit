
class PalettePanel {
public:
    void render();

    int getRightBrush() const { return m_rightBrush; }
    int getLeftBrush() const { return m_leftBrush; }

    void setLeftBrush(int b) { m_leftBrush = b; }
private:
	int m_rightBrush = 0, m_leftBrush = 1;
};