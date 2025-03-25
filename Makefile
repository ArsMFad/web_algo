all: task6

task6:
	g++ src/task6.cpp -o bin/task6

clean:
	rm -rf bin/task6
