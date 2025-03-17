/***********************************************************
*PROJECT:DHCP
*
*WRITER: Yair Singer
*
*REVIEWER: Shaked Weinberger
*
*STATUS: Approved
*
*DATE: 24/10/23
***********************************************************/
#include <stdlib.h> /*NULL, Malloc*/
#include <assert.h>
#include <string.h> /*memset*/
#include <netinet/in.h>  /*AF_INET */
#include <sys/socket.h> 
#include <arpa/inet.h> /*inet_pton*/
#include "dhcp.h"
#include "trie.h"

#define TRUE 1
#define RESERVED_IP_1 0xFFFFFFFF
#define RESERVED_IP_2 0xFFFFFFFE
#define RESERVED_IP_3 0x00000000
#define IPV4_SIZE 32
#define INET_ADDRSTRLEN 16
#define SYSTEM_IP 3

struct dhcp
{
	unsigned int subnet_id;
	unsigned int submask;
	size_t tree_height;
	trie_t *ip_tree;         
};

static int IsValidMask(unsigned int mask, size_t *mask_height);
static int IpStringToInt(const char *ip,unsigned int *buffer);
static void IpIntToString(char *ip_str,unsigned int *ip_un);

dhcp_t *DHCPCreate(const char *subnet_id, const char *subnet_mask)
{
	dhcp_t *dhcp = NULL;
	int is_valid_ip = TRUE;
	unsigned int saved_ip[SYSTEM_IP] = {RESERVED_IP_1,RESERVED_IP_2, RESERVED_IP_3};
	unsigned int givven_path = 0;
	trie_status_t insert_status = TRIE_SUCCESS;
	size_t i = 0;
	
	assert(NULL != subnet_id);
	assert(NULL != subnet_mask);
	
	
	dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	
	if(NULL == dhcp)
	{
		
		return NULL;
	}
	
	is_valid_ip = IpStringToInt(subnet_id,&dhcp->subnet_id);
	if (!is_valid_ip)
	{
		free(dhcp);
		return NULL;
	}
	
	is_valid_ip = IpStringToInt(subnet_mask,&dhcp->submask);
	if (!is_valid_ip || !IsValidMask(dhcp->submask, &dhcp->tree_height))
	{
		free(dhcp);
		return NULL;
	}
	
	dhcp->subnet_id &= dhcp->submask;
	dhcp->ip_tree = TrieCreate(dhcp->tree_height);
	
	
	for (i = 0; i < SYSTEM_IP && TRIE_SUCCESS == insert_status; ++i)
	{
		saved_ip[i] = ((saved_ip[i] << (dhcp->tree_height - IPV4_SIZE)) >>(dhcp->tree_height - IPV4_SIZE));/*sef off mask bits*/
		saved_ip[i] |= dhcp->subnet_id; 							/*replace mask bits with net_id bits */
		insert_status =  TrieCreatePath(dhcp->ip_tree, saved_ip[i], &givven_path);	
		if (saved_ip[i] != givven_path)
		{
			DHCPDestroy(dhcp);
			return NULL;
		}	
	}
	
	if (TRIE_SUCCESS != insert_status)
	{
		DHCPDestroy(dhcp);
		return NULL;
	}
	
	return dhcp;
}

static int IpStringToInt(const char *ip,unsigned int *buffer)
{
	int is_valid_ip = 0;
	unsigned int temp = 0; 
	is_valid_ip = inet_pton(AF_INET,ip, &temp);
	*buffer = ntohl(temp); /*fix endian */
	
	return is_valid_ip;
}

static void IpIntToString(char *ip_str,unsigned int *ip_un)
{
	unsigned int temp = 0; 
	
	temp = ntohl(*ip_un);
	inet_ntop(AF_INET, &temp, ip_str, INET_ADDRSTRLEN);
}
\
static int IsValidMask(unsigned int mask, size_t *mask_height)
{
	size_t height = 0;
	
	for(height = IPV4_SIZE; 0 < height && (mask & 0x80000000) != 0; --height)
	{
		mask <<= 1;
	}
	
	*mask_height = height; /*height of the trie */
	return (height < IPV4_SIZE - 2 && height > 2 && mask == 0);
}


void DHCPDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);
	
	TrieDestroy(dhcp->ip_tree);
	memset(dhcp, 0, sizeof(dhcp_t));
	free(dhcp);
}


dhcp_status_t DHCPAllocIP(dhcp_t *dhcp, const char *ip, char *buffer)
{
	trie_status_t insert_status = TRIE_SUCCESS;
	unsigned int ip_in_big_endian_order = 0;
	unsigned int requested_ip = 0;
	unsigned int givven_path = 0;
	int is_valid_ip = TRUE;
			
	assert(NULL != dhcp);
	assert(NULL != buffer);
	
	if (TrieIsFull(dhcp->ip_tree))
	{
		return DHCP_IS_FULL_ERR;
	}
	
	is_valid_ip = IpStringToInt(ip,&requested_ip);
	if (!is_valid_ip || (requested_ip & dhcp->submask) != dhcp->subnet_id)
	{
		return DHCP_ALLOC_WRONG_NET;
	}
	
	insert_status = TrieCreatePath(dhcp->ip_tree, requested_ip, &givven_path);
	
	
	switch (insert_status)
	{
		case TRIE_SUCCESS:
			
			IpIntToString(buffer,&givven_path);
			
			return DHCP_ALLOC_SUCCESS;
				
		case TRIE_ALLOCATION_FAIL:
			return DHCP_ALLOC_FAIL;
	}
}


dhcp_status_t DHCPFreeIP(dhcp_t *dhcp, const char *ip_to_free)
{
	int is_valid_ip = TRUE;
	unsigned int ip_to_remove = 0;
	unsigned int ip_in_big_endian_order = 0;
	unsigned int saved_ip[SYSTEM_IP] = {RESERVED_IP_1,RESERVED_IP_2, RESERVED_IP_3};
	trie_status_t remove_status = TRIE_SUCCESS;
	dhcp_status_t status_lut[2] = {DHCP_ALLOC_SUCCESS,DHCP_ALLOC_DOUBLE_FREE};
	size_t i = 0;
	
	assert(NULL != dhcp);
	assert(NULL != ip_to_free);
	
	
		
	is_valid_ip = inet_pton(AF_INET,ip_to_free, &ip_in_big_endian_order);
	ip_to_remove = ntohl(ip_in_big_endian_order);
	if (!is_valid_ip || (ip_to_remove & dhcp->submask) != dhcp->subnet_id)
	{
		return DHCP_ALLOC_WRONG_NET;
	}
	
	for (i = 0; i < SYSTEM_IP ; ++i)
	{
		saved_ip[i] = ((saved_ip[i] << (dhcp->tree_height - IPV4_SIZE)) >>(dhcp->tree_height - IPV4_SIZE));/*sef off mask bits*/
		saved_ip[i] |= dhcp->subnet_id;
		if (ip_to_remove == saved_ip[i])
		{
			return DHCP_ALLOC_DOUBLE_FREE;
		} 
	}
		
	
	remove_status = TrieRemovePath(dhcp->ip_tree,  ip_to_remove);
	
	return status_lut[remove_status == TRIE_DOUBLE_FREE];
}

size_t DHCPCountFreeIP(const dhcp_t *dhcp)
{
	assert(NULL != dhcp);
	return TrieCountFreeLeafs(dhcp->ip_tree);
}
