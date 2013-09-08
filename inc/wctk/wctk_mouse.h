
#ifndef _WCTK_MOUSE_H_
#define _WCTK_MOUSE_H_

void wctk_mouse_init (void);
void wctk_mouse_event (pwctk_event_t event);
uchar wctk_mouse_pressed (pwctk_event_t event);
uchar wctk_mouse_released (pwctk_event_t event);
sint wctk_mouse_getx (void);
sint wctk_mouse_gety (void);
sint wctk_mouse_getsx (void);
sint wctk_mouse_getsy (void);
void wctk_mouse_close (void);

#endif


