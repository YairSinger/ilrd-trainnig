#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /* size_t */

#define BYTES_IN_IP (4)
#define IP_LENGTH (16)

typedef enum dhcp_status
{
    DHCP_ALLOC_SUCCESS,
    DHCP_ALLOC_WRONG_NET,
    DHCP_ALLOC_FAIL,
    DHCP_IS_FULL_ERR,
    DHCP_ALLOC_DOUBLE_FREE
} dhcp_status_t;

typedef struct dhcp dhcp_t;

/*****************************************************************************************/
/*
@Name: DHCPCreate
@Description: 
    Initializes and returns a new dhcp based on the provided Network ID and Net Mask. 
@Parameters: 
    - subnet_id: 
    - subnet_mask: 

@Return: 
    - Returns a valid pointer to the newly created dhcp or NULL if allocation fails.

@Time Complexity: 
    O(1)

@Space Complexity: 
    O(1).
*/
dhcp_t *DHCPCreate(const char *subnet_id, const char *subnet_mask);


/*****************************************************************************************/
/*
@Name: DHCPDestroy
@Description: 
 
@Parameters: 
    - dhcp: A valid pointer to the dhcp.

@Return: 

@Time Complexity: 
    O(n)

@Space Complexity: 
    O(1).
*/
void DHCPDestroy(dhcp_t *dhcp);


/*****************************************************************************************/
/*
@Name: DHCPAllocIP
@Description: 
 
@Parameters: 
    - dhcp: A valid pointer to the dhcp.

@Return: 
		DHCP_ALLOC_SUCCESS,
   		DHCP_ALLOC_FAIL,
    	DHCP_IS_FULL_ERR
    	DHCP_ALLOC_WRONG_NET
@Time Complexity: 
    O(log(n))

@Space Complexity: 
    O().
*/
dhcp_status_t DHCPAllocIP(dhcp_t *dhcp, const char *ip, char *buffer);


/*****************************************************************************************/
/*
@Name: DHCPFreeIP
@Description: 
 
@Parameters: 
    - dhcp: A valid pointer to the dhcp.

@Return: 
		DHCP_ALLOC_WRONG_NET
		DHCP_ALLOC_DOUBLE_FREE
		DHCP_ALLOC_SUCCESS
@Time Complexity: 
    O(log(n))

@Space Complexity: 
    O(1).
*/
dhcp_status_t DHCPFreeIP(dhcp_t *dhcp, const char *ip_to_free);


/*****************************************************************************************/
/*
@Name: DHCPGetCountFreeIP
@Description: 
 
@Parameters: 
    - dhcp: A valid pointer to the dhcp. 

@Return: 
    - Number of free (unused) IP's in the dhcp pool.
@Time Complexity: 
    O(n)

@Space Complexity: 
    O(1).
*/
size_t DHCPCountFreeIP(const dhcp_t *dhcp);

#endif /* __DHCP_H__ */
