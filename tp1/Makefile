CC    :=    gcc
CFLAGS := -g -Wall

TARGET := tp1
SRCEXT := c

SRCDIR := src
OBJDIR := build
INCDIR := include

INC := -I $(INCDIR)/
MAIN := main.c

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
    $(CC) $(CFLAGS) $(INC) -c -o $@ $<

compile: $(OBJECTS)
    $(CC) $(CFLAGS) $(INC) $(MAIN) $^ -o $(TARGET)

clen:
	$(RM) $(TARGET)
	$(RM) -r $(OBJDIR)