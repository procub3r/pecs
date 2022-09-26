cc := clang
cflags := -std=c99 -glldb -Wall -pipe -Ipecs/

target := bin/main
mkdir = mkdir -p $(@D)

cfiles := $(shell find . -type f -name "*.c")
ofiles := $(addprefix bin/,$(cfiles:.c=.o))

$(target): $(ofiles)
	$(cc) $^ -o $@

bin/%.o: %.c
	$(mkdir)
	$(cc) $(cflags) -c $< -o $@

.PHONY: run
run: $(target)
	$(target)

.PHONY: clean
clean:
	rm -r bin/*
