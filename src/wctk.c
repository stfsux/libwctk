#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>
#include "wctk/wctk.h"

pwctk_stack_t stack = NULL;

/*-----------------------------------------------------------------*/
void
 wctk_init (void)
{
  setlocale(LC_ALL, "");
  initscr ();
  cbreak ();
  noecho ();
  curs_set (0);
  nonl ();
  raw ();
  keypad (stdscr, TRUE);
  mousemask (ALL_MOUSE_EVENTS|REPORT_MOUSE_POSITION, NULL);
  mouseinterval (1);
  timeout (0);
  wctk_mouse_init ();
}

/*-----------------------------------------------------------------*/
void
 wctk_setup_colors (void)
{
  if (has_colors ())
  {
    unsigned short fg, bg;
    start_color ();
    for (bg = 0; bg < 8; bg++)
    {
      for (fg = 0; fg < 8; fg++)
      {
        init_pair (bg*8+fg+1, fg, bg);
      }
    }
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_event_get (pwctk_event_t event)
{
  int data = 0;
  memset (event, 0x00, sizeof(wctk_event_t));
  event->window = wctk_zorder_get_first_window ();
  wctk_window_set_focus (event->window, 1);
  data = getch ();
  if (data == ERR)
    return;
  switch (data)
  {
    case KEY_MOUSE:
      wctk_mouse_event (event);
      break;

    default:
      event->event_type = WCTK_EVENT_KEY;
      event->key = data;
      break;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_event_translate (pwctk_event_t event)
{
  switch (event->event_type)
  {
    case WCTK_EVENT_MOUSE:
      if (wctk_mouse_released (event))
      {
        pwctk_zorder_t zwin = wctk_zorder_get (event->mevent.x, event->mevent.y);
        if (zwin != NULL)
        {
          if (zwin != wctk_zorder_get_first ())
          {
            pwctk_window_t win = zwin->window;
            wctk_window_set_focus (wctk_zorder_get_first_window (), 0);
            wctk_zorder_pop_target (zwin);
            wctk_zorder_push (win);
            event->window = wctk_zorder_get_first_window ();
          }
        }
      }
      else
      {
        /* Transmit event to the widget. */
      }
      break;

    case WCTK_EVENT_DRAG:
      wctk_window_move (event->window, wctk_mouse_getx()-wctk_mouse_getsx(),
          wctk_mouse_gety()-wctk_mouse_getsy());
      break;

    case WCTK_EVENT_RESIZE:
      if (wctk_mouse_getx() > event->window->xpos &&
          wctk_mouse_gety() > event->window->ypos)
      {
        wctk_window_resize (event->window,
            wctk_mouse_getx()-event->window->xpos+1,
            wctk_mouse_gety()-event->window->ypos+1);
      }
      break;

    case WCTK_EVENT_CLOSE:
      if (event->window != NULL)
      {
        wctk_window_set_focus (event->window, 0);
        wctk_zorder_pop ();
        event->window = wctk_zorder_get_first_window ();
      }
      break;

    case WCTK_EVENT_KEY:
      switch (event->key)
      {
        case '\t':
          if (!wctk_widget_focus_next (event->window) &&
              event->window != NULL)
          {
            pwctk_window_t win = wctk_zorder_get_first_window ();
            if (win != NULL)
            {
              win->widget_focus = win->widget_list;
              wctk_window_set_focus (win, 0);
              wctk_zorder_switch_next_window ();
            }
          }
          break;
      }
      /* Tansmit event to the widget. */
      wctk_widget_event_translate (event->window, event);
      break;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_refresh (void)
{
  pwctk_zorder_t ptr = NULL;
  ptr = wctk_zorder_get_last ();
  while (ptr != NULL)
  {
    wctk_window_draw (ptr->window);
    ptr = wctk_zorder_get_prev (ptr);
  }
  wctk_draw_cursor (wctk_mouse_getx(), wctk_mouse_gety());
  doupdate ();
}

/*-----------------------------------------------------------------*/
void
 wctk_quit (void)
{
  wctk_zorder_purge ();
  wctk_mouse_close ();
  endwin ();
}

