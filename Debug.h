#ifndef DEBUG_H
#define DEBUG_H


class Debug
{
public:
	enum CBF { NORMAL, PROTANOPIA, PROTANOMALY, DEUTERANOPIA, DEUTERANOMALY, TRITANOPIA, TRITANOMALY, ACHROMATOPSIA, ACHROMATOMALY };
private:
	static CBF colourBlindFilter;
public:
	static inline void setColourBlindFilter(CBF f) { colourBlindFilter = f;	}

	static inline CBF getColourBlindFilter() { return colourBlindFilter; }
};


#endif // !DEBUG_H