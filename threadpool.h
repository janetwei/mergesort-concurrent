#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct _task {
    void (*func)(void *);
    void *arg;
    struct _task *next, *last;
} task_t;

void task_free(task_t *the_task);

typedef struct {
    task_t *head, *tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    uint32_t size;
} tqueue_t;

void tqueue_init(tqueue_t *the_queue);
task_t *tqueue_pop(tqueue_t *the_queue);
uint32_t tqueue_size(tqueue_t *the_queue);
void tqueue_push(tqueue_t *the_queue, task_t *task);
void tqueue_free(tqueue_t *the_queue);

typedef struct {
    pthread_t *threads;
    uint32_t count;
    tqueue_t *queue;
} tpool_t;

void tpool_init(tpool_t *the_pool, uint32_t count, void *(*func)(void *));
void tpool_free(tpool_t *the_pool);

#endif
