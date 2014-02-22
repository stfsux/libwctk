
NAME			= wctk
EXAMPLES  = examples
LIBNAME		= lib$(NAME)
LIBSHARED	= $(LIBNAME).so
LIBSTATIC = $(LIBNAME).a
SRCDIR		= src
INCDIR		= inc
LIBDIR		= lib

STATIC_BINARIES = no

CC				= gcc
AR				= ar
RANLIB		= ranlib
MAKE			= make
MKDIR     = mkdir
CP        = cp
RM        = rm

PREFIX		= /usr

SRC_FILES = $(wildcard $(SRCDIR)/*.c)
HDR_FILES = $(wildcard $(INCDIR)/*.h)
OBJ_FILES = $(SRC_FILES:.c=.o)

CFLAGS		= -g -Wall -Wshadow -Wextra -Wmissing-prototypes -Wstrict-prototypes -I./$(INCDIR) -I/usr/local/include -I/usr/include -std=c99 
