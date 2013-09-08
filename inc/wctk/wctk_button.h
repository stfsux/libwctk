
#ifndef _WCTK_BUTTON_H_
#define _WCTK_BUTTON_H_

typedef struct _wctk_button_colors
{
  short default_cpair;
  short focus_cpair;
  short clicked_cpair;
}wctk_button_colors_t, *pwctk_button_colors_t;

typedef struct _wctk_button
{
  char *name;
  sint xpos;
  sint ypos;
  sint width;
  sint height;
  uchar flags;
  uchar state;
#define WCTK_BUTTON_STATE_FOCUS   (1<<0)
#define WCTK_BUTTON_STATE_CLICK   (1<<1)
  wctk_button_colors_t colors;
  pwctk_window_t parent;
}wctk_button_t, *pwctk_button_t;

#define WCTK_BUTTON_DRAWABLE(b)         ((b->xpos+2 < b->parent->width) &&\
                                         (b->ypos+2 < b->parent->height))
#define WCTK_BUTTON_DRAWABLE_WIDTH(b)   ((b->xpos+b->width+1) < (b->parent->width))
#define WCTK_BUTTON_DRAWABLE_HEIGHT(b)  ((b->ypos+b->height+1) < (b->parent->height))
#define WCTK_BUTTON_DRAW_WIDTH(b)       ((WCTK_BUTTON_DRAWABLE_WIDTH(b)) ? \
                                            b->width:b->parent->width-2-b->xpos)
#define WCTK_BUTTON_DRAW_HEIGHT(b)      ((WCTK_BUTTON_DRAWABLE_HEIGHT(b)) ? \
                                            b->height:b->parent->height-2-b->ypos)

pwctk_button_t wctk_button_create (char *name, sint x, sint y, sint w, sint h,
     uchar flags, pwctk_window_t parent);
void wctk_button_draw (pwctk_button_t btn, uint draw_area_width, uint draw_area_height);
void wctk_button_set_focus (pwctk_button_t btn, uchar b);
void wctk_button_move (pwctk_button_t btn, sint x, sint y);
void wctk_button_destroy (pwctk_button_t btn);

#define wbtn_t                      wctk_button_t
#define pwbtn_t                     pwctk_button_t
#define wbtn_create(n,x,y,w,h,f,p)  wctk_button_create(n,x,y,w,h,f,p)
#define wbtn_draw(b,w,h)            wctk_button_draw(b,w,h)
#define wbtn_set_focus(b,bl)        wctk_button_set_focus(b,bl)
#define wbtn_move(b,x,y)            wctk_button_move(b,x,y)
#define wbtn_destroy(b)             wctk_button_destroy(b)

#endif

