//#########################
//Pekka Kana 2
//Copyright (c) 2003 Janne Kivilahti
//#########################
#include "ui_boxes.hpp"

#include "engine/PDraw.hpp"
#include "system.hpp"

namespace PK2gui {

namespace {

constexpr int MENU_BOX_CELLS = 19;
constexpr u8 MENU_BOX_BORDER = 0;
constexpr u8 MENU_BOX_EDGE_TOP = 153;
constexpr u8 MENU_BOX_EDGE_LEFT = 144;
constexpr u8 MENU_BOX_EDGE_BOTTOM_RIGHT = 138;

constexpr int INFO_BOX_PADDING = 4;
constexpr u8 INFO_BOX_BORDER = 51;
constexpr u8 INFO_BOX_FILL = 38;

void slideEdge(int& edge, int target) {
	if (edge < target) {
		++edge;
	} else if (edge > target) {
		--edge;
	}
}

}

void BoxRect::slideTowards(const BoxRect& target) {
	slideEdge(this->left, target.left);
	slideEdge(this->right, target.right);
	slideEdge(this->top, target.top);
	slideEdge(this->bottom, target.bottom);
}

void drawMenuBox(const BoxRect& box, u8 colorBase) {
	const int left = box.left;
	const int top = box.top;
	const int right = box.right;
	const int bottom = box.bottom;

	const double cellWidth = (right - left) / static_cast<double>(MENU_BOX_CELLS);
	const double cellHeight = (bottom - top) / static_cast<double>(MENU_BOX_CELLS);

	// The squares darken every other cell; dark carries on from one row to the next
	bool dark = true;
	double cellY = top;

	for (int row = 0; row < MENU_BOX_CELLS; ++row) {
		double cellX = left;

		for (int column = 0; column < MENU_BOX_CELLS; ++column) {
			int shade = column / 4 + row / 3;
			if (dark) {
				shade /= 2;
			}

			PDraw::screen_fill(static_cast<int>(cellX), static_cast<int>(cellY),
				static_cast<int>(cellX + cellWidth), static_cast<int>(cellY + cellHeight),
				static_cast<u8>(colorBase + shade));

			cellX += cellWidth;
			dark = !dark;
		}

		cellY += cellHeight;
	}

	// A black border, then the same again one pixel down and right as its shadow
	for (int offset = 0; offset <= 1; ++offset) {
		PDraw::screen_fill(left - 1 + offset, top - 1 + offset, right + 1 + offset, top + 2 + offset, MENU_BOX_BORDER);
		PDraw::screen_fill(left - 1 + offset, top - 1 + offset, left + 2 + offset, bottom + 1 + offset, MENU_BOX_BORDER);
		PDraw::screen_fill(left - 1 + offset, bottom - 2 + offset, right + 1 + offset, bottom + 1 + offset, MENU_BOX_BORDER);
		PDraw::screen_fill(right - 2 + offset, top - 1 + offset, right + 1 + offset, bottom + 1 + offset, MENU_BOX_BORDER);
	}

	PDraw::screen_fill(left, top, right, top + 1, MENU_BOX_EDGE_TOP);
	PDraw::screen_fill(left, top, left + 1, bottom, MENU_BOX_EDGE_LEFT);
	PDraw::screen_fill(left, bottom - 1, right, bottom, MENU_BOX_EDGE_BOTTOM_RIGHT);
	PDraw::screen_fill(right - 1, top, right, bottom, MENU_BOX_EDGE_BOTTOM_RIGHT);
}

void drawMenuBoxWobbling(const BoxRect& box, u8 colorBase, int phase) {
	BoxRect wobbled = box;

	wobbled.left   += static_cast<int>(sin_table(phase * 2)        / 2.0);
	wobbled.right  += static_cast<int>(cos_table(phase * 2)        / 2.0);
	wobbled.top    += static_cast<int>(sin_table((phase * 2) + 20) / 2.0);
	wobbled.bottom += static_cast<int>(cos_table((phase * 2) + 40) / 2.0);

	drawMenuBox(wobbled, colorBase);
}

void drawInfoBox(const BoxRect& box) {
	PDraw::screen_fill(box.left - 1, box.top - 1, box.right + 1, box.bottom + 1, INFO_BOX_BORDER);
	PDraw::screen_fill(box.left, box.top, box.right, box.bottom, INFO_BOX_FILL);
}

void drawInfoBoxText(int font, const std::string& text, int x, int y) {
	const auto [textWidth, textHeight] = PDraw::font_get_text_size(font, text);

	drawInfoBox(BoxRect{x, y, x + textWidth + 2 * INFO_BOX_PADDING, y + textHeight + 2 * INFO_BOX_PADDING});
	PDraw::font_write(font, text, x + INFO_BOX_PADDING, y + INFO_BOX_PADDING);
}

void drawInfoSign(int font, const std::string& text, int centerX, int top, int timer, int totalTime) {
	if (timer <= 0) {
		return;
	}

	const auto [textWidth, textHeight] = PDraw::font_get_text_size(font, text);
	const int width = textWidth + 2 * INFO_BOX_PADDING;
	const int height = textHeight + 2 * INFO_BOX_PADDING;

	BoxRect box{centerX - width / 2, top, centerX + width / 2, top + height};

	// The box opens from its middle at the start and closes into it at the end
	const int closing = (height - timer) / 2;

	if (closing > 0) {
		box.top += closing;
		box.bottom -= closing;
	} else if (timer > totalTime - height) {
		const int opening = (height - totalTime + timer) / 2;
		box.top += opening;
		box.bottom -= opening;
	}

	drawInfoBox(box);

	const int textAlpha = timer - 1 - height;

	if (textAlpha >= 100) {
		PDraw::font_write(font, text, box.left + INFO_BOX_PADDING, box.top + INFO_BOX_PADDING);
	} else if (textAlpha > 0) {
		PDraw::font_writealpha_s(font, text, box.left + INFO_BOX_PADDING, box.top + INFO_BOX_PADDING, textAlpha);
	}
}

}
