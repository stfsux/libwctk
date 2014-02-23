#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "wctk/wctk.h"

 
/*-----------------------------------------------------------------*/
pwctk_window_t
 wctk_window_create (char* title, int32_t x, int32_t y, int32_t w, int32_t h,
     uint8_t flags, uint32_t uid)
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
  window->colors.default_cpair = WCTKC_WHITE_BLUE;
  window->colors.titlebar_cpair= WCTKC_WHITE_BLUE;
  window->colors.focused_cpair = WCTKC_WHITE_RED;
  window->uid           = uid;
  wctk_zorder_push (window);
  return window;
}

/*-----------------------------------------------------------------*/
void
 wctk_window_set_colors (pwctk_window_t window, 
     pwctk_window_colors_t colors)
{
  if (window == NULL ||
      colors == NULL)
    return;

  memcpy (&window->colors, colors, sizeof(wctk_window_colors_t));
}

/*-----------------------------------------------------------------*/
void
 wctk_window_draw (pwctk_window_t window)
{
  if (window == NULL)
    return;
  /* Draw title bar. */
  /* Set color attribute */
  if (window->state&WCTK_WINDOW_STATE_FOCUS)
  {
    wctk_draw_rect_fill (window->xpos, window->ypos, window->width, 1,
      ' '|COLOR_PAIR(window->colors.focused_cpair));
    attr_on (COLOR_PAIR(window->colors.focused_cpair), NULL);
  }
  else
  {
    wctk_draw_rect_fill (window->xpos, window->ypos, window->width, 1,
      ' '|COLOR_PAIR(window->colors.titlebar_cpair));
    attr_on (COLOR_PAIR(window->colors.titlebar_cpair), NULL);
  }
  /* Draw title. */
  attr_on (A_BOLD, NULL);
  /* Draw a line into the title bar. */
  if (window->flags&WCTK_WINDOW_TITLEBAR_LINE)
    mvhline (window->ypos, window->xpos, ACS_HLINE, window->width);
  mvprintw (window->ypos, window->xpos+1, "%s", window->title);
  attr_off (A_BOLD, NULL);

  /* Reset color attribute. */
  if (window->state&WCTK_WINDOW_STATE_FOCUS)
    attr_off (COLOR_PAIR(window->colors.focused_cpair), NULL);
  else
    attr_off (COLOR_PAIR(window->colors.default_cpair), NULL);

  /* Draw window. */
  wctk_draw_rect_fill (window->xpos, window->ypos+1, window->width,
    window->height-1, ' '|COLOR_PAIR(window->colors.default_cpair));

  /* Draw widgets. */
  wctk_widget_draw (window);
  
  /* Drop shadow. */
  if (!(window->flags&WCTK_WINDOW_NOSHADOW))
    wctk_draw_shadow (window->xpos, window->ypos, window->width, window->height);
}

/*-----------------------------------------------------------------*/
void
 wctk_window_move (pwctk_window_t window, int32_t x, int32_t y)
{
  if (window == NULL)
    return;

  window->xpos = x;
  window->ypos = y;
}

/*-----------------------------------------------------------------*/
void
 wctk_window_resize (pwctk_window_t window, int32_t w, int32_t h)
{
  if (window == NULL)
    return;

  if (w >= 20)
    window->width = w;
  if (h >= 10)
    window->height = h;
}

/*-----------------------------------------------------------------*/
void
 wctk_window_focus_set (pwctk_window_t window, uint8_t b)
{
  if (window != NULL)
  {
    if (b)
    {
      window->state = window->state | WCTK_WINDOW_STATE_FOCUS;
      wctk_widget_focus_set (window->widget_focus, 1);
    }
    else
    {
      window->state = window->state & (~WCTK_WINDOW_STATE_FOCUS);
      wctk_widget_focus_set (window->widget_focus, 0);
    }
  }
}

/*-----------------------------------------------------------------*/
uint32_t
 wctk_window_state_get (pwctk_window_t window)
{
  if (window == NULL)
    return 0;
  return window->state;
}

/*-----------------------------------------------------------------*/
void
 wctk_window_state_set (pwctk_window_t window, uint32_t state)
{
  if (window == NULL)
    return;
  window->state = window->state | state;
}


/*-----------------------------------------------------------------*/
void
 wctk_window_state_clr (pwctk_window_t window, uint32_t state)
{
  if (window == NULL)
    return;
  window->state = window->state & (~state);
}

/*-----------------------------------------------------------------*/
uint8_t
 wctk_window_region_titlebar (pwctk_window_t window, int32_t x,
     int32_t y)
{
  if (window == NULL)
    return 0;
  if (x >= (window->xpos)               &&
      x <= (window->xpos+(int32_t)window->width) &&
      y == (window->ypos))
    return 1;
  return 0;
}

/*-----------------------------------------------------------------*/
uint8_t 
 wctk_window_region_bresize (pwctk_window_t window, int32_t x,
     int32_t y)
{
  if (window == NULL)
    return 0;
  if (window->flags&WCTK_WINDOW_NORESIZE ||
      window->state&WCTK_WINDOW_STATE_MAXIMIZE)
    return 0;
  if (x == (window->xpos+(int32_t)window->width-1) &&
      y == (window->ypos+(int32_t)window->height-1))
    return 1;
  return 0;
}

/*-----------------------------------------------------------------*/
uint8_t
 wctk_window_region_bclose (pwctk_window_t window, int32_t x,
     int32_t y)
{
  if (window == NULL)
    return 0;
  if (x == (window->xpos+window->width-2) &&
      y == (window->ypos))
    return 1;
  return 0;
}

/*-----------------------------------------------------------------*/
uint8_t
 wctk_window_region_bmin (pwctk_window_t window, int32_t x,
     int32_t y)
{
  if (window == NULL)
    return 0;
  if (window->flags&WCTK_WINDOW_NOMIN)
    return 0;
  if (window->flags&WCTK_WINDOW_NOMAX)
  {
    if (x == (window->xpos+window->width-5) &&
        y == (window->ypos))
      return 1;
  }
  else
  {
    if (x == (window->xpos+window->width-8) &&
        y == window->ypos)
      return 1;
  }
  return 0;
}

/*-----------------------------------------------------------------*/
uint8_t
 wctk_window_region_bmax (pwctk_window_t window, int32_t x,
     int32_t y)
{
  if (window == NULL)
    return 0;
  if (window->flags&WCTK_WINDOW_NOMAX)
    return 0;
  if (x == (window->xpos+window->width-5) &&
      y == (window->ypos))
    return 1;
  return 0;
}

/*-----------------------------------------------------------------*/
int32_t
 wctk_window_width_get (pwctk_window_t window)
{
  if (window == NULL)
    return 0;
  return window->width;
}

/*-----------------------------------------------------------------*/
int32_t
 wctk_window_height_get (pwctk_window_t window)
{
  if (window == NULL)
    return 0;
  return window->height;
}

/*-----------------------------------------------------------------*/
void
 wctk_window_destroy_safe (pwctk_window_t *window)
{
  if (*window != NULL)
  {
    if ((*window)->title != NULL)
      free ((*window)->title);
    wctk_widget_destroy (*window);
    free (*window);
    *window = NULL;
  }
}
