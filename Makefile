all:
	cd Graph; make;
	cd Queue; make;
	cd Stack; make;
	gcc *.c -c  -I "Stack" -I "Graph" -I "Queue"
	gcc *.o -o teste
	rm *.o