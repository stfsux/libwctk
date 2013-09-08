include ../config.mk

all: windows textview

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

clean:
	rm -fv windows textview

.PHONY: clean windows textview
