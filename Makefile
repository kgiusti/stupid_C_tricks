CFLAGS = -Og -Wall -Werror -std=c11

C_INCLUDES := -Iinclude

C_SOURCES :=
TARGETS :=

.PHONY: all
all:

include sorting/Makefile

C_OBJS := $(C_SOURCES:%.c=%.o)
$(C_OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(C_INCLUDES) -c $< -o $@

clean:
	rm -f $(C_OBJS) $(TARGETS)

all: $(C_OBJS) $(TARGETS)
	@echo "C_INCLUDES: $(C_INCLUDES)"
	@echo "C_SOURCES: $(C_SOURCES)"
	@echo "C_OBJS: $(C_OBJS)"
	@echo "TARGETS: $(TARGETS)"
	#$(CC) $(C_OBJS) -o a.out

