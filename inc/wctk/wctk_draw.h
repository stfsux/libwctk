
#ifndef _WCTK_DRAW_H_
#define _WCTK_DRAW_H_


void wctk_draw_rect (sint x, sint y, sint width, sint height,
    short pair);
void wctk_draw_rect_fill (sint x, sint y, sint width,
    sint height, chtype ch);
void wctk_draw_shadow (sint x, sint y, sint width, sint height);
void wctk_draw_set_cpair (sint x, sint y, short cpair);
void wctk_draw_cursor (sint x, sint y);
void wctk_draw_vline (sint x, sint y, sint l, short cpair);
void wctk_draw_hline (sint x, sint y, sint l, short cpair);

#endif

