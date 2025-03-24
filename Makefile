all: task5

task5:
	g++ src/task5.cpp -o bin/task5

clean:
	rm -rf bin/task5
