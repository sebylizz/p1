default:
	gcc -o input src/input.c src/medicin_input.c sql/sqlite3.c
	./input