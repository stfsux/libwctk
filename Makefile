include config.mk

all: $(LIBSTATIC) $(EXAMPLES)

uninstall:
	$(RM) -f $(PREFIX)/lib/$(LIBSTATIC) $(PREFIX)/include/wctk

install: $(LIBSTATIC)
	$(CP) -vr $(LIBDIR)/$(LIBSTATIC) $(PREFIX)/lib
	$(CP) -vr $(INCDIR)/wctk $(PREFIX)/include

$(EXAMPLES): $(LIBSTATIC)
	@(cd $(EXAMPLES) && $(MAKE))

$(LIBSHARED): $(OBJ_FILES) $(HDR_FILES) | $(LIBDIR)
	$(CC) -o $(LIBDIR)/$(LIBSHARED) 

$(LIBSTATIC): $(OBJ_FILES) $(HDR_FILES) | $(LIBDIR)
	$(AR) rcs $(LIBDIR)/$(LIBSTATIC) $(OBJ_FILES)
	$(RANLIB) $(LIBDIR)/$(LIBSTATIC)

$(LIBDIR):
	mkdir -p $(LIBDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@(cd $(EXAMPLES) && $(MAKE) clean)
	rm -f $(LIBDIR)/*
	rm -f $(SRCDIR)/*.o

.PHONY: clean

