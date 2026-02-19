#include "capture.h"
#include "parser.h"
#include "display.h"
#include <signal.h>



capture_context_t global_ctx;

size_t tcp_count= 0;
size_t udp_count =0;
size_t other_count=0;
size_t packet_counter=0;

void signal_handler(int signum){
	printf("\nRecieved signal %d, stopping capture...\n:", signum);
	capture_stop(&global_ctx);
}

void packet_callback(packet_buffer_t *buffer){

	packet_info_t info;

	packet_counter++;

	if(parse_packet(buffer, &info) ==0){
		switch(info.protocol){
			case PROTO_TCP:
				tcp_count++;
				break;
			case PROTO_UDP:
				udp_count++;
				break;
			default:
				other_count++;
				break;
		}
		display_packet_summary(&info, packet_counter);
	
		if(packet_counter<=3){
			display_packet_info(&info, packet_counter);
		}
	
	}else{
		fprintf(stderr, "Falied to parse packet: %zu\n", packet_counter);
	}
}

void print_usage(const char *program_name){
	printf("Usage %s <interface> [max_packets] [filter]\n", program_name);
	printf("  interface:   Network interface (eth0, wlan0)\n)");
	printf("  max_packets: Max packets to capture (0 = unlimited)\n");
	printf("  filter: 	BPF filter (EX: 'TCP and Port 80')\n");
	printf("\nExamples\n");
	printf("  %s eth0 100\n",program_name);
	printf("  %s wlan 0 \'tcp'\n",program_name);
	printf("  %s eth0 50 'port 443'\n", program_name);

}

int main(int argc, char *argv[]){

	const char *interface;
	size_t max_packets=0;
	const char *filter= NULL;

	if(argc < 2){
		print_usage(argv[0]);
		return 1;	
	}
	interface= argv[1];

	if(argc>=3){
		max_packets=atoi(argv[2]);
	}
	if(argc>=4){
		filter= argv[3];
	}
	printf("==== Network Packet Sniffer Tool(With libpcap) ====\n");
	printf("Interface: %s\n",interface);
	printf("Max packets: %s\n", max_packets > 0 ? argv[2]: "unlimited");

	if(filter){
		printf("Filter: %s\n",filter);
	}

	printf("\n");

	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);

	if(capture_init(&global_ctx, interface)<0){
	
		fprintf(stderr, "Failed to intialize packet capture\n");
		capture_cleanup(&global_ctx);
		return 1;
	}

	if(filter){
		if(capture_set_filter(&global_ctx,filter)<0){
			fprintf(stderr,"Failed to set filter\n");
			capture_cleanup(&global_ctx);
			return 1;
		}
	}

	int captured= capture_start(&global_ctx, &packet_callback, max_packets);

	display_statistics(packet_counter, tcp_count,udp_count, other_count);
	capture_cleanup(&global_ctx);

	printf("\n Capture Complete. Total Packets: %d\n", captured);

	return 0;

	

}
