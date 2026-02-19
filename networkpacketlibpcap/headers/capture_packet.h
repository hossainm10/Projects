#ifndef CAPTURE_PACKET_H
#define CAPTURE_PACKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>

#define MAX_PACKET_SIZE 65535
#define ETHERNET_HEADER_SIZE 14
#define IP_HEADER_MIN_SIZE 20
#define TCP_HEADER_MIN_SIZE 20
#define UDP_HEADER_MIN_SIZE 8
#define PCAP_ERRBUF_SIZE 256
typedef struct{
	uint8_t data[MAX_PACKET_SIZE];
	size_t length;
	struct timeval timestamp;
	
} packet_buffer_t;

typedef enum{
	PROTO_TCP=6,
	PROTO_UDP=17,
	PROTO_ICMP=14,
	PROTO_UNKNOWN=0

} protocol_type_t;


typedef struct{
	char src_ip[16];
	char dst_ip[16];
	uint16_t src_port;
	uint16_t dst_port;
	protocol_type_t protocol;
	size_t payload_size;
} packet_info_t;

#endif
