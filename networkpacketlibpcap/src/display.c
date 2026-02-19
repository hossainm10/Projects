#include "display.h" 
#include "parser.h"
#include <ctype.h>
void display_packet_raw(packet_buffer_t *buffer){

	printf("\n==== Raw Packet Data ====\n");
	printf("Length: %zu bytes\n", buffer->length);

	for( size_t i=0; i< buffer->length ; i+=16){
		printf("%04zx: ", i);
		
		for(size_t j=0; j< 16;j++){
			if(i+j < buffer->length){
				printf("%02x ", buffer->data[i+j]);

			}else{
				printf("    ");
			}
			if (j==7){
				printf(" ");

			}
		}
		printf("  |");
		for(size_t j =0; j<16 && i+j < buffer->length;j++){
			unsigned char c = buffer->data[i+j];
			printf("%c", isprint((int)c) ? c : "-");
		}	
		printf("|\n");
	}



}

void display_packet_info(packet_info_t *info, size_t packet_num){
	printf("\n==== Packet #%zu ====\n", packet_num);
	printf("Protocol: %s\n", get_protocol_name(info->protocol));
	printf("Source Ip: %s\n", info->src_ip);
	if(info->dst_port >0){
		printf(":%u",info->src_port);
	}
	printf("\n");

	printf("Destination IP: %s", info->dst_ip);
	
	if(info->dst_port >0){
		printf(":%u\n",info->dst_port);
	}
	printf("Payload Size: %zu bytes\n", info->payload_size);

}


void display_packet_summary(packet_info_t *info, size_t packet_num){

	printf("[%4zu], %-5s %15s:%-5u -> %15s-%-5u (%zu bytes)\n",packet_num,
		get_protocol_name(info->protocol),
		info->src_ip,info->src_port, info->dst_ip, info->dst_port,
		info->payload_size);

}

void display_packet_full(packet_buffer_t *buffer, packet_info_t *info, size_t packet_num){
	printf("\n==== Packet %zu ====\n",packet_num);
	printf("TimestamL %ld.%.06ld\n", (long)buffer->timestamp.tv_sec, (long)buffer->timestamp.tv_usec);

	printf("Protocol: %s\n", get_protocol_name(info->protocol));
	printf("Source: %s:%u\n", info->src_ip, info->src_port);
	printf("Destination: %s:%u\n", info->dst_ip, info->dst_port);
	printf("Total Length: %zu bytes\n", buffer->length);
	printf("Payload Size: %zu bytes\n", info->payload_size);


}


void display_statistics(size_t total_packets, size_t tcp_count, size_t udp_count, size_t other_count){
	printf("\n==== Capture Statistics ====\n");
	printf("Total Packets: %zu\n", total_packets);

	if(total_packets>0){
		printf("TCP Packets: %zu (%.1f%%)\n", tcp_count, (tcp_count*100.0 / total_packets));
		printf("UDP Packers: %zu (%.1f%%)\n", udp_count, (udp_count*100.0/total_packets));
		printf("Other Packets: %zu (%.1f%%)\n", other_count, (other_count*100.0/other_count));
	}


}
