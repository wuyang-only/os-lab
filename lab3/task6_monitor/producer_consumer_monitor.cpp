#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

#define BUFFER_SIZE 5

std::queue<int> buffer;
pthread_mutex_t mutex;
pthread_cond_t full, empty;

void *producer(void *param) {
    for (int i = 0; i < 10; i++) {
        int item = rand() % 100;
        pthread_mutex_lock(&mutex);
        while ((int)buffer.size() == BUFFER_SIZE)
            pthread_cond_wait(&empty, &mutex);
        buffer.push(item);
        std::cout << "Produced: " << item << std::endl;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
        usleep(200000);
    }
    return nullptr;
}

void *consumer(void *param) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex);
        while (buffer.empty())
            pthread_cond_wait(&full, &mutex);
        int item = buffer.front();
        buffer.pop();
        std::cout << "Consumed: " << item << std::endl;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        usleep(200000);
    }
    return nullptr;
}

int main() {
    pthread_t prod_thread, cons_thread;
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&full, nullptr);
    pthread_cond_init(&empty, nullptr);
    pthread_create(&prod_thread, nullptr, producer, nullptr);
    pthread_create(&cons_thread, nullptr, consumer, nullptr);
    pthread_join(prod_thread, nullptr);
    pthread_join(cons_thread, nullptr);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    return 0;
}
