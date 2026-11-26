//#########################
//Pekka Kana 2
//Copyright (c) 2003 Janne Kivilahti
//#########################
#include "text_styles.hpp"

#include "engine/PDraw.hpp"
#include "engine/PString.hpp"
#include "system.hpp"

namespace PK2gui {

int drawWaveTextLap(const char* text, const TextFonts& fonts, int x, int y, int phase, float lap) {

	int pos = 0;
	int i = 0;
	PString::UTF8_Char u8c;

	while(*text!='\0'){
		text = u8c.read(text);
		int ys = (int)(sin_table((i+phase)*8))/(7.f/(lap*0.8));
		int xs = (int)(cos_table((i+phase)*8))/(9.f/(lap*2.5));

		PDraw::font_write(fonts.shadow, u8c.c_str(), x+pos-xs+3,y+ys+3);
		pos += PDraw::font_write_line(fonts.text, u8c.c_str(), x+pos-xs,y+ys);
		++i;
	}

	return pos;

}

int drawWaveText(const char* text, const TextFonts& fonts, int x, int y, int phase) {

	int pos = 0;
	int i = 0;
	PString::UTF8_Char u8c;

	while(*text!='\0'){
		text = u8c.read(text);

		int ys = (int)(sin_table((i+phase)*8))/7;
		int xs = (int)(cos_table((i+phase)*8))/9;

		PDraw::font_write(fonts.shadow,u8c.c_str(),x+pos-xs+3,y+ys+3);
		pos += PDraw::font_write_line(fonts.text,u8c.c_str(),x+pos-xs,y+ys);
		++i;
	}

	return pos;

}

int drawWaveTextSlow(const char* text, const TextFonts& fonts, int x, int y, int phase, bool transparent) {

	int pos = 0;
	int i = 0;
	PString::UTF8_Char u8c;

	while(*text!='\0'){
		text = u8c.read(text);

		int ys = (int)(sin_table((i+phase)*4))/9;
		int xs = (int)(cos_table((i+phase)*4))/11;

		if (transparent) {
			auto[width, _] = PDraw::font_writealpha_s(fonts.text,u8c.c_str(),x+pos-xs,y+ys,75, 1);
			pos += width;

		} else {

			PDraw::font_write(fonts.shadow,u8c.c_str(),x+pos-xs+1,y+ys+1);
			pos += PDraw::font_write_line(fonts.text,u8c.c_str(),x+pos-xs,y+ys);

		}
		++i;
	}

	return pos;

}

int drawShadowedText(const std::string& text, const TextFonts& fonts, int x, int y) {

	PDraw::font_write(fonts.shadow, text, x + 2, y + 2);
	return PDraw::font_write_line(fonts.text, text, x, y);

}

void drawFadingText(const std::string& text, int font, int x, int y, u32 start, u32 end, u32 time){
	int pros = 100;
	if (time > start && time < end) {

		if (time - start < 100)
			pros = time - end;

		if (end - time < 100)
			pros = end - time;

		if (pros > 0) {
			if (pros < 100)
				PDraw::font_writealpha_s(font,text,x,y,pros);
			else
				PDraw::font_write_line(font,text,x,y);
		}

	}
}

void drawFadingTextCentered(const std::string& text, int font, int centerX, int y, u32 start, u32 end, u32 time){
	std::pair<int, int> text_size = PDraw::font_get_text_size(font, text);
	int x = centerX - text_size.first/2;
	drawFadingText(text, font, x, y, start, end, time);
}

}
