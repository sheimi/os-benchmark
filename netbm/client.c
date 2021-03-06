/************
 * client.c
 * sending packets
 ***************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <memory.h>
#include "netbm.h"

void error(const char *msg)
{
	fprintf(stderr, "%s", msg);
	exit(0);
}

void rtt_benchmark(int sockfd)
{
	char buf[MAXLINE];
	char *str = "abc";
	int i, n;
	cpu_cycle ts1, ts2;

	for (i = 0; i < LOOPTIMES; i++) {
		ts1 = rdtsc();
		n = write(sockfd, str, strlen(str));
		if (n < 0)
			error("ERROR writing to socket\n");

		n = read(sockfd, buf, MAXLINE);
		if (n < 0)
			error("ERROR reading from socket\n");
		ts2 = rdtsc();
		printf("RTT = %llu\n", ts2-ts1);
		/*printf("Response from server:\n");
		  write(STDOUT_FILENO, buf, n);
		  write(STDOUT_FILENO, "\n", 1);
		 */
	}
}

void bw_benchmark(int sockfd)
{
	char buf[MAXLINE];
	char *str;
	int i, j, n;
	cpu_cycle ts1, ts2, ts3;

	str = (char *)malloc(DATASIZE);
	memset(str, 1, DATASIZE);
	for (i = 0; i < LOOPTIMES; i++) {
		ts1 = rdtsc();
		for(j = 0; j < TRANSTIMES; j++) {
			//n = write(sockfd, str, DATASIZE);
			n = send(sockfd, str, DATASIZE, 0);
			if (n < 0)
				error("ERROR writing to socket\n");
			//printf("Send %d bytes\n", n);

		}
		ts3 = rdtsc();
		printf("After send time is = %llu\n", ts3-ts1);
		//n = read(sockfd, buf, MAXLINE);
		n = recv(sockfd, buf, DATASIZE, 0);
		if (n < 0)
			error("ERROR reading from socket\n");

		ts2 = rdtsc();
		printf("Send %d * %d Byptes = %llu\n", 
				TRANSTIMES, DATASIZE, ts2-ts1);
		/*printf("Response from server:\n");
		  write(STDOUT_FILENO, buf, n);
		  write(STDOUT_FILENO, "\n", 1);
		 */
	}
}
int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	char *servip, *str;
	int sockfd, n;
	cpu_cycle ts1, ts2;

	if (argc < 2)
		error("usage: client serverip\n");
	servip = argv[1];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket\n");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, servip, &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);

	printf("Client start connections...\n");
	if (connect(sockfd, (struct sockaddr *)&servaddr, 
				sizeof(servaddr)) < 0) 
		error("ERROR connecting\n");

	//rtt_benchmark(sockfd);
	//bw_benchmark(sockfd);

	//close(sockfd);
	ts1 = rdtsc();
	shutdown(sockfd, SHUT_RDWR);
	ts2 = rdtsc();
	printf("client shutdown = %llu\n", ts2-ts1);
	return 0;
}
