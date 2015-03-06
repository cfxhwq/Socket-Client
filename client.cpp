/*
 * client.cpp
 *
 *  Created on: 2015年3月4日
 *      Author: mark
 */

//============================================================================
// Name        : server.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <stdio.h>
#include <iostream>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
using namespace std;

#define PORT 1234

#define MAXDATASIZE 100

int main(int argc, char *argv[]) {
	int sockfd, num;
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in server;

	if (argc != 2) {
		printf("ip%s\n", argv[1]);
		return 1;
	}

	if ((he = gethostbyname(argv[1])) == NULL) {
		printf("gethostbyname() error");
		return 1;
	} else {
		printf("hostname:%s", he->h_name);
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() error.");
		return 1;
	}

	bzero(&server, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr = *((struct in_addr *) he->h_addr);
	cout << endl << server.sin_addr.s_addr << endl;

	if (connect(sockfd, (struct sockaddr *) &server, sizeof(server)) == -1) {
		perror("connect() error.");
		return 1;
	}

	if ((num = recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
		perror("recv() error.");
		return 1;
	}

	buf[num] = '\0';
	printf("server: %sa",buf);

	close(sockfd);
	return 0;
}
