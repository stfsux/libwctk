#include <stdlib.h>
#include "wctk/wctk.h"

/*-----------------------------------------------------------------*/
void
 wctk_widget_attach (pwctk_window_t parent, void *widget,
     uint type)
{
  pwctk_widget_t new_widget = NULL;

  if (parent == NULL)
    return;

  if (type != WCTKW_TEXTVIEW &&
      type != WCTKW_BUTTON)
    return;

  new_widget = calloc (1, sizeof(wctk_widget_t));
  if (new_widget == NULL)
    return;

  new_widget->widget = widget;
  new_widget->type = type;

  if (parent->widget_list == NULL)
  {
    parent->widget_list = new_widget;
    parent->widget_focus = parent->widget_list;
  }
  else
  {
    pwctk_widget_t ptr = parent->widget_list;
    while (ptr->next != NULL)
      ptr = ptr->next;
    ptr->next = new_widget;
    new_widget->prev = ptr;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_widget_event_translate (pwctk_window_t parent,
     pwctk_event_t event)
{
  if (parent == NULL ||
      event  == NULL)
    return;

  if (parent->widget_focus != NULL)
  {
    switch (parent->widget_focus->type)
    {
      case WCTKW_TEXTVIEW:
          wctk_textview_event_translate (
              WCTK_WIDGET_TEXTVIEW(parent->widget_focus->widget),
              event);
          break;
    }
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_widget_set_focus (pwctk_widget_t widget, uchar b)
{
  if (widget == NULL)
    return;

  switch (widget->type)
  {
    case WCTKW_TEXTVIEW:
      wctk_textview_set_focus (
          WCTK_WIDGET_TEXTVIEW(widget->widget), b
          );
      break;

    case WCTKW_BUTTON:
      wctk_button_set_focus (
          WCTK_WIDGET_BUTTON(widget->widget), b
          );
      break;
  }
}

/*-----------------------------------------------------------------*/
uchar
 wctk_widget_focus_next (pwctk_window_t window)
{
  if (window == NULL)
    return 0;

  if (window->widget_focus == NULL)
    return 0;

  wctk_widget_set_focus (window->widget_focus, 0);
  if (window->widget_focus->next != NULL)
    window->widget_focus = window->widget_focus->next;
  else
    return 0;
  wctk_widget_set_focus (window->widget_focus, 1);
  return 1;
}

/*-----------------------------------------------------------------*/
void
 wctk_widget_focus_first (pwctk_window_t window)
{
  if (window == NULL)
    return;
  wctk_widget_set_focus (window->widget_focus, 0);
  window->widget_focus = window->widget_list;
  wctk_widget_set_focus (window->widget_focus, 1);
}

/*-----------------------------------------------------------------*/
void
 wctk_widget_draw (pwctk_window_t parent)
{
  pwctk_widget_t widget = NULL;
  if (parent == NULL)
    return;

  widget = parent->widget_list;

  while (widget != NULL)
  {
    switch (widget->type)
    {
      case WCTKW_TEXTVIEW:
        if (WCTK_TEXTVIEW_DRAWABLE(WCTK_WIDGET_TEXTVIEW(widget->widget)))
        {
          wctk_textview_draw 
            (
              WCTK_WIDGET_TEXTVIEW(widget->widget),
              WCTK_TEXTVIEW_DRAW_WIDTH(WCTK_WIDGET_TEXTVIEW(widget->widget)),
              WCTK_TEXTVIEW_DRAW_HEIGHT(WCTK_WIDGET_TEXTVIEW(widget->widget))
            );
        }
        break;

      case WCTKW_BUTTON:
        if (WCTK_BUTTON_DRAWABLE(WCTK_WIDGET_BUTTON(widget->widget)))
        {
          wctk_button_draw 
            (
              WCTK_WIDGET_BUTTON(widget->widget),
              WCTK_BUTTON_DRAW_WIDTH(WCTK_WIDGET_BUTTON(widget->widget)),
              WCTK_BUTTON_DRAW_HEIGHT(WCTK_WIDGET_BUTTON(widget->widget))
            );
        }
        break;
    }
    widget = widget->next;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_widget_destroy (pwctk_window_t parent)
{
  pwctk_widget_t ptr = NULL, fptr = NULL;
  ptr = parent->widget_list;
  while (ptr != NULL)
  {
    fptr = ptr;
    switch (fptr->type)
    {
      case WCTKW_TEXTVIEW:
        wctk_textview_destroy (WCTK_WIDGET_TEXTVIEW(fptr->widget));
        break;

      case WCTKW_BUTTON:
        wctk_button_destroy (WCTK_WIDGET_BUTTON(fptr->widget));
        break;
    }
    ptr = ptr->next;
    free (fptr);
  }
}

