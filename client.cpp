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

int main(int argc,char *argv[]) {
	int sockfd, num;
	char buf [MẠ̣̣̣̣X̣DATASIZE];
	struct hostent *he;
	struct sockaddr_in server;

	if(argc != 2){
		printf("ip%s\n",argv[0]);
		return 1;
	}

	if( (he = gethostbyname(argv[1])) == NULL){
		printf("");
		return 1;
	}

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket() error.");
		return 1;
	}

	bzero(&server, sizeof(server));

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	int opt = SO_REUSEADDR;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))
			== -1) {
		perror("setsockopt() error ");
		return 1;
	}

	if (bind(listenfd, (struct sockaddr *) &server, sizeof(server)) == -1) {
		cout << server.sin_addr.s_addr << endl;
		cout << listenfd << endl;
		perror("bind() error");
		return 1;
	}
	cout << "bind finish" << endl;
	if (listen(listenfd, BACKLOG) == -1) {
		perror("listen() error");
		return 1;
	}
	cout << "listen finish" << endl;
	addrlen = sizeof(client);

	if ((connectfd = accept(listenfd, (struct sockaddr *) &client, &addrlen))) {
		perror("accept() error\n");
		return 1;
	}
	cout << "accept finish" << endl;
	printf("Client's ip is %s,port is %d\n", inet_ntoa(client.sin_addr),
			htons(client.sin_port));
	return 0;
}
