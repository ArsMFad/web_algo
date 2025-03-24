all: task4

task4:
	g++ src/task4.cpp -o bin/task4

clean:
	rm -rf bin/task4
