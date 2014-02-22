
#ifndef _WCTK_STACK_H_
#define _WCTK_STACK_H_

typedef struct _wctk_zorder
{
  pwctk_window_t window;
  struct _wctk_zorder *next;
  struct _wctk_zorder *prev;
}wctk_zorder_t, *pwctk_zorder_t;

pwctk_zorder_t wctk_zorder_get_first (void);
pwctk_zorder_t wctk_zorder_get_last (void);
pwctk_window_t wctk_zorder_get_first_window (void);
pwctk_window_t wctk_zorder_get_last_window (void);
pwctk_zorder_t wctk_zorder_get_next (pwctk_zorder_t z);
pwctk_zorder_t wctk_zorder_get_prev (pwctk_zorder_t z);
void wctk_zorder_push (pwctk_window_t window);
void wctk_zorder_pop (void);
void wctk_zorder_pop_target (pwctk_zorder_t z);
pwctk_zorder_t wctk_zorder_get (int32_t x, int32_t y);
void wctk_zorder_switch_next_window (void);
void wctk_zorder_purge (void);

#endif


