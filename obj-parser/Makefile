# $@ = target file
# $< = first dependency
# $^ = all dependencies

# detect all .o files based on their .c source

SC = scalac

SCALA_SOURCES = $(wildcard src/*.scala)

# First rule is the one executed when no parameters are fed to the Makefile

all: run

run: $(SCALA_SOURCES)
	$(SC) $^

clean:
	$(RM) objparser/*.class objparser/*.tasty
