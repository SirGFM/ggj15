
CC=gcc
.SUFFIXES=.c .o

#==============================================================================
# Define compilation target
#==============================================================================
  TARGET := game
#==============================================================================

#==============================================================================
# Define every object required by compilation
#==============================================================================
 OBJS = \
         $(OBJDIR)/background.o \
         $(OBJDIR)/camera.o \
         $(OBJDIR)/global.o \
         $(OBJDIR)/main.o \
         $(OBJDIR)/player.o \
         $(OBJDIR)/playstate.o
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
  CFLAGS := -Wall
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
 LFLAGS := -lGFraMe -lm
# Add dependencies
 ifeq ($(OS), Win)
   LFLAGS := -L./lib/GFraMe/bin/Win -lmingw32 $(LFLAGS) -lSDL2main
 else
   LFLAGS := -L./lib/GFraMe/bin/Linux $(LFLAGS)
 endif
 LFLAGS := $(LFLAGS) -lSDL2
#==============================================================================

#==============================================================================
# Define library (to force compilation)
#==============================================================================
 LIB := ./lib/GFraMe/bin/Linux/libGFraMe.a
#==============================================================================

#==============================================================================
# Define where source files can be found and where objects & binary are output
#==============================================================================
 VPATH := src
 OBJDIR := obj
 BINDIR := bin
#==============================================================================

#==============================================================================
# Make the objects list constant
#==============================================================================
 OBJS := $(OBJS)
#==============================================================================

#==============================================================================
# Define default compilation rule
#==============================================================================
all: MKDIRS $(BINDIR)/$(TARGET)
	date
#==============================================================================

$(BINDIR)/$(TARGET): MKDIRS $(LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $(BINDIR)/$(TARGET) $(OBJS) $(LFLAGS)

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

