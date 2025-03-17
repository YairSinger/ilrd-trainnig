
/* ----------------------------------------------------------
 * Filename:    uid_test.c
 * Author:      Shahar Molina
 * Reviewer:
 * Date:        26.09.2023
 * Course:      OL-149
 * Description:	Test unit for library
 * ----------------------------------------------------------
*/

#include <stdio.h> /* printf */
#include <string.h> /* strerror */
#include <unistd.h> /* sleep */
#include <pthread.h> /* pthread_create, pthread_join */

#include "uid.h" /* API for uid */

/*---Macros---*/
#define NUM_OF_THREADS 4

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"

static void test_UIDGet(void);
static void printUID(const ilrd_uid_t uid);
static int Phase2(void);

int main(void)
{
	test_UIDGet();
	Phase2();
	return 0;
}
static void test_UIDGet(void)
{
    ilrd_uid_t uid1 = UIDGet();
    ilrd_uid_t uid2 = UIDGet();

    if (UIDIsSame(uid1, bad_uid) || UIDIsSame(uid2, bad_uid))
    {
        printf(RED "UIDGet failed: Generated UID is bad_uid\n" RESET);
        return;
    }

    if (UIDIsSame(uid1, uid2))
    {
        printf(RED "UIDGet failed: Generated UIDs are equal\n" RESET);
    }

	if (UIDIsSame(uid1, uid1))
    {
        printf(GREEN "UIDSame succeed: uid1 IsSame as uid1\n" RESET);
    }


    printf(GREEN "UIDGet succeeded: UIDs are unique\n" RESET);
	printUID(uid1);
	printUID(uid2);
	printUID(bad_uid);

}

static void printUID(const ilrd_uid_t uid)
{
    printf("UID Details:\n");
    printf("Counter: %lu\n", uid.counter);
    printf("Timestamp: %ld\n", (long)uid.timestamp);
    printf("PID: %ld\n", (long)uid.pid);
    printf("MAC Address: %02x:%02x:%02x:%02x:%02x:%02x\n",
           uid.mac_address[0], uid.mac_address[1], uid.mac_address[2],
           uid.mac_address[3], uid.mac_address[4], uid.mac_address[5]);
}

typedef struct uid_test_data_t
{
	ilrd_uid_t uid;
} uid_test_data_t;

static void * Phase2Thread(void *data_v)
{
	uid_test_data_t *data = (uid_test_data_t *)data_v;

	data->uid = UIDGet();

	return NULL;
}

static int Phase2(void)
{
	pthread_t threads[NUM_OF_THREADS] = {0};
	size_t i = 0;
	uid_test_data_t data[NUM_OF_THREADS] = {0};

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		sleep(1);
		if (0 != pthread_create(&threads[i], NULL, Phase2Thread, &data[i]))
		{
			/* todo: join all the other threads */
			return -1;
		}
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		void *return_value = 0;
		int result = pthread_join(threads[i], &return_value);

		if (0 != result)
		{
			fprintf(stderr, "Error: pthread_join failed with error %s\n",
			        strerror(result));
			return -1;
		}
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		printUID(data[i].uid);
	}

	return 0;
}
