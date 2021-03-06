PROJECT = unittest
CC=gcc -g -std=c++11
SHARED_FLAG = -fPIC -shared

OBJDIR = ../obj/unittest/

SRCS  = .
SRCS += ./ut
SRCS += ../ipc
SRCS += ../base
SRCS += ../ev
SRCS += ../net
SRCS += ../net/http
SRCS += ../gziputil
SRCS += ../gziputil/zip

LIB  = -lstdc++ -lpthread

INC  = -I.
INC += -I..

CPP_SRCS = $(foreach d,$(SRCS),$(wildcard $(d)/*.cpp))
C_SRCS   = $(foreach d,$(SRCS),$(wildcard $(d)/*.c))

CPP_OBJS = $(addprefix $(OBJDIR), $(patsubst %.cpp, %.o, $(CPP_SRCS)))
C_OBJS = $(addprefix $(OBJDIR), $(patsubst %.c, %.o, $(C_SRCS)))

OBJS = $(CPP_OBJS)
OBJS += $(C_OBJS)
all : obj $(PROJECT)
obj :
	mkdir -p $(addprefix $(OBJDIR), $(SRCS))

$(PROJECT) : $(OBJS) $(MODULE)
	$(CC) -o $@ $(OBJS) $(LIB)
	@echo ""
	@echo "+--------------------------------------------+"
	@echo "|      Finish compilation unittest           |"
	@echo "+--------------------------------------------+"
	@echo "|   copyright(c)Wang Yaofu  voipman@qq.com   |"
	@echo "+--------------------------------------------+"

clean:
	rm -rf *.o *.a *_unittest

install :
	test -d ../test || mkdir -p ../test
	cp unittest ../test

$(OBJDIR)%.o : %.cpp
	$(CC) $(INC) -c $< -o $@
$(OBJDIR)%.o : %.c
	$(CC) $(INC) -c $< -o $@
$(OBJDIR)%.o : %.cc
	$(CC) $(INC) -c $< -o $@