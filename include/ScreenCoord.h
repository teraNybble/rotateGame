#ifndef SCREENCOORD_H
#define SCREENCOORD_H

#include "glew.h"
#include <iostream>
namespace Game2D
{
	class ScreenCoord
	{
	private:
		static int screenWidth;
		static int screenHeight;
	public:
		inline static void init(int screenWidth, int screenHeight) {
			ScreenCoord::screenWidth = screenWidth;
			ScreenCoord::screenHeight = screenHeight;
			//std::cout << screenWidth << " x " << screenHeight << "\n";
		}

		inline static float getAspectRatio() {
			return (float)screenWidth / (float)screenHeight;
		}

		inline static void alignRight() {


			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			//glOrtho(-100, 0, -50, 50, 0, 100);
			glOrtho(((-100.0f * (screenWidth / (float)screenHeight))), 0, -50, 50, 0, 100);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
		inline static void alignCentre() {

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			//std::cout << screenWidth << " " << screenHeight << "\n";

			//float left = ((-50.0f * (screenWidth / (float)screenHeight)));
			//float right = ((50.0f * (screenWidth / (float)screenHeight)));

			//std::cout << left << ":" << right << "\n";

			//glOrtho(-50, 50, -50, 50, 0, 100);
			glOrtho(((-50.0f * (screenWidth / (float)screenHeight))), ((50.0f * (screenWidth / (float)screenHeight))), -50, 50, 0, 100);


			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
		inline static void alignLeft() {

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			//std::cout << screenWidth << " x " << screenHeight << "\n";
			//glOrtho(0, 100, -50, 50, 0, 100);
			glOrtho(0, ((100.0f * (screenWidth / (float)screenHeight))), -50, 50, 0, 100);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
	};
}

#endif // !SCREENCOORD_H