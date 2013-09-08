
#ifndef _WCTK_EVENT_H_
#define _WCTK_EVENT_H_

typedef struct _wctk_event
{
  void *widget;
  unsigned int widget_uid;
  unsigned int widget_type;
  unsigned int event_type;
#define WCTK_EVENT_MOUSE   1
#define WCTK_EVENT_KEY     2
#define WCTK_EVENT_DRAG    3
#define WCTK_EVENT_RESIZE  4
#define WCTK_EVENT_CLOSE   5
  pwctk_window_t window;
  int key;
  MEVENT mevent;
}wctk_event_t, *pwctk_event_t;


#endif

