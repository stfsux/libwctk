#include <stdlib.h>
#include <string.h>
#include "wctk/wctk.h"

/*-----------------------------------------------------------------*/
pwctk_astr_t
 wctk_astr_create (void)
{
  pwctk_astr_t str = NULL;
  str = calloc (1, sizeof (wctk_astr_t));
  if (str == NULL)
    return NULL;
  str->str = calloc (str->n+1, sizeof(char*));
  return str;
}

/*-----------------------------------------------------------------*/
void
 wctk_astr_line (pwctk_astr_t str, char *s, size_t sz)
{
  if (str == NULL)
    return;
  str->str = realloc (str->str, (str->n+1)*sizeof(char*));
  if (str->str == NULL)
    return;
  str->str[str->n] = calloc (sz+1, sizeof(char));
  strncpy (str->str[str->n], s, sz);
  str->n++;
}

/*-----------------------------------------------------------------*/
void
 wctk_astr (pwctk_astr_t str, char *s)
{
  char *begin = s;
  char *end = s;
  size_t sz = 0;
  while (*end != 0)
  {
    if (*end == '\n')
    {
      if (sz != 0)
        wctk_astr_line (str, begin, sz);
      else
        wctk_astr_line (str, " ", 1);
      sz = 0;
      end++;
      begin = end;
    }
    else
    {
      sz++;
      end++;
    }
  }
  if (sz != 0)
    wctk_astr_line (str, begin, sz);
  else
    wctk_astr_line (str, " ", 1);
}

/*-----------------------------------------------------------------*/
void
 wctk_astr_destroy (pwctk_astr_t str)
{
  uint32_t i;
  if (str != NULL)
  {
    if (str->str != NULL)
    {
      for (i = 0; i < str->n; i++)
      {
        if (str->str[i] != NULL)
          free (str->str[i]);
      }
      free (str->str);
    }
    free (str);
  }
}

