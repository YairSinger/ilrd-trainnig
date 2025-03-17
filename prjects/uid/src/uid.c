#include <unistd.h>		/*getpid*/
#include <stdatomic.h>
#include "uid.h"


ilrd_uid_t GenerateUID()
{
	static size_t counter_st = 0;
	ilrd_uid_t uid = {0};
		
	uid.timestamp = time(NULL);
	uid.counter = atomic_fetch_add(&counter_st, 1);
	uid.pid = getpid();

	return uid;
}
/*=======================================*/


ilrd_uid_t GenerateBadUID()
{
	ilrd_uid_t uid = {0};
	return uid;
}


/*=======================================*/


int IsSameUID(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return(uid1.timestamp == uid2.timestamp && 
		   uid1.counter == uid2.counter && 
		   uid1.pid == uid2.pid);
}
