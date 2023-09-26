//UDP 서버
//22112151 김나은
//soc2
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define MAX_BUF 1000

int main() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Error in starting up Winsock\n"); //에러메세지 출력
        return -1;
    }
    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0); //소켓 정의하기
    SOCKADDR_IN serverAdd;
    ZeroMemory(&serverAdd, sizeof(serverAdd));
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_port = htons(50000); //포트 번호를 50000번으로 지정해줌
    serverAdd.sin_addr.s_addr = INADDR_ANY; // 모든 IP 주소에서 수신

    if (bind(s, (SOCKADDR*)&serverAdd, sizeof(serverAdd)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(s);
        WSACleanup();
        return -1;
    }

    while (true) {
        SOCKADDR_IN clientInfo; // 정보를 저장할 구조체이다 
        int clientAddrLen = sizeof(clientInfo); //주소 길이의 변수이다 

        char recv_buf[MAX_BUF]; // 수신용 버퍼
        int pkt_length = recvfrom(s, recv_buf, MAX_BUF, 0, (SOCKADDR*)&clientInfo, &clientAddrLen); // 데이터 수신

        char send_buf[MAX_BUF] = "Hi, Client. Current time is ..."; //메세지를 어떻게 보낼 것인지 
        sendto(s, send_buf, 31, 0, (SOCKADDR*)&clientInfo, sizeof(clientInfo));

        // 클라이언트 정보를 서버에서 출력
        char clientIP[INET_ADDRSTRLEN]; // 클라이언트 문자열 버퍼
        inet_ntop(AF_INET, &(clientInfo.sin_addr), clientIP, INET_ADDRSTRLEN);
        printf(" %s ,%d\n", clientIP, ntohs(clientInfo.sin_port)); // 클라이언트 IP 주소 출력
        // 클라이언트 포트 번호 출력

        for (int i = 0; i < pkt_length; i++) {
            printf("%c", recv_buf[i]);// 출력해주기 
        }
        printf("\n");
    }

    closesocket(s); //닫아주기
    WSACleanup();

    return 0;
}


