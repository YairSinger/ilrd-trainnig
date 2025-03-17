#ifndef __UID_H__
#define __UID_H__

#include <sys/types.h>
#include <stddef.h>
#include <time.h>

typedef struct uid
{
    time_t timestamp;
    size_t counter;
    pid_t pid;
}ilrd_uid_t;

/*
@Description: Generates a new UID.
@Return value: uid struct.
               on failure returns a "bad UID"
@Time Complexity: O(1).
@Notes: None.
*/
ilrd_uid_t GenerateUID();

/*
@Description: Generates a "bad UID".
@Return value: uid struct.
@Time Complexity: O(1).
@Notes: None.
*/
ilrd_uid_t GenerateBadUID();

/*
@Description: Compares two UIDs.
@Parameters:  
			 1. [uid1] - UID.
			 2. [uid2] - UID.
@Return value: 1 if UID's equals or 0 otherwise.
@Time Complexity: O(1).
@Notes: None.
*/
int IsSameUID(ilrd_uid_t uid1, ilrd_uid_t uid2);

#endif /* __UID_H__ */ 
