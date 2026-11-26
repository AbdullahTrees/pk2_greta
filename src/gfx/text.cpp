//#########################
//Pekka Kana 2
//Copyright (c) 2003 Janne Kivilahti
//#########################
#include "gfx/text.hpp"
#include "utils/ui/text_styles.hpp"

#include "system.hpp"
#include "game/game.hpp"
#include "settings/settings.hpp"

#include "engine/PLog.hpp"
#include "engine/PDraw.hpp"
#include "engine/PFilesystem.hpp"

#include <cstring>
#include <list>
#include <stdexcept>

struct PK2FADETEXT {
	char teksti[20];
	int fontti;
	int x,y,timer;
};

std::list<PK2FADETEXT> fadetekstit;

//Fonts
int fontti1 = -1;
int fontti2 = -1;
int fontti3 = -1;
int fontti4 = -1;
int fontti5 = -1;


static void mLoadFont(PLang*lang, int& font, const std::string& langID, const std::string& fallbackName){
	int ind_font = lang->Search_Id(langID.c_str());

	const std::string& fontName = ind_font==-1 ? fallbackName: lang->Get_Text(ind_font);

	std::optional<PFile::File> path = PFilesystem::FindVanillaAsset(fontName, PFilesystem::FONTS_DIR);
	if(!path.has_value()){
		throw std::runtime_error("Font picture: \""+fontName+"\" not found!");
	}

	font = PDraw::font_create(*path);
	if(font == -1){
		throw std::runtime_error("Can't create font from \""+fontName+"\"!");
	}
}



void Load_Fonts(PLang* lang) {
	PDraw::clear_fonts();

	mLoadFont(lang, fontti1, "font small font", "ScandicSmall.txt");
	mLoadFont(lang, fontti2, "font big font normal", "ScandicBig1.txt");
	mLoadFont(lang, fontti3, "font big font hilite", "ScandicBig2.txt");
	mLoadFont(lang, fontti4, "font big font shadow", "ScandicBig3.txt");
}

int WavetextLap_Draw(const char *text, int fontti, int x, int y, float lap) {
	return PK2gui::drawWaveTextLap(text, {fontti, fontti4}, x, y, degree, lap);
}

int Wavetext_Draw(const char *text, int fontti, int x, int y) {
	return PK2gui::drawWaveText(text, {fontti, fontti4}, x, y, degree);
}

int WavetextSlow_Draw(const char *text, int fontti, int x, int y) {
	return PK2gui::drawWaveTextSlow(text, {fontti, fontti4}, x, y, degree, Settings.transparent_text);
}

int ShadowedText_Draw(const std::string& text, int x, int y) {
	return PK2gui::drawShadowedText(text, {fontti2, fontti4}, x, y);
}

void Fadetext_Init(){

	fadetekstit.clear();

}

void Fadetext_New(int font, const std::string&text , u32 x, u32 y, u32 timer) {

	PK2FADETEXT tt;
	
	tt.fontti = font;
	strncpy(tt.teksti, text.c_str(), 19);
	tt.x = x;
	tt.y = y;
	tt.timer = timer;
	
	fadetekstit.push_back(tt);

}

int Fadetext_Draw(){
	int pros;

	for (PK2FADETEXT& text : fadetekstit) {
		if (text.timer > 0) {
			if (text.timer > 50)
				pros = 100;
			else
				pros = text.timer * 2;

			int x = text.x - Game->camera_x;
			int y = text.y - Game->camera_y;

			if (pros < 100)
				PDraw::font_writealpha_s(text.fontti, text.teksti, x, y, pros);
			else
				PDraw::font_write(text.fontti, text.teksti, x, y);

		}
	}
	
	return 0;
}

static bool update_done (PK2FADETEXT& t) { 

	if (t.timer > 0){
		t.timer--;

		if (t.timer%2 == 0)
			t.y--;
	}
	return t.timer == 0; 

}

void Fadetext_Update() {

	fadetekstit.remove_if(update_done);

}