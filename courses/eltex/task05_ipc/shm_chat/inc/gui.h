#ifndef __GUI_H__
#define __GUI_H__

#include "chat.h"

#define CHAT_CLR	COLOR_PAIR(1)
#define BOTM_CLR	COLOR_PAIR(2)
#define POPUP_CLR	COLOR_PAIR(3)
#define BORDER_CLR	COLOR_PAIR(4)
#define NOTIFY_CLR	COLOR_PAIR(5)

#define repaint_window(wtype) draw_window(wtype)

void draw_left(enum win_t wtype);
void draw_rite(enum win_t wtype);
void draw_botm(enum win_t wtype);
void draw_window(enum win_t wtype);

int input_nickname(void);

inline void __attribute__ ((always_inline))
update_gui(void)
{
	for (int i = 0; i < NWINDOWS; ++i) {
		touchwin(win[i]);
		wnoutrefresh(win[i]);
	}

	repaint_window(BOTM_W);
	wmove(win[BOTM_W], DEFPOS_Y, DEFPOS_X);
	doupdate();
}

#endif
