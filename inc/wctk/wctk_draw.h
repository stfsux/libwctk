
#ifndef _WCTK_DRAW_H_
#define _WCTK_DRAW_H_

void wctk_draw_rect (int32_t x, int32_t y, int32_t width, int32_t height,
    short pair);
void wctk_draw_rect_fill (int32_t x, int32_t y, int32_t width,
    int32_t height, chtype ch);
void wctk_draw_shadow (int32_t x, int32_t y, int32_t width, int32_t height);
void wctk_draw_set_cpair (int32_t x, int32_t y, short cpair);
void wctk_draw_cursor (int32_t x, int32_t y);
void wctk_draw_vline (int32_t x, int32_t y, int32_t l, short cpair);
void wctk_draw_hline (int32_t x, int32_t y, int32_t l, short cpair);

#endif

