CFLAGS= -Wall -pedantic -std=gnu99
LIBS = `pkg-config --cflags --libs libnotify`
SRCDIR = src
BUILDDIR = build
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))

EXECUTABLE = $(BUILDDIR)/diskhoundd

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(BUILDDIR)
	gcc $(CFLAGS) $(LIBS) -c $< -o $@

$(EXECUTABLE): $(OBJS)
	gcc $(CFLAGS) $(LIBS) $(OBJS) -o $(EXECUTABLE)

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)

run: $(EXECUTABLE)
	./$(EXECUTABLE) /
