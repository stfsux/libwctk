
#include <stdlib.h>
#include <ncurses.h>
#include <wctk/wctk.h>

#define WINDOW_UID_MAIN 1
#define PROMPT_UID1     2

int 
 main (int argc, char* const argv[])
{
  pwctk_window_t window = NULL;
  pwctk_prompt_t p = NULL;
  wctk_event_t ev;
  unsigned char run = 1;
  (void)argc;
  (void)argv;

  wctk_init ();
  wctk_setup_colors ();

  window = wctk_window_create ("Loader configuration", 3, 3, 30, 15,
      WCTK_WINDOW|WCTK_WINDOW_NORESIZE|WCTK_WINDOW_NOMAX|WCTK_WINDOW_NOMIN,
      WINDOW_UID_MAIN);
  p = wctk_prompt_create (2, 2, 10, 1, WCTK_PROMPT_ALPHA, window, PROMPT_UID1);

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

    }
    wctk_draw_rect_fill (0, 0, WCTK_SCREEN_WIDTH+1, WCTK_SCREEN_HEIGHT+1,
        ACS_CKBOARD|COLOR_PAIR(WCTKC_BLUE_WHITE));
    wctk_refresh ();
  }
  wctk_window_destroy (window);
  wctk_quit ();
  return 0;
}


