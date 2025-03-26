all: task1

task1:
	g++ src/task1.cpp -o bin/task1

clean:
	rm -rf bin/task1
