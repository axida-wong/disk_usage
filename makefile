.PHONY = ALL
ALL: disk_usage
FLAGS = -Wall --std=c18 -D_XOPEN_SOURCE=700 -g

disk_usage: disk_usage.c
	gcc $(FLAGS) disk_usage.c -o disk_usage

clean:
	rm disk_usage
