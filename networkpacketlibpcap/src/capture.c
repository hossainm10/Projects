#include "capture.h"
#include <string.h>
#include <stdio.h>
int capture_init(capture_context_t *ctx, const char *interface){
	if(!ctx || !interface){

		fprintf(stderr,"Invalid parameters\n");
		return -1;
	}

	strncpy(ctx->interface, interface, sizeof(ctx->interface) -1);

	ctx->handle=pcap_open_live(interface, MAX_PACKET_SIZE,1, 1000, ctx->errbuf);

	if (ctx->handle == NULL){
		fprintf(stderr, "Couldn't open device %s, %s\n",interface, ctx->errbuf);
		return -1;
	
	}
	ctx->is_running=false;
	ctx->packets_captured=0;
	printf("Packet capture initialized on the interface: %s\n", interface);
	return 0;
}


int capture_packet(capture_context_t *ctx, packet_buffer_t *buffer){


	if (!ctx || !buffer){
		fprintf(stderr, "Invalid Parameters\n");
		return -1;

	}

	struct pcap_pkthdr *header;
	const u_char *packet_data;
	
	int result = pcap_next_ex(ctx-> handle, &header, &packet_data);
	
	if (result == 1){
		if(header->caplen > MAX_PACKET_SIZE){
			fprintf(stderr,"Packet too large: %u bytes\n",header->caplen);
			return -1;
		}
		buffer->length=header->caplen;
		memcpy(buffer->data, packet_data,header->len);
		
		buffer->timestamp= header->ts;
		
		ctx->packets_captured++;
		return buffer->length;
	} else if(result == 0){
		return 0;
	}else if(result ==-1){
		fprintf(stderr, "Error reading packet: %s\n",pcap_geterr(ctx->handle));
		return -1;
	}else{
		fprintf(stderr, "Unexpected end of capture\n");
		return -1;

	}


}

int capture_start(capture_context_t *ctx, void(*callback)(packet_buffer_t*), size_t max_packets){

	if(!ctx || !callback){
	
		fprintf(stderr, "Invalid parameters\n");
		return -1;
	
	
	
	}

	ctx->is_running =0;
	packet_buffer_t buffer;
	size_t count =0;

	printf("Starting packet capture... (Press Ctrl+C to stop)\n");


	while(ctx->is_running){
		int result = capture_packet(ctx,&buffer);
		
		if (result > 0){
			callback(&buffer);
			count++;
	
		}	
		if (max_packets>0 && count >=max_packets){
		
			break;
		
		}else if (result <0){
			fprintf(stderr, "Error capturing packets\n");
			break;
		
		}
			
			
			
	}
	ctx->is_running=false;
	printf("\nCapture stopped. Total packets : %zu\n", count);
	return count;

}

void capture_stop(capture_context_t *ctx){


	if(ctx){
		ctx->is_running=false;
		if(ctx->handle){
		
			pcap_breakloop(ctx->handle);
		}
	
	}

}

void capture_cleanup(capture_context_t *ctx){
	if(ctx && ctx->handle){
		pcap_close(ctx->handle);
		ctx->handle=NULL;
		printf("Capture resources cleaned up\n");
	}

}

int capture_set_filter(capture_context_t *ctx , const char *filter_exp){

	if(!ctx || !ctx->handle || !filter_exp){
		fprintf(stderr,"invalid parameters to capture_set_filter\n");

	}
	struct bpf_program filter;

	if(pcap_compile(ctx->handle, &filter, filter_exp, 0, PCAP_NETMASK_UNKNOWN)==-1){
	
		fprintf(stderr,"Couldn't parse filter '%s': %s\n", filter_exp, pcap_geterr(ctx->handle));
		return -1;
	}

	if(pcap_setfilter(ctx->handle, &filter) == -1){
	
		fprintf(stderr, "Couldn't install filter '%s' : '%s'\n", filter_exp, pcap_geterr(ctx->handle));
		pcap_freecode(&filter);
		return -1;
	
	}
	pcap_freecode(&filter);
	printf("Applied filter: %s\n",filter_exp);
	return 0;


}

