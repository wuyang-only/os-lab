# 实验三 进程管理与进程同步

> 环境：Ubuntu 20.04.6 LTS　gcc/g++ 9.4.0　glibc 2.31（POSIX 线程、信号量）
> 代码目录：`lab3/`　编译：`make`（在 `lab3/` 下执行）

```
lab3/
├── Makefile
├── task1_process/        create_process.c
├── task2_socket/         server.c  client.c
├── task3_thread/         create_thread.c
├── task4_sched/          cpu_scheduling.c
├── task5_semaphore/      producer_consumer_semaphore.c
├── task6_monitor/        producer_consumer_monitor.cpp
└── task7_dining/         dining_philosophers.c
```

## 任务 1：创建进程

`fork()` 返回值区分父子进程：子进程返回 0，父进程返回子进程 PID，失败返回 -1。

```c
pid_t pid = fork();
if (pid < 0) { perror("fork failed"); return 1; }
else if (pid == 0) printf("This is the child process with PID %d\n", getpid());
else               printf("This is the parent process with PID %d\n", getpid());
```

```bash
$ gcc create_process.c -o create_process && ./create_process
This is the parent process with PID 351151
This is the child process with PID 351152
```

## 任务 2：进程通信（Socket）

服务器创建 TCP 套接字、绑定 8080 端口、监听并 `accept`；客户端 `connect` 后发送字符串。
服务器中加入 `SO_REUSEADDR`，避免重启时端口被占用。

```c
// server.c
socket(AF_INET, SOCK_STREAM, 0) -> bind() -> listen() -> accept() -> read()
// client.c
socket() -> inet_pton("127.0.0.1") -> connect() -> send()
```

```bash
$ ./server &      # 先启动服务器
Server listening on port 8080...
$ ./client
Message sent to server
$ cat server.log
Message from client: Hello, server!
```

## 任务 3：创建线程（pthread）

主线程循环创建 2 个线程，每个线程打印自己的编号，最后 `pthread_exit` 等待线程结束。

```c
pthread_create(&threads[t], NULL, print_message_function, (void *)t);
```

```bash
$ gcc -pthread create_thread.c -o create_thread && ./create_thread
In main: creating thread 0
In main: creating thread 1
Thread #0 is running
Thread #1 is running
```

## 任务 4：CPU 调度（FCFS 与时间片轮转）

FCFS 按到达顺序执行，等待时间逐个累加；RR 以时间片 4 轮转，用剩余时间模拟。

```bash
$ ./cpu_scheduling
FCFS:
Process  Burst  Waiting  Turnaround
  P1     10     0        10
  P2     5      10       15
  P3     8      15       23
Average waiting time = 8.33, average turnaround time = 16.00

Round Robin (quantum = 4):
Process  Burst  Waiting  Turnaround
  P1     10     13       23
  P2     5      12       17
  P3     8      13       21
Average waiting time = 12.67, average turnaround time = 20.33
```

## 任务 5：信号量解决生产者-消费者

`empty` 表示空缓冲区数量，`full` 表示产品数量，`mutex` 保护缓冲区；生产者先 P(empty) 再 P(mutex)，
消费者相反，顺序错误会导致死锁。

```bash
$ ./producer_consumer_semaphore
Produced: 83
Consumed: 83
Produced: 86
Consumed: 86
...
```

## 任务 6：管程解决生产者-消费者

用 `pthread_mutex_t` + 两个条件变量 `full`、`empty` 模拟管程：缓冲区满时生产者在 `empty` 上等待，
空时消费者在 `full` 上等待，`pthread_cond_signal` 唤醒对方。

```bash
$ ./producer_consumer_monitor
Produced: 83
Consumed: 83
Produced: 86
Consumed: 86
...
```

## 任务 7：哲学家就餐（死锁避免）

5 个哲学家、5 根筷子，每根筷子用一个初值为 1 的信号量表示。若所有哲学家同时拿起左边筷子会形成
循环等待而死锁；程序让**奇数号哲学家先右后左、偶数号先左后右**，破坏循环等待条件。

```bash
$ timeout 8 ./dining_philosophers
Philosopher 4 is thinking.
Philosopher 0 is thinking.
Philosopher 1 is eating.
Philosopher 2 is eating.
...
```

运行期间哲学家不断在思考与进餐之间切换，没有出现全部阻塞的情况，说明未发生死锁。

## 遇到的问题

| 问题 | 原因 | 解决 |
| --- | --- | --- |
| 后台运行时 `server.log` 为空 | 标准输出重定向到文件后为全缓冲，进程被结束时缓冲区未刷新 | 用 `stdbuf -oL` 行缓冲，或在代码中 `fflush` |
| 服务器重启报 `bind failed` | 8080 端口处于 TIME_WAIT | 设置 `SO_REUSEADDR` |
| 哲学家程序全部停住 | 所有哲学家同时拿左筷子形成循环等待 | 改变加锁顺序（奇偶相反）破坏循环等待 |
| `timeout` 结束程序后没有输出 | 同上，输出被缓冲 | 使用 `stdbuf -oL` 管道输出 |
