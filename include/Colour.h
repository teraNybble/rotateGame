#ifndef COLOUR_H
#define COLOUR_H

#include <ostream>
#include "glew.h"

#ifdef _DEV
#include "Debug.h"
#endif

//probs want to change into a switch statement so I can switch during gameplay
//#define CBF_PROTANOPIA 1
//#define CBF_PROTANOMALY 1
//#define CBF_DEUTERANOPIA 1
//#define CBF_DEUTERANOMALY 1
//#define CBF_TRITANOPIA 1
//#define CBF_TRIANOMALY 1
//#define CBF_ACHROMATOPSIA 1
//#define CBF_ACHROMATOMALY 1

namespace Game2D
{
	class Colour
	{
	private:
		float r, g, b, a;
	public:
		Colour();
		Colour(float r, float g, float b, float a = 1);

		static const Colour Black;
		static const Colour White;
		static const Colour Transparent;
		static const Colour Red;
		static const Colour Yellow;
		static const Colour Green;
		static const Colour Cyan;
		static const Colour Blue;
		static const Colour Magenta;

		/*
		{Normal:{ R:[100, 0, 0], G:[0, 100, 0], B:[0, 100, 0]},
 Protanopia:{ R:[56.667, 43.333, 0], G:[55.833, 44.167, 0], B:[0, 24.167, 75.833]},
 Protanomaly:{ R:[81.667, 18.333, 0], G:[33.333, 66.667, 0], B:[0, 12.5, 87.5]},
 Deuteranopia:{ R:[62.5, 37.5, 0], G:[70, 30, 0], B:[0, 30, 70]},
 Deuteranomaly:{ R:[80, 20, 0], G:[25.833, 74.167, 0], B:[0, 14.167, 85.833]},
 Tritanopia:{ R:[95, 5, 0], G:[0, 43.333, 56.667], B:[0, 47.5, 52.5]},
 Tritanomaly:{ R:[96.667, 3.333, 0], G:[0, 73.333, 26.667], B:[0, 18.333, 81.667]},
 Achromatopsia:{ R:[29.9, 58.7, 11.4], G:[29.9, 58.7, 11.4], B:[29.9, 58.7, 11.4]},
 Achromatomaly:{ R:[61.8, 32, 6.2], G:[16.3, 77.5, 6.2], B:[16.3, 32.0, 51.6]}
		*/

		
#ifdef _DEV
		inline void draw() const {

			switch (Debug::getColourBlindFilter())
			{
			case Debug::PROTANOPIA:
				glColor4f(
					((r * 0.56667) + (g * 0.43333) + (b * 0.00000)),//r
					((r * 0.55833) + (g * 0.44167) + (b * 0.00000)),//g
					((r * 0.00000) + (g * 0.24167) + (b * 0.75833)),//b
					a);
				break;
			case Debug::PROTANOMALY:
				glColor4f(
					((r * 0.81667) + (g * 0.18333) + (b * 0.00000)),//r
					((r * 0.33333) + (g * 0.66667) + (b * 0.00000)),//g
					((r * 0.00000) + (g * 0.12500) + (b * 0.87500)),//b
					a);
				break;
			case Debug::DEUTERANOPIA:
				glColor4f(
					((r * 0.62500) + (g * 0.37500) + (b * 0.00000)),//r
					((r * 0.70000) + (g * 0.30000) + (b * 0.00000)),//g
					((r * 0.00000) + (g * 0.30000) + (b * 0.70000)),//b
					a);
				break;
			case Debug::DEUTERANOMALY:
				glColor4f(
					((r * 0.80000) + (g * 0.20000) + (b * 0.00000)),//r
					((r * 0.25833) + (g * 0.74167) + (b * 0.00000)),//g
					((r * 0.00000) + (g * 0.14167) + (b * 0.85833)),//b
					a);
				break;
			case Debug::TRITANOPIA:
				glColor4f(
					((r * 0.95000) + (g * 0.05000) + (b * 0.00000)),//r
					((r * 0.43333) + (g * 0.56667) + (b * 0.00000)),//g
					((r * 0.00000) + (g * 0.47500) + (b * 0.52500)),//b
					a);
				break;
			case Debug::TRITANOMALY:
				glColor4f(
					((r * 0.96667) + (g * 0.03333) + (b * 0.00000)),//r
					((r * 0.73333) + (g * 0.26667) + (b * 0.00000)),//g
					((r * 0.00000) + (g * 0.18333) + (b * 0.81667)),//b
					a);
				break;
			case Debug::ACHROMATOPSIA:
				glColor4f(
					((r * 0.29900) + (g * 0.58700) + (b * 0.11400)),//r
					((r * 0.29900) + (g * 0.58700) + (b * 0.11400)),//g
					((r * 0.29900) + (g * 0.58700) + (b * 0.11400)),//b
					a);
				break;
			case Debug::ACHROMATOMALY:
				glColor4f(
					((r * 0.61800) + (g * 0.32000) + (b * 0.06200)),//r
					((r * 0.16300) + (g * 0.77500) + (b * 0.06200)),//g
					((r * 0.16300) + (g * 0.32000) + (b * 0.51600)),//b
					a);
				break;
			default:
				std::cout << "Filter not found\n";
			case Debug::NORMAL:
				glColor4f(r, g, b, a);
				break;
			}			
		}
#else
		inline void draw() const { glColor4f(r, g, b, a); }
#endif


		inline friend std::ostream& operator<<(std::ostream& os, const Colour& c)
		{
			return os << c.r << ", " << c.g << ", " << c.b << ", " << c.a;
		}
	};
}

#endif //COLOUR_H