/* ----------------------------------------------------------
 * Filename:    uid.c
 * Author:      Shahar Molina
 * Reviewer:
 * Date:        26.09.2023
 * Course:      OL-149
 * Description: Implementation of unique identifier generation.
 * ----------------------------------------------------------
 */

#include <unistd.h>     /* getpid */
#include <time.h>       /* time */
#include <ifaddrs.h>    /* getifaddrs, freeifaddrs */
#include <string.h>     /* memcpy */
#include <linux/if_packet.h> /* struct sockaddr_ll */
#include <stdatomic.h> /* atomic_fetch_add */

#include "uid.h"        /* API for UID */

#define MAC_ADDRESS_SIZE 6

/* -------------------Global Variable-------------------- */
const ilrd_uid_t bad_uid = {0, (time_t)-1, (pid_t)-1, {'\0'}};

/* -------------------Function Decleration-------------------- */
static int GetMacAddress(unsigned char mac_address[6]);

/* -------------------Functions Definition-------------------- */
ilrd_uid_t UIDGet(void)
{
    ilrd_uid_t uid = bad_uid;
    static atomic_size_t counter = 0;

	uid.pid = getpid();

    uid.timestamp = time(NULL);
    if (uid.timestamp == (time_t)-1)
    {
        return bad_uid;
    }

    if (-1 == GetMacAddress(uid.mac_address))
    {
        return bad_uid;
    }

	uid.counter = counter;
	counter += 1;

    return uid;
}

int UIDIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{
    return (0 == memcmp(uid1.mac_address, uid2.mac_address, sizeof(uid1.mac_address))) &&
           (uid1.timestamp == uid2.timestamp) &&
           (uid1.pid == uid2.pid) &&
           (uid1.counter == uid2.counter);
}

static int GetMacAddress(unsigned char *mac_address)
{
    struct ifaddrs *ifaddr;
	struct ifaddrs *ifa;

    if (-1 == getifaddrs(&ifaddr))
    {
        return -1;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr != NULL && ifa->ifa_addr->sa_family == AF_PACKET)
        {
            struct sockaddr_ll *sll = (struct sockaddr_ll *)ifa->ifa_addr;
            if (sll->sll_halen == MAC_ADDRESS_SIZE)
            {
                if (0 != *(sll->sll_addr))
				{
					memcpy(mac_address, sll->sll_addr, MAC_ADDRESS_SIZE);
					freeifaddrs(ifaddr);
					return 0;
				}
            }
        }
    }

    freeifaddrs(ifaddr);
    return -1;
}

