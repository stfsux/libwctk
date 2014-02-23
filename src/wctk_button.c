
#include <stdlib.h>
#include <string.h>
#include "wctk/wctk.h"

/*-----------------------------------------------------------------*/
pwctk_button_t
 wctk_button_create (char *name, int32_t x, int32_t y, int32_t w, int32_t h,
     uint8_t flags, pwctk_window_t parent, uint32_t uid)
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
  btn->colors.press_cpair   = WCTKC_WHITE_GREEN;
  btn->parent = parent;
  btn->uid = uid;

  wctk_widget_attach (btn->parent, btn, WCTKW_BUTTON);
  return btn;
}

/*-----------------------------------------------------------------*/
void
 wctk_button_draw (pwctk_button_t btn, uint32_t draw_area_width,
     uint32_t draw_area_height)
{
  uint32_t xpos_name = 0, ypos_name = 0;
  uint32_t i = 0;

  if (strlen(btn->name) >= (uint32_t)btn->width)
    xpos_name = btn->parent->xpos + btn->xpos;
  else
    xpos_name = btn->parent->xpos + btn->xpos +
      (btn->width-strlen(btn->name))/2;

  ypos_name = btn->parent->ypos + btn->ypos +
    (btn->height-1)/2;

  /* Draw button. */
  if ((btn->state&WCTK_BUTTON_STATE_PRESS) &&
      (btn->state&WCTK_BUTTON_STATE_FOCUS))
  {
    wctk_draw_rect_fill (btn->parent->xpos + btn->xpos + 1,
                         btn->parent->ypos + btn->ypos + 1,
                         draw_area_width,
                         draw_area_height,
                         ' '|COLOR_PAIR(btn->colors.focus_cpair));
    for (i = 0; (i < strlen(btn->name)) &&
                (i+1 < draw_area_width) &&
                (ypos_name < btn->ypos + btn->parent->xpos + draw_area_height);
                i++)
    {
      mvaddch (ypos_name + 1, xpos_name + i + 1,
          btn->name[i]|COLOR_PAIR(btn->colors.focus_cpair));
    }
  }
  else if ((btn->state&WCTK_BUTTON_STATE_FOCUS) &&
           !(btn->state&WCTK_BUTTON_STATE_PRESS))
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
  else if ((btn->state & WCTK_BUTTON_STATE_PRESS) &&
           !(btn->state&WCTK_BUTTON_STATE_FOCUS))
  {
    wctk_draw_rect_fill (btn->parent->xpos + btn->xpos + 1,
                       btn->parent->ypos + btn->ypos + 1,
                       draw_area_width,
                       draw_area_height,
                       ' '|COLOR_PAIR(btn->colors.press_cpair));
    for (i = 0; (i < strlen(btn->name)) &&
                (i+1 < draw_area_width) &&
                (ypos_name < btn->ypos + btn->parent->xpos + draw_area_height);
                i++)
    {
      mvaddch (ypos_name + 1, xpos_name + i + 1,
          btn->name[i]|COLOR_PAIR(btn->colors.press_cpair));
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
                (ypos_name < btn->ypos + btn->parent->ypos + draw_area_height);
                i++)
    {
      mvaddch (ypos_name, xpos_name + i,
          btn->name[i]|COLOR_PAIR(btn->colors.default_cpair));
    }

  }

  /* Draw bottom shadow. */
  if (!(btn->state & WCTK_BUTTON_STATE_PRESS))
  {
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

  if (btn->reset)
  {
    btn->counter++;
    if (btn->counter > 100)
    {
      btn->counter = 0;
      btn->reset = 0;
      wctk_button_state_set (btn, 0);
    }
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_button_event_translate (pwctk_button_t btn,
     pwctk_event_t event)
{
  if (btn   == NULL ||
      event == NULL)
    return;

  switch (event->type)
  {
    case WCTK_EVENT_MOUSE:
      if (wctk_mouse_pressed (event))
      {
        if (event->mevent.x >= btn->parent->xpos + btn->xpos    &&
            event->mevent.x <= btn->parent->xpos + btn->xpos + btn->width  &&
            event->mevent.y >= btn->parent->ypos + btn->ypos               &&
            event->mevent.y <= btn->parent->ypos + btn->ypos + btn->height)
        {
          wctk_button_state_set (btn, 1);
          event->type = WCTK_EVENT_BUTTON;
          event->data = btn->uid;
        }
      }
      if (wctk_mouse_released (event))
      {
        wctk_button_state_set (btn, 0);
      }
      break;

    case WCTK_EVENT_KEY:
      if (event->data == ' '  ||
          event->data == '\r')
      {
        wctk_button_state_set (btn, 1);
        btn->reset = 1;
        event->type = WCTK_EVENT_BUTTON;
        event->data = btn->uid;
      }
      break;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_button_state_set (pwctk_button_t btn, uint8_t b)
{
  if (b)
    btn->state = btn->state | WCTK_BUTTON_STATE_PRESS;
  else
    btn->state = btn->state & (~WCTK_BUTTON_STATE_PRESS);
}

/*-----------------------------------------------------------------*/
void
 wctk_button_focus_set (pwctk_button_t btn, uint8_t b)
{
  if (b)
    btn->state = btn->state | WCTK_BUTTON_STATE_FOCUS;
  else
  {
    btn->state = btn->state & (~WCTK_BUTTON_STATE_FOCUS);
    btn->state = btn->state & (~WCTK_BUTTON_STATE_PRESS);
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_button_move (pwctk_button_t btn, int32_t x, int32_t y)
{
  if (btn != NULL)
  {
    btn->xpos = x + 1;
    btn->ypos = y + 1;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_button_resize (pwctk_button_t btn, int32_t w, int32_t h)
{
  if (btn == NULL ||
      w <= 1      ||
      w <= 0)
    return;

  btn->width  = w;
  btn->height = h;
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

