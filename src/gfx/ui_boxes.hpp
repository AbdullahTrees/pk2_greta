//#########################
//Pekka Kana 2
//Copyright (c) 2003 Janne Kivilahti
//#########################
#pragma once

#include "engine/types.hpp"
#include <string>

namespace PK2gui {

/**
 * The edges of a box on the screen.
 */
class BoxRect {
public:
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;

	// Moves each edge one pixel towards target, so the box slides between sizes.
	void slideTowards(const BoxRect& target);
};

/**
 * The checkered box behind the game's menus, shaded upwards from colorBase. The menus use
 * 224, the last palette band, which each background image defines itself: menu.bmp makes
 * it blue. 67 is the dark red box of the load menu.
 */
void drawMenuBox(const BoxRect& box, u8 colorBase);

// As the menus draw it, with each edge wobbling by phase (the menus pass degree).
void drawMenuBoxWobbling(const BoxRect& box, u8 colorBase, int phase);

/**
 * The box behind info sign texts: a light purple border around a dark purple fill.
 */
void drawInfoBox(const BoxRect& box);

// A box sized to text with the text inside, its top left corner at x, y.
void drawInfoBoxText(int font, const std::string& text, int x, int y);

/**
 * An info sign as the game shows it: centred on centerX, it opens while timer counts down
 * from totalTime, shows the text fading in, then closes as timer reaches 0.
 */
void drawInfoSign(int font, const std::string& text, int centerX, int top, int timer, int totalTime);

}
