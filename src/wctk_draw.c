#include <stdlib.h>
#include <ncurses.h>
#include "wctk/wctk.h"

/*-----------------------------------------------------------------*/
void
 wctk_draw_rect (sint x, sint y,
                 sint width, sint height,
                 short pair)
{
  sint xpos, ypos;

  if (x > WCTK_SCREEN_WIDTH  ||
      y > WCTK_SCREEN_HEIGHT ||
      x <= 20                ||
      y <= 10)
    return;

  for (xpos = x+1; xpos < (x+width-1); xpos++)
    mvaddch (y, xpos, ACS_HLINE|COLOR_PAIR(pair));
  for (xpos = x+1; xpos < (x+width-1); xpos++)
    mvaddch (y+height-1, xpos, ACS_HLINE|COLOR_PAIR(pair));
  for (ypos = y+1; ypos < (y+height-1); ypos++)
    mvaddch (ypos, x, ACS_VLINE|COLOR_PAIR(pair));
  for (ypos = y+1; ypos < (y+height-1); ypos++)
    mvaddch (ypos, x+width-1, ACS_VLINE|COLOR_PAIR(pair));
  mvaddch (y,          x,         ACS_ULCORNER|COLOR_PAIR(pair));
  mvaddch (y,          x+width-1, ACS_URCORNER|COLOR_PAIR(pair));
  mvaddch (y+height-1, x,         ACS_LLCORNER|COLOR_PAIR(pair));
  mvaddch (y+height-1, x+width-1, ACS_LRCORNER|COLOR_PAIR(pair));
}

/*-----------------------------------------------------------------*/
void
 wctk_draw_rect_fill (sint x, sint y,
                      sint width, sint height,
                      chtype ch)
{
  sint xpos, ypos;
  if (width  <= 0 ||
      height <= 0)
    return;
  for (xpos = x; xpos < (x+width); xpos++)
  {
    for (ypos = y; ypos < (y+height); ypos++)
    {
      mvaddch (ypos, xpos, ch);
    }
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_draw_shadow (sint x, sint y, sint width, sint height)
{
  sint i;
  short pair = 0;
  chtype ch = 0, newch = 0;
  for (i = 0; i < width; i++)
  {
    ch = mvinch (y+height, x+i+1);
    pair = ch&A_COLOR;
    newch = ch & (~A_COLOR);
    newch = newch | COLOR_PAIR(((pair-1)%8)+1);
    mvaddch (y+height, x+i+1, newch);
  }
  for (i = 0; i < height; i++)
  {
    ch = mvinch (y+i+1, x+width);
    pair = ch&A_COLOR;
    newch = ch & (~A_COLOR);
    newch = newch | COLOR_PAIR(((pair-1)%8)+1);
    mvaddch (y+i+1, x+width, newch);
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_draw_modify_cpair (sint x, sint y, short cpair)
{
  chtype ch = 0;
  ch = mvinch (y, x);
  ch = ch&(~A_COLOR);
  mvaddch (y, x, ch|COLOR_PAIR(cpair));
}

/*-----------------------------------------------------------------*/
void
 wctk_draw_cursor (sint x, sint y)
{
  chtype c = 0;
  c = mvinch (y, x);
  mvaddch (y, x, c|A_REVERSE);
}

/*-----------------------------------------------------------------*/
void
 wctk_draw_vline (sint x, sint y, sint l, short cpair)
{
  sint ypos;
  if ( l < 0)
    return;
  for (ypos = y; ypos < (y+l); ypos++)
    mvaddch (ypos, x, ACS_VLINE|COLOR_PAIR(cpair));
}

/*-----------------------------------------------------------------*/
void
 wctk_draw_hline (sint x, sint y, sint l, short cpair)
{
  sint xpos;
  if (l < 0)
    return;
  for (xpos = x; xpos < (x+l); xpos++)
    mvaddch (y, xpos, ACS_HLINE|COLOR_PAIR(cpair));
}

