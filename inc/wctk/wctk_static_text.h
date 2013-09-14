
#ifndef _WCTK_STATIC_TEXT_H_
#define _WCTK_STATIC_TEXT_H_

typedef struct _wctk_static_text
{
  char *text;
  sint xpos;
  sint ypos;
  sint width;
  sint height;
  pwctk_window_t parent;
  short default_cpair;
}wctk_static_text_t, *pwctk_static_text_t;

#define WCTK_STATICTEXT_DRAWABLE(s)         ((s->xpos+2 < s->parent->width) && \
                                             (s->ypos+2 < s->parent->height))
#define WCTK_STATICTEXT_DRAWABLE_WIDTH(s)   ((s->xpos+s->width+1) < (s->parent->width))
#define WCTK_STATICTEXT_DRAWABLE_HEIGHT(s)  ((s->ypos+s->height+1) < (s->parent->height))
#define WCTK_STATICTEXT_DRAW_WIDTH(s)       ((WCTK_STATICTEXT_DRAWABLE_WIDTH(s)) ? \
                                              s->width:s->parent->width-1-s->xpos)
#define WCTK_STATICTEXT_DRAW_HEIGHT(s)      ((WCTK_STATICTEXT_DRAWABLE_HEIGHT(s)) ? \
                                              s->height:s->parent->height-1-s->ypos)

pwctk_static_text_t wctk_static_text_create (char *txt, sint x, sint y,
    sint w, sint h, pwctk_window_t parent);
void wctk_static_text_set (pwctk_static_text_t st, char *txt);
void wctk_static_text_draw (pwctk_static_text_t st, sint w, sint h);
void wctk_static_text_move (pwctk_static_text_t st, sint x, sint y);
void wctk_static_text_destroy (pwctk_static_text_t st);

#endif


