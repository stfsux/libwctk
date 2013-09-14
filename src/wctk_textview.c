#include <stdlib.h>
#include <string.h>
#include "wctk/wctk.h"
#include "wctk/wctk_widget.h"

/*-----------------------------------------------------------------*/
pwctk_textview_t
 wctk_textview_create (char *txt, sint x, sint y, sint w, sint h,
     uchar flags, pwctk_window_t parent, uint uid)
{
  pwctk_textview_t textview = NULL;
  if (parent == NULL)
    return NULL;
  if (w <= 2  ||
      h == 0)
    return NULL;
  textview = calloc (1, sizeof(wctk_textview_t));
  if (textview == NULL)
    return NULL;
  if (txt != NULL)
  {
    textview->text = wctk_astr_create ();
    if (textview->text == NULL)
    {
      free (textview);
      return NULL;
    }
    wctk_astr (textview->text, txt);
  }
  textview->xpos = x + 1;
  textview->ypos = y + 1;
  textview->width = w;
  textview->height = h;
  textview->flags = flags;
  textview->colors.default_cpair        = WCTKC_WHITE_BLUE;
  textview->colors.default_hline_cpair  = WCTKC_BLACK_WHITE;
  textview->colors.default_cursor_cpair = WCTKC_WHITE_BLACK;
  textview->colors.focus_hline_cpair    = WCTKC_WHITE_RED;
  textview->colors.focus_cursor_cpair   = WCTKC_RED_WHITE;
  textview->parent = parent;
  textview->uid = uid;
  wctk_widget_attach (textview->parent, textview, WCTKW_TEXTVIEW);
  return textview;
}


/*-----------------------------------------------------------------*/
void
 wctk_textview_draw (pwctk_textview_t textview, uint draw_area_width,
     uint draw_area_height)
{
  uint n = 0, i = 0, line = 0;

  wctk_draw_rect_fill (textview->xpos + textview->parent->xpos,
      textview->ypos + textview->parent->ypos,
      draw_area_width, draw_area_height,
      ' '|COLOR_PAIR(textview->colors.default_cpair));

  for (n = textview->start; (n < textview->start+textview->height) &&
      (n < textview->text->n); n++,line++)
  {
    if (line < draw_area_height)
    {
      for (i = 0; i < strlen (textview->text->str[n]); i++)
      {
        if (i < draw_area_width)
        {
          if (i == textview->xcursor &&
              line == textview->ycursor)
          {
            if (textview->state&WCTK_TEXTVIEW_STATE_FOCUS)
            {
              mvaddch (textview->ypos+textview->parent->ypos+line,
                  textview->xpos+textview->parent->xpos+i,
                  textview->text->str[n][i]|COLOR_PAIR(textview->colors.focus_cursor_cpair));
            }
            else
            {
              mvaddch (textview->ypos+textview->parent->ypos+line,
                  textview->xpos+textview->parent->xpos+i,
                  textview->text->str[n][i]|COLOR_PAIR(textview->colors.default_cursor_cpair));
            }
          }
          else
          {
            mvaddch (textview->ypos+textview->parent->ypos+line,
                textview->xpos+textview->parent->xpos+i,
                textview->text->str[n][i]|COLOR_PAIR(textview->colors.default_cpair));
          }
        }
      }
    }
  }

  if (textview->flags&WCTK_TEXTVIEW_HILINE)
  {
    if ((sint)textview->ycursor < textview->height)
    {
      for (i = 0; i < draw_area_width; i++)
      {
        if (i != textview->xcursor)
        {
          if (textview->state&WCTK_TEXTVIEW_STATE_FOCUS)
          {
            wctk_draw_set_cpair (textview->xpos + textview->parent->xpos + i,
                textview->ypos + textview->parent->ypos + textview->ycursor,
                textview->colors.focus_hline_cpair);
          }
          else
          {
            wctk_draw_set_cpair (textview->xpos + textview->parent->xpos + i,
                textview->ypos + textview->parent->ypos + textview->ycursor,
                textview->colors.default_hline_cpair);
          }
        }
      }
    }
  }
}

/*-----------------------------------------------------------------*/
size_t
 wctk_textview_get_nchar (pwctk_textview_t textview, uint nline)
{
  size_t len = 0;
  len = strlen (textview->text->str[textview->start + nline]);
  return (len == 0) ? 0:len-1;
}

/*-----------------------------------------------------------------*/
void
 wctk_textview_event_translate (pwctk_textview_t textview, pwctk_event_t event)
{
  switch (event->type)
  {
    case WCTK_EVENT_KEY:
      switch (event->data)
      {
        case KEY_LEFT:
          if (textview->xcursor != 0)
            textview->xcursor--;
          break;

        case KEY_RIGHT:
          if (textview->xcursor < wctk_textview_get_nchar (textview, textview->ycursor))
            textview->xcursor++;
          break;

        case KEY_UP:
          if (textview->ycursor != 0)
          {
            textview->ycursor--;
            if (textview->xcursor > wctk_textview_get_nchar (textview, textview->ycursor))
              textview->xcursor = wctk_textview_get_nchar (textview, textview->ycursor);
          }
          else
          {
            wctk_textview_scroll_up (textview, 1);
            if (textview->xcursor > wctk_textview_get_nchar (textview, textview->ycursor))
              textview->xcursor = wctk_textview_get_nchar (textview, textview->ycursor);
          }
          break;

        case KEY_DOWN:
          if ((sint)(textview->ycursor+1) != (textview->height))
          {
            if (textview->ycursor+1 != textview->text->n)
              textview->ycursor++;
            if (textview->xcursor > wctk_textview_get_nchar (textview, textview->ycursor))
              textview->xcursor = wctk_textview_get_nchar (textview, textview->ycursor);
          }
          else
          {
            wctk_textview_scroll_down (textview, 1);
            if (textview->xcursor > wctk_textview_get_nchar (textview, textview->ycursor))
              textview->xcursor = wctk_textview_get_nchar (textview, textview->ycursor);
          }
          break;
      }
      break;

    case WCTK_EVENT_MOUSE:
      break;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_textview_scroll_up (pwctk_textview_t textview, uint nlines)
{
  sint val = (sint)textview->start - (sint)nlines;
  if (val < 0)
    textview->start = 0;
  else
    textview->start = textview->start - nlines;
}

/*-----------------------------------------------------------------*/
void
 wctk_textview_scroll_down (pwctk_textview_t textview, uint nlines)
{
  if (nlines+textview->start+textview->height-1 < textview->text->n)
    textview->start = textview->start+nlines;
}

/*-----------------------------------------------------------------*/
void
 wctk_textview_resize (pwctk_textview_t textview, uint w, uint h)
{
  if (textview != NULL)
  {
    if (w > 1 &&
        h != 0)
    {
      textview->width = w;
      textview->height = h;
      if ((sint)(textview->ycursor+1) > textview->height)
      {
        textview->ycursor = textview->height-1;
        textview->xcursor = 0;
      }
    }
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_textview_set_focus (pwctk_textview_t textview, uchar b)
{
  if (textview == NULL)
    return;
  if (b)
    textview->state = textview->state | WCTK_TEXTVIEW_STATE_FOCUS;
  else
    textview->state = textview->state & (~WCTK_TEXTVIEW_STATE_FOCUS);
}

/*-----------------------------------------------------------------*/
void
 wctk_textview_set_colors (pwctk_textview_t textview,
     pwctk_textview_colors_t colors)
{
  if (colors != NULL &&
      textview != NULL)
  {
    memcpy (&textview->colors, colors,
        sizeof(wctk_textview_colors_t));
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_textview_destroy (pwctk_textview_t textview)
{
  if (textview != NULL)
  {
    if (textview->text != NULL)
      wctk_astr_destroy (textview->text);
    free (textview);
  }
}

