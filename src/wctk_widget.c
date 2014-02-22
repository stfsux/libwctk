#include <stdlib.h>
#include "wctk/wctk.h"

/*-----------------------------------------------------------------*/
void
 wctk_widget_attach (pwctk_window_t parent, void *widget,
     uint32_t type)
{
  pwctk_widget_t new_widget = NULL;

  if (parent == NULL)
    return;

  if (type != WCTKW_LISTVIEW   &&
      type != WCTKW_BUTTON     &&
      type != WCTKW_STATICTEXT &&
      type != WCTKW_PROMPT)
    return;

  new_widget = calloc (1, sizeof(wctk_widget_t));
  if (new_widget == NULL)
    return;

  new_widget->widget = widget;
  new_widget->type = type;

  if (parent->widget_list == NULL)
  {
    parent->widget_list = new_widget;
    if (new_widget->type != WCTKW_STATICTEXT)
      parent->widget_focus = new_widget;
  }
  else
  {
    pwctk_widget_t ptr = parent->widget_list;
    while (ptr->next != NULL)
      ptr = ptr->next;
    if (parent->widget_focus == NULL)
    {
      if (new_widget->type != WCTKW_STATICTEXT)
        parent->widget_focus = new_widget;
    }
    ptr->next = new_widget;
    new_widget->prev = ptr;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_widget_event_translate_all (pwctk_window_t parent,
     pwctk_event_t event)
{
  pwctk_widget_t widget = NULL;

  if (parent == NULL ||
      event  == NULL)
    return;
  
  widget = parent->widget_list;
  
  while (widget != NULL)
  {
    switch (widget->type)
    {
      case WCTKW_LISTVIEW:
        /*
          wctk_listview_event_translate (
              WCTK_WIDGET_LISTVIEW(widget->widget),
              event
              );
              */
          break;

      case WCTKW_BUTTON:
          wctk_button_event_translate (
              WCTK_WIDGET_BUTTON(widget->widget),
              event
              );
          break;
    }
    widget = widget->next;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_widget_event_translate (pwctk_window_t parent,
     pwctk_event_t event)
{
  pwctk_widget_t widget = NULL;

  if (parent == NULL ||
      event  == NULL)
    return;
  
  widget = parent->widget_focus;

  if (widget == NULL)
    return;
  
  switch (widget->type)
  {
    case WCTKW_LISTVIEW:
        wctk_listview_event_translate (
            WCTK_WIDGET_LISTVIEW(widget->widget),
            event
            );
        break;

    case WCTKW_BUTTON:
        wctk_button_event_translate (
            WCTK_WIDGET_BUTTON(widget->widget),
            event
            );
        break;

    case WCTKW_PROMPT:
        wctk_prompt_event_translate (
            WCTK_WIDGET_PROMPT(widget->widget),
            event
            );
        break;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_widget_set_focus (pwctk_widget_t widget, uint8_t b)
{
  if (widget == NULL)
    return;

  switch (widget->type)
  {
    case WCTKW_LISTVIEW:
      wctk_listview_set_focus (
          WCTK_WIDGET_LISTVIEW(widget->widget), b
          );
      break;

    case WCTKW_BUTTON:
      wctk_button_set_focus (
          WCTK_WIDGET_BUTTON(widget->widget), b
          );
      break;

    case WCTKW_PROMPT:
      wctk_prompt_set_focus (
          WCTK_WIDGET_PROMPT(widget->widget), b
          );
      break;
  }
}

/*-----------------------------------------------------------------*/
uint8_t
 wctk_widget_focus_next (pwctk_window_t window)
{
  pwctk_widget_t widget = NULL;

  if (window == NULL)
    return 0;

  if (window->widget_focus == NULL)
    return 0;

  widget = window->widget_focus;

  wctk_widget_set_focus (widget, 0);

  widget = widget->next;

  while (widget != NULL)
  {
    if (widget->type != WCTKW_STATICTEXT)
    {
      window->widget_focus = widget;
      wctk_widget_set_focus (window->widget_focus, 1);
      return 1;
    }
    widget = widget->next;
  }
  return 0;
}

/*-----------------------------------------------------------------*/
void
 wctk_widget_focus_first (pwctk_window_t window)
{
  pwctk_widget_t widget = NULL;
  if (window == NULL)
    return;
  wctk_widget_set_focus (window->widget_focus, 0);
  widget = window->widget_list;
  window->widget_focus = NULL;
  while (widget != NULL)
  {
    if (widget->type != WCTKW_STATICTEXT)
    {
      window->widget_focus = widget;
      break;
    }
    widget = widget->next;
  }
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

      case WCTKW_LISTVIEW:
        if (WCTK_LISTVIEW_DRAWABLE(WCTK_WIDGET_LISTVIEW(widget->widget)))
        {
          wctk_listview_draw 
            (
              WCTK_WIDGET_LISTVIEW(widget->widget),
              WCTK_LISTVIEW_DRAW_WIDTH(WCTK_WIDGET_LISTVIEW(widget->widget)),
              WCTK_LISTVIEW_DRAW_HEIGHT(WCTK_WIDGET_LISTVIEW(widget->widget))
            );
        }
        break;

      case WCTKW_STATICTEXT:
        if (WCTK_STATICTEXT_DRAWABLE(WCTK_WIDGET_STATICTEXT(widget->widget)))
        {
          wctk_static_text_draw
            (
              WCTK_WIDGET_STATICTEXT(widget->widget),
              WCTK_STATICTEXT_DRAW_WIDTH (
                WCTK_WIDGET_STATICTEXT(widget->widget)
              ),
              WCTK_STATICTEXT_DRAW_HEIGHT (
                WCTK_WIDGET_STATICTEXT(widget->widget)
              )
            );
        }
        break;

      case WCTKW_PROMPT:
        if (WCTK_PROMPT_DRAWABLE(WCTK_WIDGET_PROMPT(widget->widget)))
        {
          wctk_prompt_draw
            (
              WCTK_WIDGET_PROMPT(widget->widget),
              WCTK_PROMPT_DRAW_WIDTH (
                WCTK_WIDGET_PROMPT(widget->widget)
              )
            );
        }
        break;
    }
    widget = widget->next;
  }
}

/*-----------------------------------------------------------------*/
/*
uint8_t
 wctk_widget_hit (pwctk_widget_t widget, int32_t x, int32_t y)
{
  uint8_t r = 0;

  if (widget == NULL)
    return 0;

  switch (widget->type)
  {
    case WCTKW_LISTVIEW:
      if (WCTK_LISTVIEW_HIT_TEST(WCTK_WIDGET_LISTVIEW(widget->widget)))
        r = 1;
      break;

    case WCTKW_BUTTON:
      if (WCTK_BUTTON_HIT_TEST(WCTK_WIDGET_BUTTON(widget->widget)))
        r = 1;
      break;
  }

  return r;
}
*/

/*-----------------------------------------------------------------*/
/*
pwctk_widget_t
 wctk_widget_hit_region (pwctk_window_t parent, int32_t x, int32_t y)
{
  pwctk_widget_t ptr = NULL;
  if (parent == NULL)
    return NULL;
  ptr = parent->widget_list;
  while (ptr != NULL)
  {
    if (wctk_widget_hit (ptr, x, y))
      return ptr;
    ptr = ptr->next;
  }
  return NULL;
}
*/

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
      case WCTKW_BUTTON:
        wctk_button_destroy (WCTK_WIDGET_BUTTON(fptr->widget));
        break;

      case WCTKW_LISTVIEW:
        wctk_listview_destroy (WCTK_WIDGET_LISTVIEW(fptr->widget));
        break;

      case WCTKW_STATICTEXT:
        wctk_static_text_destroy (WCTK_WIDGET_STATICTEXT(fptr->widget));
        break;

      case WCTKW_PROMPT:
        wctk_prompt_destroy (WCTK_WIDGET_PROMPT(fptr->widget));
        break;
    }
    ptr = ptr->next;
    free (fptr);
    fptr = NULL;
  }
  parent->widget_list = NULL;
}

