#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>
#include "wctk/wctk.h"

/*-----------------------------------------------------------------*/
void
 wctk_init (void)
{
  /* setlocale(LC_ALL, "");*/
  initscr ();
  cbreak ();
  noecho ();
  curs_set (0);
  raw (); 
  nonl ();
  keypad (stdscr, TRUE);
  timeout (250);
  /* wctk_mouse_init (); */
}

/*-----------------------------------------------------------------*/
void
 wctk_setup_colors (void)
{
  if (has_colors ())
  {
    signed short fg, bg;
    start_color ();
    use_default_colors ();
    for (bg = 0; bg < 8; bg++)
    {
      for (fg = 0; fg < 8; fg++)
      {
        init_pair (bg*8+fg+(signed short)1, fg, bg);
      }
    }
    for (fg = 0; fg < 8; fg++)
      init_pair (WCTKC_BLACK_DEFAULT+fg, fg, -1);
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_event_get (pwctk_event_t event)
{
  int key = 0;
  if (event->type != WCTK_EVENT_DRAG &&
      event->type != WCTK_EVENT_RESIZE)
    memset (event, 0x00, sizeof(wctk_event_t));
  event->window = wctk_zorder_get_first_window ();
  wctk_window_set_focus (event->window, 1);
  key = wgetch (stdscr);
  switch (key)
  {
    /*
    case KEY_MOUSE:
      wctk_mouse_event (event);
      break;
      */

    case KEY_F(10):
      if (event->type != WCTK_EVENT_DRAG)
        event->type = WCTK_EVENT_DRAG;
      else
        event->type = WCTK_EVENT_NONE;
      event->data = key;
      break;

    case KEY_F(11):
      if (event->type != WCTK_EVENT_RESIZE)
        event->type = WCTK_EVENT_RESIZE;
      else
        event->type = WCTK_EVENT_NONE;
      event->data = key;
      break;

    case KEY_F(12):
      event->type = WCTK_EVENT_MAXIMIZE;
      break;

    default:
      if (event->type != WCTK_EVENT_DRAG &&
          event->type != WCTK_EVENT_RESIZE)
      {
        event->type = WCTK_EVENT_KEY;
      }
      else
      {
        if (key == KEY_RETURN)
          event->type = WCTK_EVENT_NONE;
      }
      event->data = key;
      break;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_event_translate (pwctk_event_t event)
{
  switch (event->type)
  {

    /*
    case WCTK_EVENT_MOUSE:
      if (event->window != NULL)
      {
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
      }
      wctk_widget_event_translate_all (event->window, event);
      break;
      */

    case WCTK_EVENT_DRAG:
      /*
      wctk_window_move (event->window, wctk_mouse_getx()-wctk_mouse_getsx(),
          wctk_mouse_gety()-wctk_mouse_getsy());
          */
      switch (event->data)
      {
        case KEY_LEFT:
          wctk_window_move (event->window, event->window->xpos - 1, 
              event->window->ypos);
          break;

        case KEY_RIGHT:
          wctk_window_move (event->window, event->window->xpos + 1, 
              event->window->ypos);
          break;

        case KEY_UP:
          wctk_window_move (event->window, event->window->xpos, 
              event->window->ypos - 1);
          break;

        case KEY_DOWN:
          wctk_window_move (event->window, event->window->xpos, 
              event->window->ypos + 1);
          break;
      }
      break;

    case WCTK_EVENT_RESIZE:
      /*
      if (wctk_mouse_getx() > event->window->xpos &&
          wctk_mouse_gety() > event->window->ypos)
      {
        wctk_window_resize (event->window,
            wctk_mouse_getx()-event->window->xpos+1,
            wctk_mouse_gety()-event->window->ypos+1);
      }
      */
      switch (event->data)
      {
        case KEY_LEFT:
          wctk_window_resize (event->window,
              event->window->width - 1,
              event->window->height);
          break;

        case KEY_RIGHT:
          wctk_window_resize (event->window,
              event->window->width + 1,
              event->window->height);
          break;

        case KEY_UP:
          wctk_window_resize (event->window,
              event->window->width,
              event->window->height - 1);
          break;

        case KEY_DOWN:
          wctk_window_resize (event->window,
              event->window->width,
              event->window->height + 1);
          break;
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

    case WCTK_EVENT_MAXIMIZE:
      if (event->window != NULL)
      {
        if (!(wctk_window_get_state(event->window)&WCTK_WINDOW_STATE_MAXIMIZE))
        {
          wctk_window_resize (event->window, getmaxx(stdscr), getmaxy(stdscr));
          wctk_window_move (event->window, 0, 0);
          wctk_window_set_state (event->window, WCTK_WINDOW_STATE_MAXIMIZE);
        }
        else
        {
          wctk_window_resize (event->window, 40, 10);
          wctk_window_move (event->window, 20, 5);
          wctk_window_clr_state (event->window, WCTK_WINDOW_STATE_MAXIMIZE);
        }
      }
      break;

    case WCTK_EVENT_KEY:
      switch (event->data)
      {
        case '\t':
          if (event->window != NULL)
          {
            if (!wctk_widget_focus_next (event->window))
            {
              pwctk_window_t win = wctk_zorder_get_first_window ();
              if (win != NULL)
              {
                wctk_widget_focus_first (win);
                wctk_window_set_focus (win, 0);
                wctk_zorder_switch_next_window ();
              }
            }
          }
          break;
      }
      /* Tansmit event to the focused widget. */
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
  /*
  wctk_draw_cursor (wctk_mouse_getx(), wctk_mouse_gety());
  */
  doupdate ();
}

/*-----------------------------------------------------------------*/
void
 wctk_quit (void)
{
  wctk_zorder_purge ();
  /*
  wctk_mouse_close ();
  */
  endwin ();
}

