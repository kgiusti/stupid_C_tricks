C_SOURCES += sorting/insertion_sort.c
C_SOURCES += sorting/merge_sort.c
C_SOURCES += sorting/heap_sort.c

TARGETS += sorting/insertion-sort
sorting/insertion-sort: sorting/insertion_sort.c
	$(CC) sorting/insertion_sort.o -o sorting/insertion-sort

TARGETS += sorting/merge-sort
sorting/merge-sort: sorting/merge_sort.c
	$(CC) sorting/merge_sort.o -o sorting/merge-sort

TARGETS += sorting/heap-sort
sorting/heap-sort: sorting/heap_sort.c
	$(CC) sorting/heap_sort.o -o sorting/heap-sort

