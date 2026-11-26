//#########################
//Pekka Kana 2
//Copyright (c) 2003 Janne Kivilahti
//#########################
#pragma once

#include "engine/types.hpp"
#include <string>

namespace PK2gui {

/**
 * The fonts a text style draws with. The program owns its fonts and passes them in,
 * so these styles work with any font set, not only the game's.
 */
struct TextFonts {
	int text = -1;
	int shadow = -1;
};

/*
 * Each letter bobs on its own wave; phase moves the waves along (the game passes degree).
 * The wave functions return the width drawn.
 */
int drawWaveText(const char* text, const TextFonts& fonts, int x, int y, int phase);

// As drawWaveText, with the waves scaled by lap.
int drawWaveTextLap(const char* text, const TextFonts& fonts, int x, int y, int phase, float lap);

// A slower, smaller wave. Transparent text is drawn at 75% alpha with no shadow.
int drawWaveTextSlow(const char* text, const TextFonts& fonts, int x, int y, int phase, bool transparent);

// Returns the width drawn.
int drawShadowedText(const std::string& text, const TextFonts& fonts, int x, int y);

// Shown between start and end, fading out over its last 100 ticks.
void drawFadingText(const std::string& text, int font, int x, int y, u32 start, u32 end, u32 time);

void drawFadingTextCentered(const std::string& text, int font, int centerX, int y, u32 start, u32 end, u32 time);

}
