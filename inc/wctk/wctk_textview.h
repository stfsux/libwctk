
#ifndef _WCTK_TEXTVIEW_H_
#define _WCTK_TEXTVIEW_H_

typedef struct _wctk_textview_colors
{
  short default_cpair;
  short default_hline_cpair;
  short default_cursor_cpair;
  short focus_hline_cpair;
  short focus_cursor_cpair;
}wctk_textview_colors_t, *pwctk_textview_colors_t;

typedef struct _wctk_textview
{
  pwctk_astr_t text;
  uint start;
  sint xpos;
  sint ypos;
  sint width;
  sint height;
  uchar flags;
#define WCTK_TEXTVIEW_CURSOR        (1<<0)
#define WCTK_TEXTVIEW_HILINE        (1<<1)
#define WCTK_TEXTVIEW_NUMBER        (1<<2)
  uchar state;
#define WCTK_TEXTVIEW_STATE_FOCUS   (1<<0)
  pwctk_window_t parent;
  uint xcursor;
  uint ycursor;
  wctk_textview_colors_t colors;
  uint uid;
}wctk_textview_t, *pwctk_textview_t;

#define WCTK_TEXTVIEW_DRAWABLE(t)         ((t->xpos+2 < t->parent->width) && \
                                           (t->ypos+2 < t->parent->height))
#define WCTK_TEXTVIEW_DRAWABLE_WIDTH(t)   ((t->xpos+t->width+1) < (t->parent->width))
#define WCTK_TEXTVIEW_DRAWABLE_HEIGHT(t)  ((t->ypos+t->height+1) < (t->parent->height))
#define WCTK_TEXTVIEW_DRAW_WIDTH(t)       ((WCTK_TEXTVIEW_DRAWABLE_WIDTH(t)) ? \
                                              t->width:t->parent->width-1-t->xpos)
#define WCTK_TEXTVIEW_DRAW_HEIGHT(t)      ((WCTK_TEXTVIEW_DRAWABLE_HEIGHT(t)) ? \
                                              t->height:t->parent->height-1-t->ypos)


pwctk_textview_t wctk_textview_create (char *txt, sint x, sint y,
    sint w, sint h, uchar flags, pwctk_window_t parent, uint uid);
void wctk_textview_draw (pwctk_textview_t textview, uint draw_area_width,
    uint draw_area_height);
size_t wctk_textview_get_nchar (pwctk_textview_t textview, uint nline);
void wctk_textview_event_translate (pwctk_textview_t textview, pwctk_event_t event);
void wctk_textview_scroll_up (pwctk_textview_t textview, uint nlines);
void wctk_textview_scroll_down (pwctk_textview_t textview, uint nlines);
void wctk_textview_resize (pwctk_textview_t textview, uint w, uint h);
void wctk_textview_set_focus (pwctk_textview_t textview, uchar b);
void wctk_textview_set_colors (pwctk_textview_t textview, pwctk_textview_colors_t colors);
void wctk_textview_destroy (pwctk_textview_t textview);

#define wtv_t                       wctk_textview_t
#define pwtv_t                      pwctk_textview_t
#define wtv_create(t,x,y,w,h,f,p,u) wctk_textview_create(t,x,y,w,h,f,p,u)
#define wtv_draw(t,w,h)             wctk_textview_draw(t,w,h)
#define wtv_get_nchar(t,l)          wctk_textview_get_nchar(t,l)
#define wtv_event_translate(t,e)    wctk_textview_event_translate(t,e)
#define wtv_scroll_up(t,l)          wctk_textview_scroll_up(t,l)
#define wtv_scroll_down(t,l)        wctk_textview_scroll_down(t,l)
#define wtv_resize(t,w,h)           wctk_textview_resize(t,w,h)
#define wtv_set_focus(t,b)          wctk_textview_set_focus(t,b)
#define wtv_set_colors(t,c)         wctk_textview_set_colors(t,c)
#define wtv_destroy(t)              wctk_textview_destroy(t)


#endif

