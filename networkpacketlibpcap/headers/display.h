#ifndef DISPLAY_H
#define DISPLAY_H


#include "capture_packet.h"
void display_packet_raw(packet_buffer_t *buffer);
void display_packet_info(packet_info_t *info, size_t packet_num);
void display_packet_summary(packet_info_t *info, size_t packet_num);
void display_packet_full(packet_buffer_t *buffer, packet_info_t *info, size_t packet_num);
void display_statistics(size_t total_packets, size_t tcp_count, size_t udp_count, size_t other_count);

#endif
