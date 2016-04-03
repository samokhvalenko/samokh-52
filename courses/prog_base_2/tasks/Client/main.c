#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

#pragma comment(lib, "ws2_32.lib")

#define BUFMAX 1000

SOCKET createSocket(void){
	SOCKET recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (recvSocket == INVALID_SOCKET)
	{
		printf("CREATION SOCKET ERROR\n");
		exit(EXIT_FAILURE);
	}
	return recvSocket;
}

void connectToServer(SOCKET recvSocket, SOCKADDR_IN recvSockAddr){
	if (connect(recvSocket, (SOCKADDR*)&recvSockAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		printf("ERROR: socket could not connect\r\n");
		closesocket(recvSocket);
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void sendStartRequest(SOCKET recvSocket, const char* host_name){
	char request[200];
	sprintf(request, "GET /var/13 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);
	send(recvSocket, request, strlen(request), 0);
}

void receiveResponse(SOCKET recvSocket, char* buffer){
	int numrcv = recv(recvSocket, buffer, BUFMAX, 0);
	if (numrcv == SOCKET_ERROR)
	{
		printf("ERROR receive was unsuccessful\n");
		int status = closesocket(recvSocket);
		if (status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\n");
		status = WSACleanup();
		if (status == SOCKET_ERROR)
			printf("WSACleanup unsuccessful\n");
		exit(EXIT_FAILURE);
	}
}

void sendSecretRequest(SOCKET recvSocket, char* host_name, char* buffer){
	char secret[50];
	char request[200];
	strcpy(secret, strstr(buffer, "secret"));
	sprintf(request, "GET /var/13?%s HTTP/1.1\r\nHost:%s\r\n\r\n", secret, host_name);
	send(recvSocket, request, strlen(request), 0);
}

int calculateMaxStudentsOccurance(char* buffer){
    char *a[35],*pov[35];
    char* text;
    int i=0, j, k, num_of_words, pov_count[35], cop_num=0, d, sum = 0;

    text=strtok(buffer," ");

    while (text != NULL) {
        a[i] = text;
        text = strtok (NULL, " ");
        text = strtok (NULL, "\n");
        i++;
    }

    for(j=0; j<i; j++) {
        num_of_words=0;
        for(k = 0; k < i; k++) {
            if (strcmp(a[j], a[k]) == 0) {
            num_of_words++;
            }
        }
        if(num_of_words > 0) {
            pov[cop_num] = a[j];
            printf("%s\n", pov[cop_num]);
            pov_count[cop_num] = num_of_words;
            cop_num++;
        }
    }
    for(j = 0; j < cop_num; j++) {
        if(pov_count[j] > sum)
            sum = pov_count[j];
    }
	return sum;
}

void sendFinalPOST(SOCKET recvSocket, char* host_name, int sum){
	char data[30];
	char request[200];
	sprintf(data, "result=%d", sum);
	printf("Studet`s count: %d\n", sum);
	sprintf(request, "POST /var/13 HTTP/1.0\r\n" // magic starts here
		"Host: %s\r\n"
		"Content-type: application/x-www-form-urlencoded\r\n" // from stackoverflow, i don`t know what is this
		"Content-length: %d\r\n\r\n"
		"%s\r\n", host_name, strlen(data), data);
	send(recvSocket, request, strlen(request) + 1, 0);
}

int main(void) {
	WSADATA Data;
	SOCKADDR_IN recvSockAddr;
	SOCKET recvSocket;
	int status;
	int numrcv = 0;
	struct hostent * remoteHost;
	char * ip;
	const char * host_name = "pb-homework.appspot.com";
	char buffer[BUFMAX];
	memset(buffer, 0, BUFMAX);

	status = WSAStartup(MAKEWORD(2, 2), &Data);
	if (status != 0)
	{
		printf("ERROR WSAStartup\n");
		return 0;
	}

	remoteHost = gethostbyname(host_name);
	ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("IP: %s \n", ip);
	memset(&recvSockAddr, 0, sizeof(recvSockAddr));
	recvSockAddr.sin_port = htons(80);
	recvSockAddr.sin_family = AF_INET;
	recvSockAddr.sin_addr.s_addr = inet_addr(ip);

	recvSocket = createSocket();
	connectToServer(recvSocket, recvSockAddr);
	sendStartRequest(recvSocket, host_name);
	receiveResponse(recvSocket, buffer);
	sendSecretRequest(recvSocket, host_name, buffer);
	receiveResponse(recvSocket, buffer);

	printf("%s\n", buffer);
	int sum = calculateMaxStudentsOccurance(buffer);
	printf("\nServer response:\n%s\n", buffer);

	sendFinalPOST(recvSocket, host_name, sum);

	for (int i = strlen(buffer); i >= 0; i--)
		buffer[i] = '\0';

	receiveResponse(recvSocket, buffer);
	printf("\nServer response:\n\n%s\n", buffer);

	closesocket(recvSocket);
	return EXIT_SUCCESS;
}
