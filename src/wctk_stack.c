#include <stdlib.h>
#include "wctk/wctk.h"

pwctk_zorder_t _g_wctk_first = NULL;
pwctk_zorder_t _g_wctk_last  = NULL;
pwctk_zorder_t _g_wctk_next  = NULL;

wctk_window_t **_g_wctk_window_stack = NULL;

/*-----------------------------------------------------------------*/
pwctk_zorder_t
 wctk_zorder_get_last (void)
{
  return _g_wctk_last;
}

/*-----------------------------------------------------------------*/
pwctk_zorder_t
 wctk_zorder_get_first (void)
{
  return _g_wctk_first;
}

/*-----------------------------------------------------------------*/
pwctk_window_t
 wctk_zorder_get_first_window (void)
{
  if (_g_wctk_first != NULL)
    return _g_wctk_first->window;
  return NULL;
}

/*-----------------------------------------------------------------*/
pwctk_window_t
 wctk_zorder_get_last_window (void)
{
  if (_g_wctk_last != NULL)
    return _g_wctk_last->window;
  return NULL;
}

/*-----------------------------------------------------------------*/
pwctk_zorder_t
 wctk_zorder_get_next (pwctk_zorder_t z)
{
  return z->next;
}

/*-----------------------------------------------------------------*/
pwctk_zorder_t
 wctk_zorder_get_prev (pwctk_zorder_t z)
{
  return z->prev;
}

/*-----------------------------------------------------------------*/
void
 wctk_zorder_push (pwctk_window_t window)
{
  pwctk_zorder_t new = NULL;

  new = calloc (1, sizeof(wctk_zorder_t));
  if (new == NULL)
    return;

  new->window = window;
  if (_g_wctk_first == NULL)
  {
    _g_wctk_first = new;
    _g_wctk_last  = new;
  }
  else
  {
    _g_wctk_first->prev = new;
    new->next = _g_wctk_first;
    _g_wctk_first = new;
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_zorder_pop (void)
{
  if (_g_wctk_first != NULL)
  {
    pwctk_zorder_t ptr = _g_wctk_first;
    if (ptr->next != NULL)
    {
      _g_wctk_first = ptr->next;
      _g_wctk_first->prev = NULL;
    }
    else
    {
      _g_wctk_first = NULL;
      _g_wctk_last = NULL;
    }
    free (ptr);
  }
}

/*-----------------------------------------------------------------*/
void
 wctk_zorder_pop_target (pwctk_zorder_t z)
{
  pwctk_zorder_t next = NULL;
  pwctk_zorder_t prev = NULL;

  if (z != NULL)
  {
    next = z->next;
    prev = z->prev;

    if (next != NULL)
      next->prev = prev;
    if (prev != NULL)
      prev->next = next;

    if (z == _g_wctk_last)
      _g_wctk_last = prev;

    if (z == _g_wctk_first)
      _g_wctk_first = next;

    free (z);
  }
}

/*-----------------------------------------------------------------*/
pwctk_zorder_t
 wctk_zorder_get (int32_t x, int32_t y)
{
  pwctk_zorder_t ret = NULL;
  pwctk_zorder_t n = _g_wctk_first;
  while (n != NULL)
  {
    if (x >= (n->window->xpos)                         &&
        x <= (n->window->xpos+(int32_t)n->window->width)  &&
        y >= (n->window->ypos)                         &&
        y <= (n->window->ypos+(int32_t)n->window->height))
    {
      ret = n;
      break;
    }
    n = n->next;
  }
  return ret;
}

/*-----------------------------------------------------------------*/
void
 wctk_zorder_switch_next_window (void)
{
  pwctk_zorder_t tmp = NULL;
  pwctk_window_t win = NULL;

  if (_g_wctk_first == NULL)
    return;

  if (_g_wctk_next == NULL)
    _g_wctk_next = _g_wctk_first->next;

  if (_g_wctk_next == NULL)
    return;

  tmp = _g_wctk_next;

  if (tmp != NULL)
    tmp = tmp->next;

  win = _g_wctk_next->window;
  if (_g_wctk_next == _g_wctk_last)
    _g_wctk_last = _g_wctk_last->prev;
  wctk_zorder_pop_target (_g_wctk_next);
  wctk_zorder_push (win);
  if (tmp == NULL)
    _g_wctk_next = _g_wctk_first->next;
  else
    _g_wctk_next = tmp;
}

/*-----------------------------------------------------------------*/
void
 wctk_zorder_purge (void)
{
  while (_g_wctk_first != NULL)
    wctk_zorder_pop ();
}
