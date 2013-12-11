#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>

#define PORT 9100

int main (int argc, char *argv[])
{
	int sockfd, len, bytes_sent;
	struct hostent *host;
	struct sockaddr_in target_addr;
	char line[100];
	
	if (argc != 4)
	{
	printf("HP Printer Message Editor\n");
	printf("%s [Printer IP Address] \"String\" [rdy (ready message) or err (error message)]\n", argv[0]);
	printf("Message can be up to 16 characters long (32 on 2 line displays)\n");
	exit(1);
	}

	if ((host = gethostbyname(argv[1])) == NULL)
	{
		perror("gethostbyname");
		exit(1);
	}

	printf ("HP Printer Message Editor\n");
	printf ("Hostname:\t%s\n", argv[1]);
	printf ("Message:\t%s\n", argv[2]);

	target_addr.sin_family = host -> h_addrtype;
	target_addr.sin_port = htons(PORT);

	bcopy(host -> h_addr, (char *) &target_addr.sin_addr, host -> h_length);
	bzero(&(target_addr.sin_zero), 8);
	
	if ((sockfd=socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		exit(1);
	}

	printf ("Connecting...\n");
	
	if (connect(sockfd, (struct sockaddr *) &target_addr, sizeof(target_addr)) == -1)
	{
		perror("connect");
		exit(1);
	}
	if (argv[3] == "rdy")
	{
		strcpy(line, "\033%-12345X@PJL ERRMSG DISPLAY = \"");
		return 0;
	}
	else if (argv[3] == "err")
	{
		strcpy(line, "\033%-12345X@PJL RDYMSG DISPLAY = \"");
		return 0;
	}
	
	strncat(line, argv[2], 44);
	strcat(line, "\"\r\n\033%-12345X\r\n");
	bytes_sent = send(sockfd, line, strlen(line), 0);
	printf("Sent %d bytes\n", bytes_sent);
	close(sockfd);
}