
#include <stdlib.h>
#include "wctk/wctk.h"

void
 wctk_scrollbar_vertical_draw (int32_t x, int32_t y, int32_t height,
     int32_t vheight, int32_t vy)
{
  wctk_draw_rect_fill (x, y, 1, height, ACS_CKBOARD|COLOR_PAIR(WCTKC_WHITE_BLACK));
  mvaddch (y, x, '^'|COLOR_PAIR(WCTKC_BLACK_WHITE));
  mvaddch (y+height-1, x, 'v'|COLOR_PAIR(WCTKC_BLACK_WHITE));
  if (height-2 < vheight)
    wctk_draw_rect_fill (x, y+1+vy*(height-2-((height-2)*(height-2)/vheight+1))/vheight, 1, (height-2)*(height-2)/vheight+1, ' '|COLOR_PAIR(WCTKC_WHITE_WHITE));
  else
    wctk_draw_rect_fill (x, y+1, 1, (height-2), ' '|COLOR_PAIR(WCTKC_WHITE_WHITE));
}

