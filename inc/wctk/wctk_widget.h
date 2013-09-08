
#ifndef _WCTK_WIDGET_H_
#define _WCTK_WIDGET_H_

#define WCTK_WIDGET_BUTTON(w)   ((pwctk_button_t)w)
#define WCTK_WIDGET_TEXTVIEW(w) ((pwctk_textview_t)w)

void wctk_widget_attach (pwctk_window_t parent, void *widget, uint type);
void wctk_widget_draw (pwctk_window_t parent);
void wctk_widget_event_translate (pwctk_window_t parent, pwctk_event_t event);
void wctk_widget_set_focus (pwctk_widget_t widget, uchar b);
uchar wctk_widget_focus_next (pwctk_window_t window);
void wctk_widget_focus_first (pwctk_window_t window);
void wctk_widget_destroy (pwctk_window_t parent);

#endif

