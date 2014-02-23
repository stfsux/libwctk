
#include <stdlib.h>
#include <ncurses.h>
#include <wctk/wctk.h>

#define WINDOW_UID_MAIN 1
#define LISTVIEW_INTRO  2

int 
 main (int argc, char* const argv[])
{
  pwctk_window_t window = NULL;
  pwctk_listview_t lv = NULL;
  wctk_event_t ev;
  unsigned char run = 1;
  unsigned int i;
  (void)argc;
  (void)argv;

  wctk_init ();
  wctk_setup_colors ();

  window = wctk_window_create ("Log viewer", 3, 3, 30, 15, WCTK_WINDOW,
      WINDOW_UID_MAIN);
  lv = wctk_listview_create (0, 0, 28, 10, WCTK_LISTVIEW_AUTOSCROLL|WCTK_LISTVIEW_SCROLLBAR, window, LISTVIEW_INTRO);
  for (i = 0; i < 100; i++)
  {
    char tmp[256];
    sprintf (tmp, "0x%08X hello world!", 0x08040000+i);
    wctk_listview_item_add (lv, tmp);
  }

  while (run)
  {
    wctk_event_get (&ev);
    wctk_event_translate (&ev);
    switch (ev.type)
    {
      case WCTK_EVENT_KEY:
        switch (ev.data)
        {
          case 'Q':
          case 'q':
            run = 0;
            break;
        }
        break;

      case WCTK_EVENT_RESIZE:
        wctk_listview_resize (lv, ev.window->width-2, ev.window->height-2);
        break;

      case WCTK_EVENT_MAXIMIZE:
        wctk_listview_resize (lv, ev.window->width-2, ev.window->height-2);
        break;
    }
    wctk_draw_rect_fill (0, 0, WCTK_SCREEN_WIDTH+1, WCTK_SCREEN_HEIGHT+1,
        ACS_CKBOARD|COLOR_PAIR(WCTKC_BLUE_WHITE));
    wctk_refresh ();
  }
  wctk_window_destroy (window);
  wctk_quit ();
  return 0;
}


