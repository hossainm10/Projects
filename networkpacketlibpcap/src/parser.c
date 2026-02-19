#include "parser.h"
int parse_ethernet(uint8_t *data,size_t *offset){
	*offset = ETHERNET_HEADER_SIZE;
	printf("Parsed Ethernet!\n");
	return 0;
}

int parse_ip(uint8_t *data, size_t offset, packet_info_t *info){
	(void)data;
	struct iphdr *ip= (struct iphdr *)(data+offset);

	struct in_addr src;
	src.s_addr=ip->saddr;
	strncpy(info->src_ip, inet_ntoa(src), sizeof(info->src_ip)-1);
	info->src_ip[sizeof(info->src_ip) -1] ='\0';


	struct in_addr dst;
        dst.s_addr=ip->daddr;
        strncpy(info->dst_ip, inet_ntoa(dst), sizeof(info->dst_ip)-1);
        info->dst_ip[sizeof(info->dst_ip) -1] ='\0';
	
	info->protocol = ip->protocol;

	printf("Succesfully parsed IP\n");
	
	return 0;
	
}

int parse_tcp(uint8_t *data, size_t offset, packet_info_t *info){
	struct tcphdr *tcp= (struct tcphdr *)(data+offset);
	
	info->src_port= ntohs(tcp->source);
	info->dst_port= ntohs(tcp->dest);

	printf("Parsed TCP\n");
	
	return 0;
}

int parse_udp(uint8_t *data, size_t offset, packet_info_t *info){
	struct udphdr *udp= (struct udphdr *)(data+offset);

	info->src_port = ntohs(udp->source);
	info->dst_port= ntohs(udp->dest);
	
	printf("Parsed UDP\n");

	return 0;
}

int parse_packet(packet_buffer_t *buffer, packet_info_t *info){
	if(!buffer || !info){
		printf("Error, couldn't parsed\n");
		return -1;
	}

	memset(info, 0, sizeof(packet_info_t));

	size_t offset=0;

	if(parse_ethernet(buffer->data, &offset)<0){
		return -1;
	}

	if(offset + sizeof(struct iphdr) > buffer-> length){
		return -1;
	}
	if(parse_ip(buffer->data, offset, info)<0){
		return -1;
	}
	struct iphdr *ip= (struct iphdr *)(buffer->data + offset);
	size_t ip_header_len= ip->ihl *4;
	offset+=ip_header_len;

	switch(info->protocol){
		case PROTO_TCP:
			if(offset+ sizeof(struct tcphdr) <= buffer->length){
				parse_tcp(buffer->data, offset, info);
				offset+=TCP_HEADER_MIN_SIZE;
			}
			break;
		case PROTO_UDP:
			if(offset+ sizeof(struct udphdr) <= buffer->length){
                                parse_udp(buffer->data, offset, info);
                                offset+=UDP_HEADER_MIN_SIZE;
                        }
                        break;
		case PROTO_ICMP:
			info->src_port=0;
			info->dst_port=0;
			break;
		default :
			info->protocol= PROTO_UNKNOWN;
			break;

	}
	info->payload_size= (buffer->length>offset) ? (buffer->length-offset): 0;
	
	return 0;	
}      

const char* get_protocol_name(protocol_type_t protocol){
	switch(protocol){
		case PROTO_TCP:
			return "TCP";
		case PROTO_UDP:
			return "UDP";
		case PROTO_ICMP:
			return "ICMP";
		default:
			return "OTHER";
	}
		
}
