#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*Global variable*/
size_t global_var = 0;

void* thread_func(void* arg) {
   /*Thread local variable*/
    int thread_local_var;
	size_t *arr = (size_t *)arg;
	
    /* Dynamically allocated variable*/
    int* dynamic_var = malloc(sizeof(int));

    printf("Thread id: %ld\n", pthread_self());
    sleep(2);
    printf("Address of thread local variable: %p\n", &thread_local_var);
    
    sleep(2);
    printf("Address of dynamically allocated variable: %p\n", dynamic_var);
    sleep(2);
    printf("Address of stack frame: %p\n", __builtin_frame_address(0));
    sleep(2);


    free(dynamic_var);

    return NULL;
}

int main() {
    pthread_t threads[3];
    int i;
	size_t arr[10] = {0};
    printf("Address of global variable: %p\n", &global_var);

    for(i = 0; i < 3; i++) {
        pthread_create(&threads[i], (void *)arr, thread_func, NULL);
    }

    for(i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
