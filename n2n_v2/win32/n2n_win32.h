/*

	(C) 2007-09 - Luca Deri <deri@ntop.org>

*/

#ifndef _N2N_WIN32_H_
#define _N2N_WIN32_H_

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <winsock2.h>
#include <windows.h>

#include "wintap.h"

#include "getopt.h"

typedef unsigned long in_addr_t;
typedef __int8 int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
typedef int ssize_t;

#define EAFNOSUPPORT   WSAEAFNOSUPPORT 
#define MAX(a,b) (a > b ? a : b)
#define MIN(a,b) (a < b ? a : b)
typedef unsigned int u_int32_t;
typedef unsigned short u_int16_t;
typedef unsigned char u_int8_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;

#define snprintf _snprintf
#define strdup _strdup

#define socklen_t int

#define ETH_ADDR_LEN 6
/*                                                                                                                                                                                     
 * Structure of a 10Mb/s Ethernet header.                                                                                                                                              
 */
struct ether_hdr
{
    uint8_t  dhost[ETH_ADDR_LEN];
    uint8_t  shost[ETH_ADDR_LEN];
    uint16_t type;                /* higher layer protocol encapsulated */
};

typedef struct ether_hdr ether_hdr_t;

/* ************************************* */

struct ip {
#if BYTE_ORDER == LITTLE_ENDIAN
        u_char  ip_hl:4,                /* header length */
                ip_v:4;                 /* version */
#else
        u_char  ip_v:4,                 /* version */
                ip_hl:4;                /* header length */
#endif
        u_char  ip_tos;                 /* type of service */
        short   ip_len;                 /* total length */
        u_short ip_id;                  /* identification */
        short   ip_off;                 /* fragment offset field */
#define IP_DF 0x4000                    /* dont fragment flag */
#define IP_MF 0x2000                    /* more fragments flag */
#define IP_OFFMASK 0x1fff               /* mask for fragmenting bits */
        u_char  ip_ttl;                 /* time to live */
        u_char  ip_p;                   /* protocol */
        u_short ip_sum;                 /* checksum */
        struct  in_addr ip_src,ip_dst;  /* source and dest address */
};


/* ************************************* */

typedef struct tuntap_dev {
	HANDLE device_handle;
	char *device_name;
	char *ifName;
	OVERLAPPED overlap_read, overlap_write;
	u_int8_t      mac_addr[6];
	u_int32_t     ip_addr, device_mask;
	u_int         mtu;
} tuntap_dev;

#define index(a, b) strchr(a, b)


#endif