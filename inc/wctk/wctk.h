
#ifndef _WCTK_H_
#define _WCTK_H_

#include <stdint.h>
#include <ncurses.h>
#include <wctk/wctk_str.h>
#include <wctk/wctk_draw.h>
#include <wctk/wctk_scrollbar.h>
#include <wctk/wctk_window.h>
#include <wctk/wctk_event.h>
#include <wctk/wctk_mouse.h>
#include <wctk/wctk_static_text.h>
#include <wctk/wctk_button.h>
#include <wctk/wctk_listview.h>
#include <wctk/wctk_prompt.h>
#include <wctk/wctk_widget.h>
#include <wctk/wctk_stack.h>

/* ncurses color pairs (wctkc_fg_bg). */
#define WCTKC_BLACK_BLACK        1
#define WCTKC_RED_BLACK          2
#define WCTKC_GREEN_BLACK        3
#define WCTKC_YELLOW_BLACK       4
#define WCTKC_BLUE_BLACK         5
#define WCTKC_MAGENTA_BLACK      6
#define WCTKC_CYAN_BLACK         7
#define WCTKC_WHITE_BLACK        8
#define WCTKC_BLACK_RED          9
#define WCTKC_RED_RED           10
#define WCTKC_GREEN_RED         11
#define WCTKC_YELLOW_RED        12
#define WCTKC_BLUE_RED          13
#define WCTKC_MAGENTA_RED       14
#define WCTKC_CYAN_RED          15
#define WCTKC_WHITE_RED         16
#define WCTKC_BLACK_GREEN       17
#define WCTKC_RED_GREEN         18
#define WCTKC_GREEN_GREEN       19
#define WCTKC_YELLOW_GREEN      20
#define WCTKC_BLUE_GREEN        21
#define WCTKC_MAGENTA_GREEN     22
#define WCTKC_CYAN_GREEN        23
#define WCTKC_WHITE_GREEN       24
#define WCTKC_BLACK_YELLOW      25
#define WCTKC_RED_YELLOW        26
#define WCTKC_GREEN_YELLOW      27
#define WCTKC_YELLOW_YELLOW     28
#define WCTKC_BLUE_YELLOW       29
#define WCTKC_MAGENTA_YELLOW    30
#define WCTKC_CYAN_YELLOW       31
#define WCTKC_BLACK_BLUE        33
#define WCTKC_RED_BLUE          34
#define WCTKC_GREEN_BLUE        35
#define WCTKC_YELLOW_BLUE       36
#define WCTKC_BLUE_BLUE         37
#define WCTKC_MAGENTA_BLUE      38
#define WCTKC_CYAN_BLUE         39
#define WCTKC_WHITE_BLUE        40
#define WCTKC_BLACK_MAGENTA     41
#define WCTKC_RED_MAGENTA       42
#define WCTKC_GREEN_MAGENTA     43
#define WCTKC_YELLOW_MAGENTA    44
#define WCTKC_BLUE_MAGENTA      45
#define WCTKC_MAGENTA_MAGENTA   46
#define WCTKC_CYAN_MAGENTA      47
#define WCTKC_WHITE_MAGENTA     48
#define WCTKC_BLACK_CYAN        49
#define WCTKC_RED_CYAN          50
#define WCTKC_GREEN_CYAN        51
#define WCTKC_YELLOW_CYAN       52
#define WCTKC_BLUE_CYAN         53
#define WCTKC_MAGENTA_CYAN      54
#define WCTKC_CYAN_CYAN         55
#define WCTKC_WHITE_CYAN        56
#define WCTKC_BLACK_WHITE       57
#define WCTKC_RED_WHITE         58
#define WCTKC_GREEN_WHITE       59
#define WCTKC_YELLOW_WHITE      60
#define WCTKC_BLUE_WHITE        61
#define WCTKC_MAGENTA_WHITE     62
#define WCTKC_CYAN_WHITE        63
#define WCTKC_WHITE_WHITE       64
#define WCTKC_BLACK_DEFAULT     65
#define WCTKC_RED_DEFAULT       66
#define WCTKC_GREEN_DEFAULT     67
#define WCTKC_YELLOW_DEFAULT    68
#define WCTKC_BLUE_DEFAULT      69
#define WCTKC_MAGENTA_DEFAULT   70
#define WCTKC_CYAN_DEFAULT      71
#define WCTKC_WHITE_DEFAULT     72
#define WCTKC_MAX_PAIR          73


#define WCTK_SCREEN_WIDTH        (getmaxx(stdscr))
#define WCTK_SCREEN_HEIGHT       (getmaxy(stdscr))


#ifndef KEY_RETURN
#define KEY_RETURN 0x0000000D
#endif

void wctk_init (void);
void wctk_setup_colors (void);
void wctk_event_get (pwctk_event_t event);
void wctk_event_translate (pwctk_event_t event);
void wctk_refresh (void);
void wctk_quit (void);

#endif

