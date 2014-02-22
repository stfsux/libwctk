
#ifndef _WCTK_WIDGET_H_
#define _WCTK_WIDGET_H_

#define WCTK_WIDGET_BUTTON(w)     ((pwctk_button_t)w)
#define WCTK_WIDGET_LISTVIEW(w)   ((pwctk_listview_t)w)
#define WCTK_WIDGET_STATICTEXT(w) ((pwctk_static_text_t)w)
#define WCTK_WIDGET_PROMPT(w)     ((pwctk_prompt_t)w)

void wctk_widget_attach (pwctk_window_t parent, void *widget, uint32_t type);
void wctk_widget_draw (pwctk_window_t parent);
void wctk_widget_event_translate_all (pwctk_window_t parent, pwctk_event_t event);
void wctk_widget_event_translate (pwctk_window_t parent, pwctk_event_t event);
void wctk_widget_set_focus (pwctk_widget_t widget, uint8_t b);
uint8_t wctk_widget_focus_next (pwctk_window_t window);
void wctk_widget_focus_first (pwctk_window_t window);
/* uint8_t wctk_widget_hit (pwctk_widget_t widget, int32_t x, int32_t y); */
/* pwctk_widget_t wctk_widget_hit_region (pwctk_window_t window, int32_t x, int32_t y); */
void wctk_widget_destroy (pwctk_window_t parent);

#endif

