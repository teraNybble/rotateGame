#ifndef FREE_NEHE_H
#define FREE_NEHE_H

#include <vector>
#include "glew.h"
#include <iostream>
// FreeType Headers
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>


#ifdef _WIN32
#include <Windows.h>
#endif // WIN32

// OpenGL Headers
/*
#include <windows.h>                                      // (The GL Headers Need It)
#include <GL/gl.h>
#include <GL/glu.h>
*/


// Using The STL Exception Library Increases The
// Chances That Someone Else Using Our Code Will Correctly
// Catch Any Exceptions That We Throw.
#include <stdexcept>

// MSVC Will Spit Out All Sorts Of Useless Warnings If
// You Create Vectors Of Strings, This Pragma Gets Rid Of Them.
#pragma warning(disable : 4786)
#pragma warning(disable : 4996) // i couldn't give a shit if that functuon is unsafe

#ifndef GAME2D_FONT_PATHS
#define GAME2D_FONT_PATHS


#ifdef _WIN32 //Windows
//#include <Windows.h>
constexpr const char* _SysFont = "C:/Windows/Fonts/arial.ttf";
#endif
#ifdef  __unix__ //Linux
constexpr const char* _SysFont = "/usr/share/fonts/noto/NotoSans-Medium.ttf";
#endif

#endif // !GAME2D_FONT_PATHS

// Wrap Everything In A Namespace, That Way We Can Use A Common
// Function Name Like "print" Without Worrying About
// Overlapping With Anyone Else's Code.
namespace freetype {

	// Inside Of This Namespace, Give Ourselves The Ability
	// To Write Just "vector" Instead Of "std::vector"
	using std::vector;

	// Ditto For String.
	using std::string;

	// This Holds All Of The Information Related To Any
	// FreeType Font That We Want To Create. 
	struct font_data {
		float h;                                        // Holds The Height Of The Font.
		GLuint * textures;                                  // Holds The Texture Id's
		GLuint list_base;                                   // Holds The First Display List Id

															// The Init Function Will Create A Font With
															// The Height h From The File fname.
		void init(const char * fname, unsigned int h);

		// Free All The Resources Associated With The Font.
		void clean();
	};

	// The Flagship Function Of The Library - This Thing Will Print
	// Out Text At Window Coordinates X, Y, Using The Font ft_font.
	// The Current Modelview Matrix Will Also Be Applied To The Text.
	float print(const font_data &ft_font, float x, float y, const char *fmt, ...);

	float getLength(const font_data& ft_font, const char* fmt, ...);
	inline float getHeight(const font_data& ft_font) 
	{ 
		float h = ft_font.h / .63f;
		float projectionMatMine[4][4];
		glGetFloatv(GL_PROJECTION_MATRIX, &projectionMatMine[0][0]);

		//pushScreenCoordinateMatrix();
		glPushAttrib(GL_TRANSFORM_BIT);
		GLint	viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		//gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
		glOrtho(viewport[0], viewport[2], viewport[1], viewport[3], 0, 100);
		//gluOrtho2D(left, right, bottom, top);
		glPopAttrib();
		//!

		float projectionMatScreen[4][4];
		glGetFloatv(GL_PROJECTION_MATRIX, &projectionMatScreen[0][0]);

		glPushAttrib(GL_TRANSFORM_BIT);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();

		h = h * projectionMatScreen[1][1];
		h = (h - projectionMatMine[3][1]) / projectionMatMine[1][1];

		//std::cout << "Matrix things\t";
		//std::cout << projectionMatScreen[1][1] << "\t";
		//std::cout << projectionMatMine[3][1] << "\t" << projectionMatMine[1][1] << "\n";

		return h;
	}

}                                               // Close The Namespace

#endif