all: task_

task_:
	g++ src/task_.cpp -o build/task_

clean:
	rm -rf build/task1 build/task2 build/task3
