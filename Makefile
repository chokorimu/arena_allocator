ifeq ($(OS),Windows_NT)
    COMPILE = main.exe
    RUN = .\main.exe
else
    COMPILE = main
    RUN = ./main
endif

main: main.c arena.c queue.c
	gcc main.c arena.c queue.c -o $(COMPILE)
	$(RUN)
    