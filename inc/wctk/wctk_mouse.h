
#ifndef _WCTK_MOUSE_H_
#define _WCTK_MOUSE_H_

void wctk_mouse_init (void);
void wctk_mouse_enable (void);
void wctk_mouse_disable (void);
uint8_t wctk_has_mouse (void);
void wctk_mouse_drag_disable (void);
void wctk_mouse_resize_disable (void);
void wctk_mouse_event (pwctk_event_t event);
uint8_t wctk_mouse_pressed (pwctk_event_t event);
uint8_t wctk_mouse_released (pwctk_event_t event);
int32_t wctk_mouse_getx (void);
int32_t wctk_mouse_gety (void);
int32_t wctk_mouse_getsx (void);
int32_t wctk_mouse_getsy (void);
void wctk_mouse_close (void);

#endif


