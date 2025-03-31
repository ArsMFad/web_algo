all: task1 task2 task3

task1:
	g++ src/rk1_task1.cpp -o build/rk1_task1

task2:
	g++ src/rk1_task2.cpp -o build/rk1_task2

task3:
	g++ src/rk1_task3.cpp -o build/rk1_task3

clean:
	rm -rf build/task1 build/task2 build/task3
