#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("usage: %s ip port\n", argv[0]);
		exit(1);
	}

	/*����1:����socket*/
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		perror("socket error");
		exit(1);
	}

	/*����2:����recvfrom��sendto�Ⱥ����ͷ�����˫��ͨ��*/
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET; //ipv4
	server_addr.sin_port = htons(atoi(argv[2])); //port
	inet_pton(AF_INET, argv[1], &server_addr.sin_addr.s_addr); //ip address

	if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("connect error");
		exit(1);
	}


	char buffer[1024] = "hello gmqh!";
	//��������������ݱ���
	//���ͷ�ʽ1:
	/*if (sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
		perror("sendto error");
		exit(1);
	}*/
	//���ͷ�ʽ2:
	if (send(sockfd, buffer, sizeof(buffer), 0) < 0) {
		perror("send error");
		exit(1);
	}
	else {
		//���ܷ������˷��͵����ݱ���
		int size;
		memset(buffer, 0, sizeof(buffer));
		if ((size = recv(sockfd, buffer, sizeof(buffer), 0)) < 0) {
			perror("recv error");
			exit(1);
		}
		else
		{
			printf("%s", buffer);
		}
	}
	close(sockfd);

	return 0;
}