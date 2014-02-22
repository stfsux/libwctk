
#ifndef _WCTK_BUTTON_H_
#define _WCTK_BUTTON_H_

typedef struct _wctk_button_colors
{
  short default_cpair;
  short focus_cpair;
  short press_cpair;
}wctk_button_colors_t, *pwctk_button_colors_t;

typedef struct _wctk_button
{
  char *name;
  int32_t xpos;
  int32_t ypos;
  int32_t width;
  int32_t height;
  uint8_t flags;
  uint8_t state;
#define WCTK_BUTTON_STATE_FOCUS   (1<<0)
#define WCTK_BUTTON_STATE_PRESS   (1<<1)
  wctk_button_colors_t colors;
  pwctk_window_t parent;
  uint8_t reset;
  uint8_t counter;
  uint32_t uid;
}wctk_button_t, *pwctk_button_t;

#define WCTK_BUTTON_DRAWABLE(b)         ((b->xpos+2 < b->parent->width) &&\
                                         (b->ypos+2 < b->parent->height))
#define WCTK_BUTTON_DRAWABLE_WIDTH(b)   ((b->xpos+b->width+1) < (b->parent->width))
#define WCTK_BUTTON_DRAWABLE_HEIGHT(b)  ((b->ypos+b->height+1) < (b->parent->height))
#define WCTK_BUTTON_DRAW_WIDTH(b)       ((WCTK_BUTTON_DRAWABLE_WIDTH(b)) ? \
                                            b->width:b->parent->width-2-b->xpos)
#define WCTK_BUTTON_DRAW_HEIGHT(b)      ((WCTK_BUTTON_DRAWABLE_HEIGHT(b)) ? \
                                            b->height:b->parent->height-2-b->ypos)
#define WCTK_BUTTON_HIT_TESTX(b,x)      ((x >= b->xpos)&&(x <= b->xpos+b->width))
#define WCTK_BUTTON_HIT_TESTY(b,y)      ((y >= b->ypos)&&(y <= b->ypos+b->height))
#define WCTK_BUTTON_HIT_TEST(b,x,y)     (WCTK_BUTTON_HIT_TESTX(b,x) &&\
                                           WCTK_BUTTON_HIT_TESTY(b,y))

pwctk_button_t wctk_button_create (char *name, int32_t x, int32_t y, int32_t w, int32_t h,
     uint8_t flags, pwctk_window_t parent, uint32_t uid);
void wctk_button_draw (pwctk_button_t btn, uint32_t draw_area_width, uint32_t draw_area_height);
void wctk_button_event_translate (pwctk_button_t btn, pwctk_event_t event);
void wctk_button_set_state (pwctk_button_t btn, uint8_t b);
void wctk_button_set_focus (pwctk_button_t btn, uint8_t b);
void wctk_button_move (pwctk_button_t btn, int32_t x, int32_t y);
void wctk_button_resize (pwctk_button_t btn, int32_t w, int32_t h);
void wctk_button_destroy (pwctk_button_t btn);

#define wbtn_t                      wctk_button_t
#define pwbtn_t                     pwctk_button_t
#define wbtn_create(n,x,y,w,h,f,p)  wctk_button_create(n,x,y,w,h,f,p)
#define wbtn_draw(b,w,h)            wctk_button_draw(b,w,h)
#define wbtn_set_state(b,bl)        wctk_button_set_state(b,bl)
#define wbtn_set_focus(b,bl)        wctk_button_set_focus(b,bl)
#define wbtn_move(b,x,y)            wctk_button_move(b,x,y)
#define wbtn_resize(b,w,h)          wctk_button_resize(b,w,h)
#define wbtn_destroy(b)             wctk_button_destroy(b)

#endif

