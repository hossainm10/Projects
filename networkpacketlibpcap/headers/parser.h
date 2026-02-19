#ifndef PARSER_H 
#define PARSER_H

#include "capture_packet.h"
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

int parse_packet(packet_buffer_t *buffer, packet_info_t *info);
int parse_ethernet(uint8_t *data, size_t *offset);
int parse_ip(uint8_t *data, size_t offset, packet_info_t *info);
int parse_tcp(uint8_t *data, size_t offset, packet_info_t *info);
int parse_udp(uint8_t *data, size_t offset, packet_info_t *info);
const char* get_protocol_name(protocol_type_t protocol);

#endif
