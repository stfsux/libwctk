#ifndef _WCTK_LISTVIEW_H_
#define _WCTK_LISTVIEW_H_

typedef struct _wctk_listview_colors
{
  short default_cpair;
  short default_hline_cpair;
  short default_sel_cpair;
  short focus_hline_cpair;
  short focus_sel_cpair;
}wctk_listview_colors_t, *pwctk_listview_colors_t;

typedef struct _wctk_listview_item
{
  char *item;
  uint8_t state;
#define WCTK_LISTVIEW_ITEM_STATE_SELECTED (1<<0)
  uint32_t id;
  struct _wctk_listview_item *next;
  struct _wctk_listview_item *prev;
}wctk_listview_item_t, *pwctk_listview_item_t;

typedef struct _wctk_listview
{
  pwctk_listview_item_t head;
  pwctk_listview_item_t queue;
  pwctk_listview_item_t start;
  int32_t start_item;
  int32_t current_item;
  int32_t nitems;
  int32_t xpos;
  int32_t ypos;
  int32_t width;
  int32_t height;
  uint32_t flags;
#define WCTK_LISTVIEW_AUTOSCROLL   (1U<<0)
#define WCTK_LISTVIEW_QUEUE_FIRST  (1U<<1)
#define WCTK_LISTVIEW_SCROLLBAR    (1U<<2)
  uint32_t state;
#define WCTK_LISTVIEW_STATE_FOCUS (1U<<0)
  pwctk_window_t parent;
  wctk_listview_colors_t colors;
  uint32_t uid;
}wctk_listview_t, *pwctk_listview_t;

#define WCTK_LISTVIEW_DRAWABLE(s)         ((s->xpos+2 < s->parent->width) && \
                                             (s->ypos+2 < s->parent->height))
#define WCTK_LISTVIEW_DRAWABLE_WIDTH(s)   ((s->xpos+s->width+2) < (s->parent->width))
#define WCTK_LISTVIEW_DRAWABLE_HEIGHT(s)  ((s->ypos+s->height+2) < (s->parent->height))
#define WCTK_LISTVIEW_DRAW_WIDTH(s)       ((WCTK_LISTVIEW_DRAWABLE_WIDTH(s)) ? \
                                              s->width:s->parent->width-2-s->xpos)
#define WCTK_LISTVIEW_DRAW_HEIGHT(s)      ((WCTK_LISTVIEW_DRAWABLE_HEIGHT(s)) ? \
                                              s->height:s->parent->height-2-s->ypos)

#define wctk_listview_xscreen(p)  (p->parent->xpos + p->xpos + 1)
#define wctk_listview_yscreen(p)  (p->parent->ypos + p->ypos + 1)

pwctk_listview_t
 wctk_listview_create (int32_t x, int32_t y, int32_t width,
     int32_t height, uint32_t flags, pwctk_window_t parent, 
     uint32_t uid);
void wctk_listview_resize (pwctk_listview_t lv, int32_t width, int32_t height);
uint8_t wctk_listview_add_item (pwctk_listview_t lv, char *item);
uint8_t wctk_listview_item_add_queue (pwctk_listview_t lv,
     pwctk_listview_item_t item);
pwctk_listview_item_t  wctk_listview_item_get_bottom (pwctk_listview_t lv);
void wctk_listview_item_hl_next (pwctk_listview_t lv);
void wctk_listview_item_hl_prev (pwctk_listview_t lv);
void wctk_listview_draw (pwctk_listview_t lv, int32_t draw_area_width,
     int32_t draw_area_height);
void wctk_listview_event_translate (pwctk_listview_t lv,
     pwctk_event_t event);
void wctk_listview_set_focus (pwctk_listview_t lv, uint8_t b);
uint8_t wctk_listview_item_remove_queue (pwctk_listview_t lv);
void wctk_listview_destroy (pwctk_listview_t lv);

#endif

