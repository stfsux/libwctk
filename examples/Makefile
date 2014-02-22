include ../config.mk

all: windows textview listview prompt

windows: windows.c
ifeq ($(STATIC_BINARIES),yes)
	gcc -DNCURSES_STATIC -g -Wall -Wextra -I../inc -o windows windows.c ../lib/libwctk.a -static -lm -lncurses -static-libgcc -ltinfo -lgpm
else
	gcc -g -Wall -Wextra -I../inc -o windows windows.c ../lib/libwctk.a -lm -lncurses 
endif

textview: textview.c
ifeq ($(STATIC_BINARIES),yes)
	gcc -DNCURSES_STATIC -g -Wall -Wextra -I../inc -o textview textview.c ../lib/libwctk.a -static -lncurses -static-libgcc -ltinfo -lgpm
else
	gcc -g -Wall -Wextra -I../inc -o textview textview.c ../lib/libwctk.a -lncurses 
endif

listview: listview.c
	gcc -g -Wall -Wextra -I../inc -o listview listview.c ../lib/libwctk.a -lncurses

prompt: prompt.c
	gcc -g -Wall -Wextra -I../inc -o prompt prompt.c ../lib/libwctk.a -lncurses

clean:
	rm -fv windows textview listview prompt

.PHONY: clean windows textview prompt
