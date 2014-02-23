#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "wctk/wctk.h"

/*------------------------------------------------------------------*/
pwctk_listview_t
 wctk_listview_create (int32_t x, int32_t y, int32_t width,
     int32_t height, uint32_t flags, pwctk_window_t parent, 
     uint32_t uid)
{
  pwctk_listview_t lv = NULL;

  if (parent == NULL)
    return NULL;

  if (width == WCTK_LISTVIEW_MAXWIDTH)
    width = parent->width;

  if (height == WCTK_LISTVIEW_MAXHEIGHT)
    height = parent->height-1;

  if (width <= 2 || height <= 2)
    return NULL;

  lv = calloc (1, sizeof(wctk_listview_t));
  if (lv == NULL)
    return NULL;

  lv->xpos = x;
  lv->ypos = y;

  if (flags&WCTK_LISTVIEW_SCROLLBAR)
    lv->width = width-1;
  else
    lv->width = width;

  lv->height = height;
  lv->flags = flags;
  lv->uid = uid;
  lv->parent = parent;
  lv->current_item = 0;

  lv->colors.default_cpair       = WCTKC_WHITE_BLUE;
  lv->colors.default_hline_cpair = WCTKC_BLACK_WHITE;
  lv->colors.default_sel_cpair   = WCTKC_WHITE_RED;
  lv->colors.focus_hline_cpair   = WCTKC_BLACK_WHITE;
  lv->colors.focus_sel_cpair     = WCTKC_WHITE_RED;

  wctk_widget_attach (lv->parent, lv, WCTKW_LISTVIEW);
  return lv;
}

/*------------------------------------------------------------------*/
void
 wctk_listview_colors_set (pwctk_listview_t lv,
     pwctk_listview_colors_t colors)
{
  if (lv == NULL || colors == NULL)
    return;

  memcpy (&lv->colors, colors, sizeof(wctk_listview_colors_t));
}

/*------------------------------------------------------------------*/
void
 wctk_listview_resize (pwctk_listview_t lv, int32_t width, int32_t height)
{
  if (lv == NULL)
    return;

  lv->width = width;
  lv->height = height;
  if (lv->current_item >= lv->height)
    lv->current_item = lv->height-1;
}

/*------------------------------------------------------------------*/
uint8_t
 wctk_listview_item_add (pwctk_listview_t lv, char *item)
{
  pwctk_listview_item_t lv_item = NULL;
  if (lv == NULL ||
      item == NULL)
    return 0;

  lv_item = calloc (1, sizeof(wctk_listview_item_t));
  if (lv_item == NULL)
    return 0;

  lv_item->item = calloc (strlen(item)+1, sizeof(char));
  if (lv_item->item == NULL)
  {
    free (lv_item);
    return 0;
  }
  memcpy (lv_item->item, item, strlen(item));

  if (lv->head == NULL)
  {
    lv->head = lv_item;
    lv->queue = lv_item;
    lv->start = lv_item;
  }
  else
    wctk_listview_item_queue_add (lv, lv_item);

  if (lv->flags&WCTK_LISTVIEW_AUTOSCROLL)
    wctk_listview_item_hl_next (lv);

  return 1;
}

/*------------------------------------------------------------------*/
uint8_t
 wctk_listview_item_queue_add (pwctk_listview_t lv,
     pwctk_listview_item_t item)
{
  pwctk_listview_item_t old_queue = NULL;
  if (lv == NULL)
    return 0;

  if (lv->nitems+1 > 0)
    lv->nitems++;
  else
    return 0; /* reached the maximum number of items. */

  old_queue = lv->queue;
  old_queue->next = item;
  item->id = old_queue->id+1;
  lv->queue = item;
  item->prev = old_queue;
  return 1;
}
 
/*------------------------------------------------------------------*/
pwctk_listview_item_t
 wctk_listview_item_bottom_get (pwctk_listview_t lv)
{
  pwctk_listview_item_t item = NULL;
  int32_t i;
  
  if (lv == NULL)
    return NULL;

  item = lv->start;
  if (item == NULL)
    return NULL;

  for (i = 0; i < lv->height-1; i++)
  {
    if (item->next == NULL)
      break;
    item = item->next;
  }
  return item;
}

/*------------------------------------------------------------------*/
void
 wctk_listview_item_hl_next (pwctk_listview_t lv)
{
  if (lv == NULL)
    return;

  if (lv->start == NULL)
    return;

  if (lv->current_item+1 != lv->height &&
      lv->current_item + lv->start_item < lv->nitems)
    lv->current_item++;
  else
  {
    if (lv->queue != wctk_listview_item_bottom_get (lv))
    {
      lv->start = lv->start->next;
      lv->start_item++;
    }
  }
}

/*------------------------------------------------------------------*/
void
 wctk_listview_item_hl_prev (pwctk_listview_t lv)
{
  if (lv == NULL)
    return;

  if (lv->start == NULL)
    return;
  
  if (lv->current_item != 0)
    lv->current_item--;
  else
  {
    if (lv->start->prev != NULL)
    {
      lv->start = lv->start->prev;
      lv->start_item--;
    }
  }
}

/*------------------------------------------------------------------*/
void
 wctk_listview_draw (pwctk_listview_t lv, int32_t draw_area_width,
     int32_t draw_area_height)
{
  pwctk_listview_item_t item = NULL;
  int32_t i, j;
  uint32_t id = 0;
  short hcpair = 0;

  if (lv == NULL)
    return;

  if (lv->state&WCTK_LISTVIEW_STATE_FOCUS)
    hcpair = lv->colors.focus_hline_cpair;
  else
    hcpair = lv->colors.default_hline_cpair;

  /* Draw background of the listview. */
  wctk_draw_rect_fill (wctk_listview_xscreen(lv),
      wctk_listview_yscreen(lv), draw_area_width,
      draw_area_height, ' '|COLOR_PAIR(lv->colors.default_cpair));

  /* Draw each item from the linked list starting with    */
  /* the member "start" of the wctk_listview_t structure. */
  item = lv->start;

  for (i = 0; i < draw_area_height; i++)
  {
    if (item == NULL)
      break;

    /* Shit always happens. */
    if ((int32_t)strlen(item->item) < 0)
      break;
    
    if (i == lv->current_item)
    {
      wctk_draw_rect_fill (wctk_listview_xscreen(lv),
          wctk_listview_yscreen(lv) + i, draw_area_width,
          1, ' '|COLOR_PAIR(hcpair));
      id = item->id;
    }

    /* Draw each character */
    for (j = 0; (j < (int32_t)strlen(item->item)) &&
                (j < draw_area_width); j++)
    {
      if (i == lv->current_item)
      {
        mvaddch (wctk_listview_yscreen(lv) + i,
            wctk_listview_xscreen(lv) + j,
            item->item[j]|COLOR_PAIR(hcpair));
      }
      else
      {
        mvaddch (wctk_listview_yscreen(lv) + i,
            wctk_listview_xscreen(lv) + j,
            item->item[j]|COLOR_PAIR(lv->colors.default_cpair));
      }
    }

    item = item->next;
  }

  if (lv->flags&WCTK_LISTVIEW_SCROLLBAR)
    wctk_scrollbar_vertical_draw (lv->parent->xpos + lv->xpos + lv->width,
        wctk_listview_yscreen(lv), lv->height, lv->nitems, id);
}

/*------------------------------------------------------------------*/
void
 wctk_listview_event_translate (pwctk_listview_t lv,
     pwctk_event_t event)
{
  if (lv == NULL ||
      event == NULL)
    return;

  switch (event->type)
  {
    case WCTK_EVENT_KEY:
      switch (event->data)
      {
        case KEY_DOWN:
          wctk_listview_item_hl_next (lv);
          break;

        case KEY_UP:
          wctk_listview_item_hl_prev (lv);
          break;
      }
      break;
  }
}

/*------------------------------------------------------------------*/
void
 wctk_listview_focus_set (pwctk_listview_t lv, uint8_t b)
{
  if (lv == NULL)
    return;

  if(b)
    lv->state = lv->state | WCTK_LISTVIEW_STATE_FOCUS;
  else
    lv->state = lv->state & (~WCTK_LISTVIEW_STATE_FOCUS);
}

/*------------------------------------------------------------------*/
uint8_t
 wctk_listview_item_queue_remove (pwctk_listview_t lv)
{
  pwctk_listview_item_t prev_item = NULL;
  if (lv == NULL)
    return 0;

  if (lv->queue == NULL)
    return 0;

  prev_item = lv->queue->prev;
  if (prev_item == NULL)
  {
    if (lv->queue->item != NULL)
      free (lv->queue->item);
    free (lv->queue);
    lv->queue = NULL;
    lv->head = NULL;
  }
  else
  {
    prev_item->next = NULL;
    if (lv->queue->item != NULL)
      free (lv->queue->item);
    free (lv->queue);
    lv->queue = prev_item;
  }
  if (lv->nitems != 0)
    lv->nitems--;
  return 1;
}

/*------------------------------------------------------------------*/
void
 wctk_listview_destroy (pwctk_listview_t lv)
{
  if (lv == NULL)
    return;

  if (lv->queue != NULL)
    while (wctk_listview_item_queue_remove (lv));

  free (lv);
}

