all: task3

task3:
	g++ src/task3.cpp -o bin/task3

clean:
	rm -rf bin/task3
