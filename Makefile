ifeq ($(OS),Windows_NT)
    COMPILE = main.exe
    RUN = .\main.exe
else
    COMPILE = main
    RUN = ./main
endif

main: main.c arena.c
	gcc main.c arena.c -o $(COMPILE)
	$(RUN)
    