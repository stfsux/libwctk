#ifndef _WCTK_WINDOW_H_
#define _WCTK_WINDOW_H_

/* List of widget(s). */
typedef struct _wctk_widget
{
  void *widget;
  uint32_t type;
#define WCTKW_BUTTON     1
#define WCTKW_LISTVIEW   2
#define WCTKW_STATICTEXT 3
#define WCTKW_PROMPT     4
  struct _wctk_widget *next;
  struct _wctk_widget *prev;
}wctk_widget_t, *pwctk_widget_t;

typedef struct _wctk_window_colors
{
  short default_cpair;
  short titlebar_cpair;
  short focused_cpair;
}wctk_window_colors_t, *pwctk_window_colors_t;

typedef struct _wctk_window
{
  char *title;
  int32_t xpos;
  int32_t ypos;
  int32_t xoffset;
  int32_t yoffset;
  int32_t width;
  int32_t height;
  uint32_t flags;
#define WCTK_WINDOW               0U
#define WCTK_WINDOW_NOMAX         (1U<<0)
#define WCTK_WINDOW_NOMIN         (1U<<1)
#define WCTK_WINDOW_TOP           (1U<<2)
#define WCTK_WINDOW_NORESIZE      (1U<<3)
#define WCTK_WINDOW_NOSHADOW      (1U<<4)
#define WCTK_WINDOW_TITLEBAR_LINE (1U<<5)
  uint32_t state;
#define WCTK_WINDOW_STATE_FOCUS     (1U<<0)
#define WCTK_WINDOW_STATE_DISABLE   (1U<<1)
#define WCTK_WINDOW_STATE_MAXIMIZE  (1U<<2)
  wctk_window_colors_t colors;
  pwctk_widget_t widget_list;
  pwctk_widget_t widget_focus;
  uint32_t uid;
}wctk_window_t, *pwctk_window_t;

#define wctk_window_destroy(w) wctk_window_destroy_safe(&w)

/*-----------------------------------------------------------------*/
pwctk_window_t wctk_window_create (char* title, int32_t x, int32_t y,
    int32_t w, int32_t h, uint8_t flags, uint32_t uid);
void wctk_window_set_colors (pwctk_window_t window,
    pwctk_window_colors_t colors);
void wctk_window_draw (pwctk_window_t window);
void wctk_window_move (pwctk_window_t window, int32_t x, int32_t y);
void wctk_window_resize (pwctk_window_t window, int32_t w, int32_t h);
void wctk_window_focus_set (pwctk_window_t window, uint8_t b);
uint32_t wctk_window_state_get (pwctk_window_t window);
void wctk_window_state_set (pwctk_window_t window, uint32_t state);
void wctk_window_state_clr (pwctk_window_t window, uint32_t state);
uint8_t wctk_window_region_titlebar (pwctk_window_t window, int32_t x,
    int32_t y);
uint8_t wctk_window_region_bresize (pwctk_window_t window, int32_t x,
    int32_t y);
uint8_t wctk_window_region_bclose (pwctk_window_t window, int32_t x,
    int32_t y);
uint8_t wctk_window_region_bmin (pwctk_window_t window, int32_t x,
     int32_t y);
uint8_t wctk_window_region_bmax (pwctk_window_t window, int32_t x,
     int32_t y);
int32_t wctk_window_width_get (pwctk_window_t window);
int32_t wctk_window_height_get (pwctk_window_t window);
void wctk_window_destroy_safe (pwctk_window_t *window);
#define wctk_window_destroy(w) wctk_window_destroy_safe(&w)

#define wwin_t                      wctk_window_t
#define pwwin_t                     pwctk_window_t
#define wwin_colors_t               wctk_window_colors_t
#define pwwin_colors_t              pwctk_window_colors_t

#define wwin_create(t,x,y,w,h,f,u)  wctk_window_create(t,x,y,w,h,f,u)
#define wwin_set_colors(w,c)        wctk_window_set_colors(t,c)
#define wwin_draw(w)                wctk_window_draw(w)
#define wwin_move(w,x,y)            wctk_window_move(w,x,y)
#define wwin_resize(w,wd,h)         wctk_window_resize(w,wd,h)
#define wwin_focus_set(w,b)         wctk_window_focus_set(w,b)
#define wwin_region_titlebar(w,x,y) wctk_window_region_titlebar(w,x,y)
#define wwin_region_bclose(w,x,y)   wctk_window_region_bclose(w,x,y)
#define wwin_destroy(w)             wctk_window_destroy(w)
#endif

