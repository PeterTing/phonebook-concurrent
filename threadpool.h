#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#define MAX_THREADS 64
#define MAX_QUEUE 65536

typedef enum {
    threadpool_invalid        = -1,
    threadpool_lock_failure   = -2,
    threadpool_queue_full     = -3,
    threadpool_shutdown       = -4,
    threadpool_thread_failure = -5
} threadpool_error_t;

typedef struct {
    void (*function)(void *);
    void *argument;
} threadpool_task_t;

typedef enum {
    threadpool_graceful       = 1
} threadpool_destroy_flags_t;

typedef struct _thread_pool {
    pthread_mutex_t lock;
    pthread_cond_t notify;
    pthread_t *threads;
    threadpool_task_t *queue;
    int thread_count;
    int queue_size;
    int head;
    int tail;
    int count;
    int started;
    int shutdown;
} threadpool_t;

int threadpool_add(threadpool_t *pool, void(*routine)(void *), void *arg, int flags);

threadpool_t *createPool(int thread_count, int pool_size, int flags);

int threadpool_destroy(threadpool_t *pool, int flags);

#endif
