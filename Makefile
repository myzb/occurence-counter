APP		:= occurence-counter

OS 		?= linux
OPT		:= -O2

LIBS	:=
SRCS	:= main.cpp progressbar.cpp worker.cpp utils.c
OBJS	:= $(SRCS:%=%.o)

CFLAGS 	:= -Werror -Wall -Wpedantic
LDFLAGS := -pthread

ifeq ($(DEBUG),1)
CFLAGS	+= -DDEBUG
endif

ifeq ($(OS),win)
	CC		:= x86_64-w64-mingw32-gcc
	CXX		:= x86_64-w64-mingw32-g++
	STRIP	:= x86_64-w64-mingw32-strip --strip-unneeded
	CFLAGS	+= -DOS_WINDOWS
	LDFLAGS	+=

else
	CC		:= gcc
	CXX		:= g++
	STRIP	:= strip --strip-unneeded
	CFLAGS  +=
	LDFLAGS	+=
endif

ifeq ($(V),1)
	Q		:=
else
	Q		:= @
endif


# -----------------------------------------------------------------------------

default: $(APP) strip

$(APP): $(OBJS)
	$(Q) $(CXX) $(OPT) $(LDFLAGS) $(OBJS) $(LIBS) -o $@
	@echo 'Finished building target: $@'
	@echo ' '

%.cpp.o: %.cpp
	$(Q) $(CXX) $(OPT) $(CFLAGS) -c $< -o $@

%.c.o: %.c
	$(Q) $(CC) $(OPT) $(CFLAGS) -c $< -o $@


strip:
	$(Q) $(STRIP) $(APP)*

clean:
	rm -rf *.o $(APP)*
