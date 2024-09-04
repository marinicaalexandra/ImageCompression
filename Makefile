build: 
	gcc -std=gnu11 -g -o quadtree main.c task1.c
run: 
	./quadtree
clean: 
	rm quadtree
