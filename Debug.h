#ifndef DEBUG_H
#define DEBUG_H


class Debug
{
public:
	enum CBF { NORMAL, PROTANOPIA, PROTANOMALY, DEUTERANOPIA, DEUTERANOMALY, TRITANOPIA, TRITANOMALY, ACHROMATOPSIA, ACHROMATOMALY };
private:
	static CBF colourBlindFilter;
	static bool drawHitBoxes;
public:
	static inline void setColourBlindFilter(CBF f) { colourBlindFilter = f;	}
	static inline void setDrawHitBoxes(bool b) { drawHitBoxes = b; }

	static inline CBF getColourBlindFilter() { return colourBlindFilter; }
	static inline bool getDrawHitboxes() { return drawHitBoxes; }
};


#endif // !DEBUG_H