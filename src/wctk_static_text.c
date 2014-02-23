
#include <stdlib.h>
#include <string.h>
#include "wctk/wctk.h"

/*------------------------------------------------------------------*/
pwctk_static_text_t
 wctk_static_text_create (char *txt, int32_t x, int32_t y,
     int32_t width, int32_t height, pwctk_window_t parent)
{
  pwctk_static_text_t st = NULL;
  
  if (parent == NULL ||
      width < 3 ||
      height < 3)
    return NULL;

  st = calloc (1, sizeof(wctk_static_text_t));
  if (st == NULL)
    return NULL;

  st->xpos   = x + 1;
  st->ypos   = y + 1;
  st->width  = width;
  st->height = height;
  st->parent = parent;
  st->default_cpair = parent->colors.default_cpair;

  if (txt != NULL)
  {
    st->text = calloc (strlen(txt)+1, sizeof(char));
    if (st->text == NULL)
    {
      free (st);
      return NULL;
    }
    strncpy (st->text, txt, strlen(txt));
  }

  wctk_widget_attach (st->parent, st, WCTKW_STATICTEXT);
  return st;
}

/*------------------------------------------------------------------*/
void
 wctk_static_text_set (pwctk_static_text_t st, char* txt)
{
  if (st == NULL)
    return;

  st->text = realloc (st->text, (strlen(txt)+1)*sizeof(char));
  if (st->text == NULL)
    return;

  strncpy (st->text, txt, strlen(txt));
  st->text[strlen(txt)] = 0;
}

/*------------------------------------------------------------------*/
void
 wctk_static_text_draw (pwctk_static_text_t st,
     int32_t draw_area_width, int32_t draw_area_height)
{
  uint32_t i;
  int32_t y = 0, x = 0;

  if (st == NULL)
    return;

  for (i = 0; (i < strlen(st->text)); i++)
  {
    if (st->text[i] == '\n' || x >= draw_area_width)
    {
      x = 0;
      y++;
      if (y >= draw_area_height)
        break;
      continue;
    }
    mvaddch (st->parent->ypos + st->ypos + y,
        st->parent->xpos + st->xpos + x,
        st->text[i] | COLOR_PAIR(st->default_cpair));
    x++;
  }
}

/*------------------------------------------------------------------*/
void
 wctk_static_text_resize (pwctk_static_text_t st, int32_t width,
     int32_t height)
{
  if (st == NULL)
    return;

  if (width < 3 ||
      height < 3)
    return;

  st->width = width;
  st->height = height;
}

/*------------------------------------------------------------------*/
void
 wctk_static_text_move (pwctk_static_text_t st, int32_t x, int32_t y)
{
  if (x < 0 ||
      y < 0 ||
      st == NULL)
    return;

  st->xpos = x + 1;
  st->ypos = y + 1;
}

/*------------------------------------------------------------------*/
void
 wctk_static_text_destroy (pwctk_static_text_t st)
{
  if (st != NULL)
  {
    if (st->text != NULL)
      free (st->text);
    free (st);
  }
}

