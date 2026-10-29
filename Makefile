CC := gcc
CFLAGS := -Werror -Wall -Wextra

target := addressbook
src_files := main.c linkedlist.c
obj_files := $(src_files:%.c=build/%.o)

.PHONY: all clean

all: $(target)

$(target): $(obj_files)
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -f $(target) $(obj_files)
	rm -rf build