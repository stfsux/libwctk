
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "wctk/wctk.h"

pwctk_prompt_t
 wctk_prompt_create (int32_t x, int32_t y, int32_t width, int32_t height,
     uint32_t flags, pwctk_window_t parent, uint32_t uid)
{
  pwctk_prompt_t prompt = NULL;

  if (width  < 3 ||
      height == 0 ||
      parent == NULL)
    return NULL;

  prompt = calloc (1, sizeof(wctk_prompt_t));
  if (prompt == NULL)
    return NULL;

  prompt->input_max_size = WCTK_PROMPT_INPUT_BLOCK_SIZE;
  prompt->input = calloc (prompt->input_max_size, sizeof(char));
  if (prompt->input == NULL)
  {
    free (prompt);
    return NULL;
  }

  prompt->xpos = x;
  prompt->ypos = y;
  prompt->width = width;
  prompt->height = height;
  prompt->flags = flags;
  prompt->parent = parent;
  prompt->uid = uid;

  wctk_widget_attach (prompt->parent, prompt, WCTKW_PROMPT);
  return prompt;
}

void
 wctk_prompt_focus_set (pwctk_prompt_t prompt, uint8_t b)
{
  if (prompt == NULL)
    return;

  if (b)
    prompt->state = prompt->state | WCTK_PROMPT_STATE_FOCUS;
  else
    prompt->state = prompt->state & (~WCTK_PROMPT_STATE_FOCUS);
}

void
 wctk_prompt_draw (pwctk_prompt_t prompt, int32_t draw_area_width)
{
  int32_t i;

  /* Draw prompt background. */
  wctk_draw_rect_fill (wctk_prompt_xscreen(prompt),
      wctk_prompt_yscreen(prompt), draw_area_width, 
      1, ' '|COLOR_PAIR(WCTKC_WHITE_BLACK));

  /* Draw prompt input. */
  for (i = 0; (i < draw_area_width) &&
      (i+prompt->input_start < prompt->input_size); i++)
  {
    mvaddch (wctk_prompt_yscreen(prompt),
        wctk_prompt_xscreen(prompt) + i,
        prompt->input[prompt->input_start+i]|COLOR_PAIR(WCTKC_WHITE_BLACK));
  }

  /* Draw cursor. */
  wctk_draw_set_cpair (wctk_prompt_xscreen(prompt) + prompt->xcursor,
      wctk_prompt_yscreen(prompt) + prompt->ycursor, WCTKC_BLACK_WHITE);
}

void
 wctk_prompt_event_translate (pwctk_prompt_t prompt, pwctk_event_t event)
{
  if (prompt == NULL ||
      event == NULL)
    return;

  if ((isalpha(event->data)) && (prompt->flags&WCTK_PROMPT_ALPHA))
    wctk_prompt_add_char (prompt, event->data);
  else if ((isdigit(event->data)) && (prompt->flags&WCTK_PROMPT_DIGIT))
    wctk_prompt_add_char (prompt, event->data);
  else if ((isxdigit(event->data)) && (prompt->flags&WCTK_PROMPT_XDIGIT))
    wctk_prompt_add_char (prompt, event->data);
  else if ((ispunct(event->data)) && (prompt->flags&WCTK_PROMPT_PUNCT))
    wctk_prompt_add_char (prompt, event->data);
  else if (event->data == KEY_BACKSPACE)
    wctk_prompt_del_char (prompt);
}

void
 wctk_prompt_add_char (pwctk_prompt_t prompt, char c)
{
  if (prompt->input_size < prompt->input_max_size)
  {
    prompt->input[prompt->input_size] = c;
    if (prompt->input_size < INT_MAX-1) 
      prompt->input_size++;
  }
  else
  {
    char *ptr = NULL;
    prompt->input_max_size = prompt->input_max_size + WCTK_PROMPT_INPUT_BLOCK_SIZE;
    if (prompt->input_max_size == INT_MAX-WCTK_PROMPT_INPUT_BLOCK_SIZE)
      return;
    ptr = realloc (prompt->input, prompt->input_max_size);
    if (ptr == NULL)
      return;
    prompt->input = ptr;
    prompt->input[prompt->input_size] = c;
    if (prompt->input_size < INT_MAX-1)
      prompt->input_size++;
  }
  prompt->xcursor++;
  prompt->cursor++;
  if (prompt->xcursor > prompt->width-1)
  {
    prompt->input_start++;
    prompt->xcursor = prompt->width-1;
  }
}

void
 wctk_prompt_del_char (pwctk_prompt_t prompt)
{
  if (prompt->xcursor != 0)
  {
    if (prompt->input_size != 0)
    {
      prompt->input[prompt->input_size] = 0;
      prompt->input_size--;
    }
    prompt->xcursor--;
  }
  else
  {
    if (prompt->input_start != 0)
    {
      if (prompt->input_start < prompt->width)
      {
        prompt->input_start = 0;
        prompt->cursor = prompt->input_size;
        prompt->xcursor = prompt->input_size;
      }
      else
      {
        prompt->input_start = prompt->input_start - prompt->width + 1;
        prompt->xcursor = prompt->width - 1;
        prompt->cursor = prompt->width - 1;
      }
    }
  }
}

void
 wctk_prompt_destroy (pwctk_prompt_t prompt)
{
  if (prompt == NULL)
    return;

  if (prompt->input != NULL)
    free (prompt->input);

  free (prompt);
}

