//#########################
//Pekka Kana 2
//Copyright (c) 2003 Janne Kivilahti
//#########################
#pragma once

#include "engine/types.hpp"
#include <string>

/**
 * The checkered box behind the game's menus. color_base is the first colour of a palette
 * band; the box shades within the band. 224 is the blue box most menus use, 67 the dark
 * red one of the load menu.
 */
struct MenuBox {
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;
};

void MenuBox_Draw(int left, int top, int right, int bottom, u8 color_base);

// As the menus draw it, with each edge wobbling by phase (the menus pass degree).
void MenuBox_DrawWobbling(int left, int top, int right, int bottom, u8 color_base, int phase);

// Moves each edge of box one pixel towards the target, so the box slides between sizes.
void MenuBox_Slide(MenuBox& box, int left, int top, int right, int bottom);


/**
 * The box behind info sign texts: a light purple border around a dark purple fill.
 */
void InfoBox_Draw(int left, int top, int right, int bottom);

// A box sized to text with the text inside, its top left corner at x, y.
void InfoBox_DrawText(int font, const std::string& text, int x, int y);

/**
 * An info sign as the game shows it: centred on center_x, it opens while timer counts down
 * from total_time, shows the text fading in, then closes as timer reaches 0.
 */
void InfoSign_Draw(int font, const std::string& text, int center_x, int top, int timer, int total_time);
