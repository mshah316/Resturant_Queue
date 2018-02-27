llimplimentation.o: proj4.h llimplimentation.c
	gcc -c llimplimentation.c

llist_helpers.o: proj4.h llist_helpers.c
	gcc -c llist_helpers.c

driver: driver.c llist_helpers.o llimplimentation.o
	gcc driver.c llimplimentation.o llist_helpers.o -o driver


clean:  
	rm -f driver *.o