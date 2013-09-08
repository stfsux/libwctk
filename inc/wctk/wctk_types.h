
#ifndef _WCTK_TYPES_H_
#define _WCTK_TYPES_H_

#if defined(__i386__)
typedef unsigned long long ulong;
typedef unsigned int       uint;
typedef unsigned short     ushort;
typedef unsigned char      uchar;
typedef signed long long   slong;
typedef signed int         sint;
typedef signed short       sshort;
typedef signed char        schar;
#elif defined(__amd64__)
typedef unsigned long      ulong;
typedef unsigned int       uint;
typedef unsigned short     ushort;
typedef unsigned char      uchar;
typedef signed long        slong;
typedef signed int         sint;
typedef signed short       sshort;
typedef signed char        schar;
#else
#error "Please define types of your architecture."
#endif

#endif

