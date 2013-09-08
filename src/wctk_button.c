
#include <stdlib.h>
#include <string.h>
#include "wctk/wctk.h"

/*-----------------------------------------------------------------*/
pwctk_button_t
 wctk_button_create (char *name, sint x, sint y, sint w, sint h,
     uchar flags, pwctk_window_t parent)
{
  pwctk_button_t btn = NULL;
  
  if (parent == NULL)
    return NULL;

  if (w <= 2 ||
      h <= 0)
    return NULL;

  btn = calloc (1, sizeof(wctk_button_t));
 
  if (btn == NULL)
    return NULL;
 
  btn->name = calloc (strlen(name)+1, sizeof(char));
 
  if (btn->name == NULL)
  {
    free (btn);
    return NULL;
  }
 
  strncpy (btn->name, name, strlen(name));
  btn->xpos = x + 1;
  btn->ypos = y + 1;
  btn->width = w;
  btn->height = h;
  btn->flags = flags;
  btn->colors.default_cpair = WCTKC_WHITE_GREEN;
  btn->colors.focus_cpair   = WCTKC_WHITE_RED;
  btn->colors.clicked_cpair = WCTKC_WHITE_GREEN;
  btn->parent = parent;

  wctk_widget_attach (btn->parent, btn, WCTKW_BUTTON);
  return btn;
}

/*-----------------------------------------------------------------*/
void
 wctk_button_draw (pwctk_button_t btn, uint draw_area_width,
     uint draw_area_height)
{
  uint xpos_name = 0, ypos_name = 0;
  uint i = 0;

  if (strlen(btn->name) >= (uint)btn->width)
    xpos_name = btn->parent->xpos + btn->xpos;
  else
    xpos_name = btn->parent->xpos + btn->xpos +
      (btn->width-strlen(btn->name))/2;

  ypos_name = btn->parent->ypos + btn->ypos +
    (btn->height-1)/2;

  /* Draw button. */
  if (btn->state & WCTK_BUTTON_STATE_FOCUS)
  {
    wctk_draw_rect_fill (btn->parent->xpos + btn->xpos,
                         btn->parent->ypos + btn->ypos,
                         draw_area_width,
                         draw_area_height,
                         ' '|COLOR_PAIR(btn->colors.focus_cpair));
    for (i = 0; (i < strlen(btn->name)) &&
        (i+1 < draw_area_width); i++)
    {
      mvaddch (ypos_name, xpos_name + i,
          btn->name[i]|COLOR_PAIR(btn->colors.focus_cpair));
    }
  }
  else
  {
    wctk_draw_rect_fill (btn->parent->xpos + btn->xpos,
                       btn->parent->ypos + btn->ypos,
                       draw_area_width,
                       draw_area_height,
                       ' '|COLOR_PAIR(btn->colors.default_cpair));
    for (i = 0; (i < strlen(btn->name)) &&
                (i+1 < draw_area_width) &&
                (ypos_name < btn->ypos + btn->parent->xpos + draw_area_height); i++)
    {
      mvaddch (ypos_name, xpos_name + i,
          btn->name[i]|COLOR_PAIR(btn->colors.default_cpair));
    }

  }

  /* Draw bottom shadow. */
  wctk_draw_rect_fill (btn->parent->xpos + btn->xpos + 1,
                       btn->parent->ypos + btn->ypos + draw_area_height,
                       draw_area_width,
                       1,
                       ' '|COLOR_PAIR(WCTKC_BLACK_BLACK));

  /* Draw right shadow. */
  wctk_draw_rect_fill (btn->parent->xpos + btn->xpos + draw_area_width,
                       btn->parent->ypos + btn->ypos + 1,
                       1,
                       draw_area_height,
                       ' '|COLOR_PAIR(WCTKC_BLACK_BLACK));
}

/*-----------------------------------------------------------------*/
void
 wctk_button_set_focus (pwctk_button_t btn, uchar b)
{
  if (b)
    btn->state = btn->state | WCTK_BUTTON_STATE_FOCUS;
  else
    btn->state = btn->state & (~WCTK_BUTTON_STATE_FOCUS);
}

/*-----------------------------------------------------------------*/
void
 wctk_button_move (pwctk_button_t btn, sint x, sint y)
{
  if (btn != NULL)
  {
    btn->xpos = x + 1;
    btn->ypos = y + 1;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_button_destroy (pwctk_button_t btn)
{
  if (btn != NULL)
  {
    if (btn->name != NULL)
      free (btn->name);
    free (btn);
  }
}

