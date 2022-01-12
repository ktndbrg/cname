.PHONY: clean clean_all

Qualker.emc: main.o init_engine.o input.o script_engine.o render.o audio.o
	gcc $^ -o $@ -lm `sdl-config --libs` -lGL -lGLU -ltcl

main.o: main.c
	gcc $^ -c -o $@

init_engine.o: init_engine.c
	gcc $^ -c -o $@ `sdl-config --cflags`

input.o: input.c
	gcc $^ -c -o $@ `sdl-config --cflags`

script_engine.o: script_engine.c
	gcc $^ -c -o $@

render.o: render.c
	gcc $^ -c -o $@

audio.o: audio.c
	gcc $^ -c -o $@ `sdl-config --cflags`

clean:
	rm *.o

clean_all:
	rm *.o && rm *.emc
