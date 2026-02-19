#ifndef CAPTURE_H
#define CAPTURE_H

#include "capture_packet.h"
#include <pcap.h>
typedef struct {
	pcap_t *handle;
	char interface[16];
	bool is_running;
	size_t packets_captured;
	char errbuf[PCAP_ERRBUF_SIZE];


} capture_context_t;

int capture_init(capture_context_t *ctx, const char *interface);
int capture_packet(capture_context_t *ctx, packet_buffer_t *buffer);
int capture_start(capture_context_t *ctx, void(*callback)(packet_buffer_t *),size_t max_packets);
void capture_stop(capture_context_t *ctx);
void capture_cleanup(capture_context_t *ctx);
int capture_set_filter(capture_context_t *ctx, const char *filter_exp);
#endif
