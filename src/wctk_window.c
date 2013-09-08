#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "wctk/wctk.h"

 
/*-----------------------------------------------------------------*/
pwctk_window_t
 wctk_window_create (char* title, sint x, sint y, sint w, sint h,
     uchar flags, short default_cpair, short titlebar_cpair,
     short focused_cpair, uint uid)
{
  pwctk_window_t window = NULL;
  if (w  <= 2 ||
      h <= 2)
    return NULL;
  window = calloc (1, sizeof(wctk_window_t));
  if (window == NULL)
    return NULL;
  if (strlen (title) >= 255)
  {
    free (window);
    return NULL;
  }
  window->title = calloc (strlen(title)+1, sizeof (char));
  if (window->title == NULL)
  {
    free (window);
    return NULL;
  }
  sprintf (window->title, "%s", title);
  window->xpos          = x;
  window->ypos          = y;
  window->width         = w;
  window->height        = h;
  window->flags         = flags;
  window->default_cpair = default_cpair;
  window->titlebar_cpair= titlebar_cpair;
  window->focused_cpair = focused_cpair;
  window->uid           = uid;
  wctk_zorder_push (window);
  return window;
}

/*-----------------------------------------------------------------*/
void
 wctk_window_draw (pwctk_window_t window)
{
  if (window == NULL)
    return;
  /* Draw title bar. */
  if (window->state&WCTK_WINDOW_STATE_FOCUS)
  {
    wctk_draw_rect_fill (window->xpos, window->ypos, window->width, 1,
      ' '|COLOR_PAIR(window->focused_cpair));
    attr_on (COLOR_PAIR(window->focused_cpair), NULL);
  }
  else
  {
    wctk_draw_rect_fill (window->xpos, window->ypos, window->width, 1,
      ' '|COLOR_PAIR(window->titlebar_cpair));
    attr_on (COLOR_PAIR(window->titlebar_cpair), NULL);
  }
  mvprintw (window->ypos, window->xpos+1, "%s", window->title);
  mvprintw (window->ypos, window->xpos+window->width-9, "[.][o][x]");
  if (window->state&WCTK_WINDOW_STATE_FOCUS)
    attr_off (COLOR_PAIR(window->focused_cpair), NULL);
  else
    attr_off (COLOR_PAIR(window->default_cpair), NULL);

  /* Draw window. */
  wctk_draw_rect_fill (window->xpos, window->ypos+1, window->width,
    window->height-1, ' '|COLOR_PAIR(window->default_cpair));

  /* Draw vertical and horizontal lines. */
  wctk_draw_vline (window->xpos, window->ypos+1, window->height-1, window->default_cpair);
  wctk_draw_vline (window->xpos+window->width-1, window->ypos+1, window->height-2, window->default_cpair);
  wctk_draw_hline (window->xpos, window->ypos+window->height-1, window->width-1, window->default_cpair);

  /* Draw widgets. */
  wctk_widget_draw (window);
  
  /* Draw corners. */
  mvaddch (window->ypos+window->height-1, window->xpos+window->width-1,
      ACS_LRCORNER|COLOR_PAIR(window->default_cpair));
  mvaddch (window->ypos+window->height-1, window->xpos,
      ACS_LLCORNER|COLOR_PAIR(window->default_cpair));

  /* Drop shadow. */
  wctk_draw_shadow (window->xpos, window->ypos, window->width, window->height);
}

/*-----------------------------------------------------------------*/
void
 wctk_window_move (pwctk_window_t window, sint x, sint y)
{
  if (window != NULL)
  {
    window->xpos = x;
    window->ypos = y;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_window_resize (pwctk_window_t window, sint w, sint h)
{
  if (window != NULL)
  {
    if (w > 20)
      window->width = w;
    if (h > 10)
      window->height = h;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_window_set_focus (pwctk_window_t window, uchar b)
{
  if (window != NULL)
  {
    if (b)
    {
      window->state = window->state | WCTK_WINDOW_STATE_FOCUS;
      wctk_widget_set_focus (window->widget_focus, 1);
    }
    else
    {
      window->state = window->state & (~WCTK_WINDOW_STATE_FOCUS);
      wctk_widget_set_focus (window->widget_focus, 0);
    }
  }
}

/*-----------------------------------------------------------------*/
uchar
 wctk_window_region_titlebar (pwctk_window_t window, sint x,
     sint y)
{
  if (window == NULL)
    return 0;
  if (x >= (window->xpos)               &&
      x <= (window->xpos+(sint)window->width) &&
      y == (window->ypos))
    return 1;
  return 0;
}

/*-----------------------------------------------------------------*/
uchar 
 wctk_window_region_bresize (pwctk_window_t window, sint x,
     sint y)
{
  if (window == NULL)
    return 0;
  if (x == (window->xpos+(sint)window->width-1) &&
      y == (window->ypos+(sint)window->height-1))
    return 1;
  return 0;
}

/*-----------------------------------------------------------------*/
uchar
 wctk_window_region_bclose (pwctk_window_t window, sint x,
     sint y)
{
  if (window == NULL)
    return 0;
  if (x == (window->xpos+(sint)window->width-2) &&
      y == (window->ypos))
    return 1;
  return 0;
}

/*-----------------------------------------------------------------*/
void
 wctk_window_destroy (pwctk_window_t window)
{
  if (window != NULL)
  {
    if (window->title != NULL)
      free (window->title);
    wctk_widget_destroy (window);
    free (window);
  }
}
