
#ifndef _WCTK_PROMPT_H_
#define _WCTK_PROMPT_H_

#define WCTK_PROMPT_INPUT_BLOCK_SIZE  32

typedef struct _wctk_prompt
{
  char *input;
  int32_t input_size;
  int32_t input_max_size;
  int32_t input_start;
  int32_t cursor;
  int32_t xpos;
  int32_t ypos;
  int32_t xcursor;
  int32_t ycursor;
  int32_t width;
  int32_t height;
  uint32_t flags;
#define WCTK_PROMPT_PASSWORD  (1U<<0)
#define WCTK_PROMPT_ALPHA     (1U<<1)
#define WCTK_PROMPT_PUNCT     (1U<<2)
#define WCTK_PROMPT_DIGIT     (1U<<3)
#define WCTK_PROMPT_XDIGIT    (1U<<4)
#define WCTK_PROMPT_SPACE     (1U<<5)
  uint32_t state;
#define WCTK_PROMPT_STATE_FOCUS (1U<<0)
  pwctk_window_t parent;
  uint32_t uid;
}wctk_prompt_t, *pwctk_prompt_t;

#define WCTK_PROMPT_DRAWABLE(s)         ((s->xpos+2 < s->parent->width) && \
                                             (s->ypos+2 < s->parent->height))
#define WCTK_PROMPT_DRAWABLE_WIDTH(s)   ((s->xpos+s->width+2) < (s->parent->width))
#define WCTK_PROMPT_DRAWABLE_HEIGHT(s)  ((s->ypos+s->height+2) < (s->parent->height))
#define WCTK_PROMPT_DRAW_WIDTH(s)       ((WCTK_PROMPT_DRAWABLE_WIDTH(s)) ? \
                                              s->width:s->parent->width-2-s->xpos)
#define WCTK_PROMPT_DRAW_HEIGHT(s)      ((WCTK_PROMPT_DRAWABLE_HEIGHT(s)) ? \
                                              s->height:s->parent->height-2-s->ypos)

#define wctk_prompt_xscreen(p)  (p->parent->xpos + p->xpos + 1)
#define wctk_prompt_yscreen(p)  (p->parent->ypos + p->ypos + 1)

pwctk_prompt_t wctk_prompt_create (int32_t x, int32_t y, int32_t width, int32_t height,
     uint32_t flags, pwctk_window_t parent, uint32_t uid);
void wctk_prompt_set_focus (pwctk_prompt_t prompt, uint8_t b);
void wctk_prompt_draw (pwctk_prompt_t prompt, int32_t draw_area_width);
void wctk_prompt_event_translate (pwctk_prompt_t prompt, pwctk_event_t event);
void wctk_prompt_add_char (pwctk_prompt_t prompt, char c);
void wctk_prompt_del_char (pwctk_prompt_t prompt);
void wctk_prompt_destroy (pwctk_prompt_t prompt);

#endif

