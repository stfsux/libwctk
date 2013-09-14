
#ifndef _WCTK_EVENT_H_
#define _WCTK_EVENT_H_

typedef struct _wctk_event
{
  unsigned int type;
#define WCTK_EVENT_KEY     1
#define WCTK_EVENT_MOUSE   2
#define WCTK_EVENT_DRAG    3
#define WCTK_EVENT_RESIZE  4
#define WCTK_EVENT_CLOSE   5
#define WCTK_EVENT_BUTTON  6
  pwctk_window_t window;
  int data;
  MEVENT mevent;
}wctk_event_t, *pwctk_event_t;


#endif

