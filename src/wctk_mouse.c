#include <stdlib.h>
#include <stdio.h>
#include "wctk/wctk.h"

int32_t _g_wctk_xmouse = 0;
int32_t _g_wctk_ymouse = 0;
int32_t _g_wctk_click_sx = 0;
int32_t _g_wctk_click_sy = 0;
uint8_t _g_wctk_drag    = 0;
uint8_t _g_wctk_resize = 0;
uint8_t _g_wctk_mouse_enable = 0;

/*-----------------------------------------------------------------*/
void
 wctk_mouse_init (void)
{
  mousemask (ALL_MOUSE_EVENTS|REPORT_MOUSE_POSITION, NULL);
  mouseinterval (1);
  fprintf (stdout, "\E[?1001s\E[?1003h");
  fflush (stdout);
  wctk_mouse_enable ();
}

/*-----------------------------------------------------------------*/
void
 wctk_mouse_enable (void)
{
  _g_wctk_mouse_enable = 1;
}

/*-----------------------------------------------------------------*/
void
 wctk_mouse_disable (void)
{
  _g_wctk_mouse_enable = 0;
}

/*-----------------------------------------------------------------*/
uint8_t
 wctk_has_mouse (void)
{
  return _g_wctk_mouse_enable;
}

/*-----------------------------------------------------------------*/
void
 wctk_mouse_drag_disable (void)
{
  _g_wctk_drag = 0;
}

/*-----------------------------------------------------------------*/
void
 wctk_mouse_resize_disable (void)
{
  _g_wctk_resize = 0;
}

/*-----------------------------------------------------------------*/
void
 wctk_mouse_event (pwctk_event_t event)
{
  if (getmouse (&event->mevent) == OK)
  {
    _g_wctk_xmouse = event->mevent.x;
    _g_wctk_ymouse = event->mevent.y;
    
    if (event->mevent.bstate&BUTTON1_PRESSED)
    {
      if (event->window != NULL)
      {
        if (wctk_window_region_titlebar (event->window,
              _g_wctk_xmouse, _g_wctk_ymouse) &&
            !(wctk_window_get_state (event->window)&WCTK_WINDOW_STATE_MAXIMIZE))
        {
          _g_wctk_drag = 1;
          _g_wctk_click_sx = _g_wctk_xmouse - event->window->xpos;
          _g_wctk_click_sy = _g_wctk_ymouse - event->window->ypos;
        }
        if (wctk_window_region_bresize (event->window,
              _g_wctk_xmouse, _g_wctk_ymouse))
        {
          _g_wctk_resize = 1;
        }
      }
    }
    if (event->mevent.bstate&BUTTON1_RELEASED)
    {
      _g_wctk_drag = 0;
      _g_wctk_resize = 0;

      if (event->window != NULL)
      {
        if (wctk_window_region_bclose (event->window,
              _g_wctk_xmouse, _g_wctk_ymouse))
        {
          event->type = WCTK_EVENT_CLOSE;
        }
        else if (wctk_window_region_bmax (event->window,
              _g_wctk_xmouse, _g_wctk_ymouse))
        {
          event->type = WCTK_EVENT_MAXIMIZE;
        }
        else if (wctk_window_region_bmin (event->window,
              _g_wctk_xmouse, _g_wctk_ymouse))
        {
          event->type = WCTK_EVENT_MINIMIZE;
        }
      }
    }
    
    if (_g_wctk_drag)
      event->type = WCTK_EVENT_DRAG;
    else if (_g_wctk_resize)
      event->type = WCTK_EVENT_RESIZE;
    else if (event->type == 0)
      event->type = WCTK_EVENT_MOUSE;
  }
}

/*-----------------------------------------------------------------*/
uint8_t
 wctk_mouse_pressed (pwctk_event_t event)
{
  return (event->mevent.bstate&BUTTON1_PRESSED)?1:0;
}

/*-----------------------------------------------------------------*/
uint8_t
 wctk_mouse_released (pwctk_event_t event)
{
  return (event->mevent.bstate&BUTTON1_RELEASED)?1:0;
}

/*-----------------------------------------------------------------*/
int32_t
 wctk_mouse_getx (void)
{
  return _g_wctk_xmouse;
}

/*-----------------------------------------------------------------*/
int32_t
 wctk_mouse_gety (void)
{
  return _g_wctk_ymouse;
}

/*-----------------------------------------------------------------*/
int32_t
 wctk_mouse_getsx (void)
{
  return _g_wctk_click_sx;
}

/*-----------------------------------------------------------------*/
int32_t
 wctk_mouse_getsy (void)
{
  return _g_wctk_click_sy;
}

/*-----------------------------------------------------------------*/
void
 wctk_mouse_close (void)
{
  fprintf (stdout, "\E[?1003l\E[?1001h");
  fflush (stdout);
}
