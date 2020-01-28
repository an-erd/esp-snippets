 OTA display update function
#define BAR_PAD		3
static void dispod_screen_ota_update_display(otaUpdate_t otaUpdate, bool clearScreen)
{
	int ypos;
	int x0 = 20, x1 = 300, y0 = 60, y1 = 100;	 gauge corner
	int mapx;

	 Preparation
    M5.Lcd.fillScreen(TFT_BLACK);
	TFT_resetclipwin();
    TFT_setFont(DEJAVU18_FONT, NULL);        DEJAVU18_FONT
    _fg = TFT_WHITE;
	_bg = TFT_BLACK;                         (color_t){ 64, 64, 64 };

	 Title
	ypos = 10;
    M5.Lcd.drawString(OTA Update..., CENTER, ypos, GFXFF);

	ypos = 180;
	if (otaUpdate.otaUpdateError_) {
		 Error Message
		 M5.Lcd.drawString(otaErrorNames[otaUpdate.otaUpdateErrorNr_], CENTER, ypos, GFXFF);
	}
	else if (otaUpdate.otaUpdateEnd_) {
		M5.Lcd.drawString(Done, rebooting..., CENTER, ypos, GFXFF);
	}
	else {
		if (clearScreen)
			TFT_drawRect(x0, y0, x1, y1, TFT_WHITE);
		mapx = map(otaUpdate.otaUpdateProgress_, 0, 100, 0, x1 - x0 - 2  BAR_PAD);
		TFT_fillRect(x0 + BAR_PAD, y0 + BAR_PAD, mapx, y1 - y0 - 2  BAR_PAD, TFT_LIGHTGREY);
	}
}

