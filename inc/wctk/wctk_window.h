#ifndef _WCTK_WINDOW_H_
#define _WCTK_WINDOW_H_

/* List of widget(s). */
typedef struct _wctk_widget
{
  void *widget;
  uint type;
#define WCTKW_BUTTON    1
#define WCTKW_TEXTVIEW  2
  struct _wctk_widget *next;
  struct _wctk_widget *prev;
}wctk_widget_t, *pwctk_widget_t;

typedef struct _wctk_window
{
  char *title;
  sint xpos;
  sint ypos;
  sint xoffset;
  sint yoffset;
  sint width;
  sint height;
  sint flags;
#define WCTK_WINDOW           0
#define WCTK_WINDOW_NOCLOSE  (1<<0)
#define WCTK_WINDOW_NOMAX    (1<<1)
#define WCTK_WINDOW_NOMIN    (1<<2)
  uchar state;
#define WCTK_WINDOW_STATE_FOCUS   (1<<0)
#define WCTK_WINDOW_STATE_DISABLE (1<<1)
  short default_cpair;
  short titlebar_cpair;
  short focused_cpair;
  pwctk_widget_t widget_list;
  pwctk_widget_t widget_focus;
  uint uid;
}wctk_window_t, *pwctk_window_t;

/*-----------------------------------------------------------------*/
pwctk_window_t wctk_window_create (char* title, sint x, sint y,
    sint w, sint h, uchar flags, short default_cpair,
    short titlebar_cpair, short focused_cpair, uint uid);
void wctk_window_draw (pwctk_window_t window);
void wctk_window_move (pwctk_window_t window, sint x, sint y);
void wctk_window_resize (pwctk_window_t window, sint w, sint h);
void wctk_window_set_focus (pwctk_window_t window, uchar b);
uchar wctk_window_region_titlebar (pwctk_window_t window, sint x,
    sint y);
uchar wctk_window_region_bresize (pwctk_window_t window, sint x,
    sint y);
uchar wctk_window_region_bclose (pwctk_window_t window, sint x,
    sint y);
void wctk_window_destroy (pwctk_window_t window);

#endif

