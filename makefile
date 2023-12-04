all: clean input.exe

input.exe:
	gcc -o input.exe src/input.c src/medicin_input.c sql/sqlite3.c
     
clean:
	rm input.exe