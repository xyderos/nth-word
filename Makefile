CC 		 	:= clang
CFLAGS	:= -g -Wall -Wextra -O3
SRC			:= src
BIN     := tsk
LIBS		:= -lm
OBJS		:=
TARGET	:= dev
ENTITIES:= src/entities.h
OBJDIR	:= obj

ifeq ($(TARGET), dev)
	OBJS :=$(addprefix $(OBJDIR)/,hash.o table.o tsk.o)
else
	OBJS :=$(addprefix $(OBJDIR)/,hash.o table.o tsk.o, qsort.o)
endif

$(BIN): DIRECTORIES $(OBJS) $(SRC)/$(BIN).c
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

$(OBJDIR) $(OBJDIR)/%.o: $(SRC)/%.c $(SRC)/%.h $(ENTITIES)
	$(CC) $(CFLAGS) -c $< -o $@

DIRECTORIES:
	mkdir -p $(OBJDIR)

clean:
	rm -f *~ *.o $(TARGET)
	rm -rf obj

all: clean $(BIN)
