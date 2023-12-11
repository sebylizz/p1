default:
	gcc -o main.exe src/main.c src/doctor.c src/helpers.c sql/sqlite3.c
	./input