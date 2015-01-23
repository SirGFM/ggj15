
CC=gcc
.SUFFIXES=.c .o

#==============================================================================
# Define compilation target
#==============================================================================
  TARGET := game
#==============================================================================

#==============================================================================
# Set OS flag
#==============================================================================
  OS := $(shell uname)
  ifeq ($(OS), MINGW32_NT-6.1)
    OS := Win
  endif
#==============================================================================

#==============================================================================
# Define CFLAGS (compiler flags)
#==============================================================================
# Add all warnings and default include path
  CFLAGS := -Wall -I"./include" -I"./src/include" 
# Add the framework includes
  CFLAGS := $(CFLAGS) -I"./lib/GFraMe/include/"
# Add architecture flag
  ARCH := $(shell uname -m)
  ifeq ($(ARCH), x86_64)
    CFLAGS := $(CFLAGS) -m64
  else
    CFLAGS := $(CFLAGS) -m32
  endif
# Add debug flags
  ifneq ($(RELEASE), yes)
    CFLAGS := $(CFLAGS) -g -O0 -DDEBUG
  endif
#==============================================================================

#==============================================================================
# Define LFLAGS (linker flags)
#==============================================================================
# Add the framework library
 LFLAGS := -L./lib/GFraMe/bin/Linux -lGFraMe -lm
# Add dependencies
 ifeq ($(OS), Win)
   LFLAGS := $(LFLAGS) -lSDL2main
 endif
 LFLAGS := $(LFLAGS) -lSDL2
#==============================================================================

#==============================================================================
# Define where source files can be found and where objects & binary are output
#==============================================================================
 VPATH := src
 OBJDIR := obj
 BINDIR := bin
#==============================================================================

#==============================================================================
# Define every object required by compilation
#==============================================================================
 OBJS := \
         $(OBJDIR)/main.o
#==============================================================================

#==============================================================================
# Define library (to force compilation)
#==============================================================================
 LIB := ./lib/GFraMe/bin/Linux/libGFraMe.a
#==============================================================================

#==============================================================================
# Define default compilation rule
#==============================================================================
all: MKDIRS $(BINDIR)/$(TARGET)
	date
#==============================================================================

$(BINDIR)/$(TARGET): MKDIRS $(LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(TARGET) $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIB):
	make static --directory=./lib/GFraMe/

MKDIRS: | $(OBJDIR) $(BINDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

.PHONY: clean mostlyclean

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@rm -rf $(BINDIR)

mostlyclean:
	@make clean
	@make clean --directory=./lib/GFraMe/

