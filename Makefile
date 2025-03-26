all: task2

task2:
	g++ src/task2.cpp -o bin/task2

clean:
	rm -rf bin/task2
