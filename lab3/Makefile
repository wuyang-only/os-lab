# 实验三 进程管理与进程同步
CC = gcc
CXX = g++
CFLAGS = -Wall -g -pthread

all: task1 task2 task3 task4 task5 task6 task7

task1:
	$(CC) task1_process/create_process.c -o task1_process/create_process

task2:
	$(CC) task2_socket/server.c -o task2_socket/server
	$(CC) task2_socket/client.c -o task2_socket/client

task3:
	$(CC) $(CFLAGS) task3_thread/create_thread.c -o task3_thread/create_thread

task4:
	$(CC) task4_sched/cpu_scheduling.c -o task4_sched/cpu_scheduling

task5:
	$(CC) $(CFLAGS) task5_semaphore/producer_consumer_semaphore.c -o task5_semaphore/producer_consumer_semaphore

task6:
	$(CXX) -pthread task6_monitor/producer_consumer_monitor.cpp -o task6_monitor/producer_consumer_monitor

task7:
	$(CC) $(CFLAGS) task7_dining/dining_philosophers.c -o task7_dining/dining_philosophers

clean:
	rm -f task1_process/create_process task2_socket/server task2_socket/client \
	      task3_thread/create_thread task4_sched/cpu_scheduling \
	      task5_semaphore/producer_consumer_semaphore \
	      task6_monitor/producer_consumer_monitor task7_dining/dining_philosophers

.PHONY: all clean task1 task2 task3 task4 task5 task6 task7
