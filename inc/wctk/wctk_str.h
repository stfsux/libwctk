
#ifndef _WCTK_STR_H_
#define _WCTK_STR_H_

/* Array of string(s).             */
typedef struct _wctk_astr
{
  uint32_t n;
  char **str;
}wctk_astr_t, *pwctk_astr_t;

/* Linked string(s). */
typedef struct _wctk_lstr
{
  char *str;
  struct _wctk_lstr *next;
}wctk_lstr_t, *pwctk_lstr_t;

pwctk_astr_t wctk_astr_create (void);
void wctk_astr_line (pwctk_astr_t str, char *s, size_t sz);
void wctk_astr (pwctk_astr_t str, char *s);
void wctk_astr_destroy (pwctk_astr_t str);

#endif

