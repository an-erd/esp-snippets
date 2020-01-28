//---------------------------------
static void disp_header(char *info)
{
	TFT_fillScreen(TFT_BLACK);
	TFT_resetclipwin();

	_fg = TFT_YELLOW;
	_bg = (color_t){ 64, 64, 64 };

    if (_width < 240) TFT_setFont(DEF_SMALL_FONT, NULL);
	else TFT_setFont(DEFAULT_FONT, NULL);
	TFT_fillRect(0, 0, _width-1, TFT_getfontheight()+8, _bg);
	TFT_drawRect(0, 0, _width-1, TFT_getfontheight()+8, TFT_CYAN);

	TFT_fillRect(0, _height-TFT_getfontheight()-9, _width-1, TFT_getfontheight()+8, _bg);
	TFT_drawRect(0, _height-TFT_getfontheight()-9, _width-1, TFT_getfontheight()+8, TFT_CYAN);

	TFT_print(info, CENTER, 4);
	_dispTime();

	_bg = TFT_BLACK;
	TFT_setclipwin(0,TFT_getfontheight()+9, _width-1, _height-TFT_getfontheight()-10);
}

//---------------------------------------------
static void update_header(char *hdr, char *ftr)
{
	color_t last_fg, last_bg;

	TFT_saveClipWin();
	TFT_resetclipwin();

	Font curr_font = cfont;
	last_bg = _bg;
	last_fg = _fg;
	_fg = TFT_YELLOW;
	_bg = (color_t){ 64, 64, 64 };
    if (_width < 240) TFT_setFont(DEF_SMALL_FONT, NULL);
	else TFT_setFont(DEFAULT_FONT, NULL);

	if (hdr) {
		TFT_fillRect(1, 1, _width-3, TFT_getfontheight()+6, _bg);
		TFT_print(hdr, CENTER, 4);
	}

	if (ftr) {
		TFT_fillRect(1, _height-TFT_getfontheight()-8, _width-3, TFT_getfontheight()+6, _bg);
		if (strlen(ftr) == 0) _dispTime();
		else TFT_print(ftr, CENTER, _height-TFT_getfontheight()-5);
	}

	cfont = curr_font;
	_fg = last_fg;
	_bg = last_bg;

	TFT_restoreClipWin();
}
