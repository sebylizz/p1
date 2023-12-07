default:
	gcc -o input src/main.c src/helpers.c sql/sqlite3.c
	./input