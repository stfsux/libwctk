
#include <stdio.h>
#include <stdlib.h>
#include <wctk/wctk.h>
#include <sys/time.h>
#include <math.h>

#define MAX_WINDOW  10

int
 main (int argc, char* const argv[])
{
  pwctk_window_t window[MAX_WINDOW];
  wctk_event_t ev;
  unsigned char run = 1;
  unsigned int i;
  struct timeval c, s, tv_fps;
  float x = 0.0f, y = 0.0f;
  unsigned int rot = 1;
  unsigned int fps = 0, frame = 0;

  (void)argc;
  (void)argv;
  wctk_init ();
  wctk_setup_colors ();
  for (i = 0; i < MAX_WINDOW; i++)
  {
    char tmp[MAX_WINDOW];
    sprintf (tmp, "Window %u!", i);
    window[i] = wctk_window_create (tmp, 1+i*2, 1+i*2, 20, 10, WCTK_WINDOW, WCTKC_WHITE_BLUE, WCTKC_WHITE_RED, WCTKC_WHITE_GREEN, i+1);
  }
  gettimeofday (&s, NULL);
  gettimeofday (&tv_fps, NULL);
  while (run)
  {
    wctk_event_get (&ev);
    wctk_event_translate (&ev);
    switch (ev.event_type)
    {
      case WCTK_EVENT_KEY:
        if (ev.key == 'q')
          run = 0;
        else if (ev.key == ' ')
          rot = rot ^ 1;
        break;
    }
    gettimeofday (&c, NULL);
    if ((double)(c.tv_sec+c.tv_usec*0.000001)-
        (double)(s.tv_sec+s.tv_usec*0.000001) > 0.016f)
    {
      for (i = 0; i < MAX_WINDOW; i++)
      {
        x =  (WCTK_SCREEN_WIDTH-20)/2+((WCTK_SCREEN_WIDTH-50)/2)*sin(i*3.14f/10.0f+(c.tv_sec+c.tv_usec*0.000001)*6.28f*0.1f);
        y =  (WCTK_SCREEN_HEIGHT-10)/2+((WCTK_SCREEN_HEIGHT-10)/2)*sin(i*3.28f/20.0f+(c.tv_sec+c.tv_usec*0.000001)*6.28f*0.1f);
        if (rot == 1)
        wctk_window_move (window[i], x, y);
      }
      wctk_draw_rect_fill (0, 0, WCTK_SCREEN_WIDTH+1, WCTK_SCREEN_HEIGHT+1, ACS_CKBOARD|COLOR_PAIR(WCTKC_BLUE_WHITE));
      mvprintw (0,0, "%3d fps", fps);
      wctk_refresh ();
      gettimeofday (&s, NULL);
      frame++;
    }
    if ((double)(c.tv_sec+c.tv_usec*0.000001)-
        (double)(tv_fps.tv_sec+tv_fps.tv_usec*0.000001) > 1.0f)
    {
      fps = frame;
      frame = 0;
      gettimeofday (&tv_fps, NULL);
    }
    //wctk_draw_rect_fill (0, 0, WCTK_SCREEN_WIDTH+1, WCTK_SCREEN_HEIGHT+1, ' '|COLOR_PAIR(WCTKC_BLUE_WHITE));
    //wctk_refresh ();
  }
  for (i = 0; i < MAX_WINDOW; i++)
    wctk_window_destroy (window[i]);
  wctk_quit ();
  return 0;
}


