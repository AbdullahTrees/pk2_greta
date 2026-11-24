//#########################
//Pekka Kana 2
//Copyright (c) 2003 Janne Kivilahti
//#########################
#include "ui_boxes.hpp"

#include "engine/PDraw.hpp"
#include "system.hpp"

static const int INFO_BOX_PADDING = 4;
static const u8 INFO_BOX_BORDER = 51;
static const u8 INFO_BOX_FILL = 38;

void MenuBox_Draw(int left, int top, int right, int bottom, u8 color_base){

	double mult_y = (bottom - top) / 19.0;
	double mult_x = (right - left) / 19.0;
	double dbl_y = top;
	double dbl_x = left;
	bool dark = true;
	int vari = 0;

	//Draw squares
	for (int y=0;y<19;y++) {
		dbl_x = left;

		for (int x=0;x<19;x++) {

			vari = (x / 4) + (y / 3);
			if (dark) vari /= 2;

			PDraw::screen_fill(int(dbl_x),int(dbl_y),int(dbl_x+mult_x),int(dbl_y+mult_y),color_base+vari);

			dbl_x += mult_x;
			dark = !dark;

		}

		dbl_y += mult_y;
	}

	//Draw borders
	PDraw::screen_fill(left-1,top-1,right+1,top+2,0);
	PDraw::screen_fill(left-1,top-1,left+2,bottom+1,0);
	PDraw::screen_fill(left-1,bottom-2,right+1,bottom+1,0);
	PDraw::screen_fill(right-2,top-1,right+1,bottom+1,0);

	PDraw::screen_fill(left-1+1,top-1+1,right+1+1,top+2+1,0);
	PDraw::screen_fill(left-1+1,top-1+1,left+2+1,bottom+1+1,0);
	PDraw::screen_fill(left-1+1,bottom-2+1,right+1+1,bottom+1+1,0);
	PDraw::screen_fill(right-2+1,top-1+1,right+1+1,bottom+1+1,0);

	PDraw::screen_fill(left,top,right,top+1,153);
	PDraw::screen_fill(left,top,left+1,bottom,144);
	PDraw::screen_fill(left,bottom-1,right,bottom,138);
	PDraw::screen_fill(right-1,top,right,bottom,138);
}

void MenuBox_DrawWobbling(int left, int top, int right, int bottom, u8 color_base, int phase){

	left   += (int)(sin_table( phase*2)     / 2.0);
	right  += (int)(cos_table( phase*2)     / 2.0);
	top    += (int)(sin_table((phase*2)+20) / 2.0);
	bottom += (int)(cos_table((phase*2)+40) / 2.0);

	MenuBox_Draw(left, top, right, bottom, color_base);
}

static void slide_edge(int& edge, int target){
	if (edge < target)
		edge++;

	if (edge > target)
		edge--;
}

void MenuBox_Slide(MenuBox& box, int left, int top, int right, int bottom){
	slide_edge(box.left, left);
	slide_edge(box.right, right);
	slide_edge(box.top, top);
	slide_edge(box.bottom, bottom);
}


void InfoBox_Draw(int left, int top, int right, int bottom){
	PDraw::screen_fill(left - 1, top - 1, right + 1, bottom + 1, INFO_BOX_BORDER);
	PDraw::screen_fill(left, top, right, bottom, INFO_BOX_FILL);
}

void InfoBox_DrawText(int font, const std::string& text, int x, int y){
	std::pair<int, int> size = PDraw::font_get_text_size(font, text);

	InfoBox_Draw(x, y, x + size.first + 2 * INFO_BOX_PADDING, y + size.second + 2 * INFO_BOX_PADDING);
	PDraw::font_write(font, text, x + INFO_BOX_PADDING, y + INFO_BOX_PADDING);
}

void InfoSign_Draw(int font, const std::string& text, int center_x, int top, int timer, int total_time){

	if (timer <= 0)
		return;

	std::pair<int, int> box_size = PDraw::font_get_text_size(font, text);

	box_size.first += 2 * INFO_BOX_PADDING;
	box_size.second += 2 * INFO_BOX_PADDING;

	int left = center_x - (box_size.first / 2);
	int right = center_x + (box_size.first / 2);
	int bottom = top + box_size.second;

	// The box opens from its middle at the start and closes into it at the end
	int tmp = (box_size.second - timer) / 2;

	if (tmp > 0)
	{
		top += tmp;
		bottom -= tmp;
	}
	else if (timer > total_time - box_size.second)
	{
		tmp = (box_size.second - total_time + timer) / 2;

		top += tmp;
		bottom -= tmp;
	}

	InfoBox_Draw(left, top, right, bottom);

	tmp = timer - 1 - box_size.second;

	if (tmp >= 100)
		PDraw::font_write(font, text, left + INFO_BOX_PADDING, top + INFO_BOX_PADDING);
	else if (tmp > 0)
		PDraw::font_writealpha_s(font, text, left + INFO_BOX_PADDING, top + INFO_BOX_PADDING, tmp);
}
