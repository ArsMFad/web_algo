all: task3

task3:
	g++ src/module_3/task3.cpp -o build/task3

clean:
	rm -rf build/task3
