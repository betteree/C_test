//UDP 클라이언트
//22112151 김나은
//soc2
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h> // 라이브러리 정의
#pragma comment(lib,"ws2_32.lib")
#define MAX_BUF 1000 // 최대 버퍼 사이즈 정의

int main() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { 
        printf("Error in starting up Winsock\n"); //에러메세지
        return -1;
    }

    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0); //소켓 정의하기 
    SOCKADDR_IN serverAdd;
    ZeroMemory(&serverAdd, sizeof(serverAdd));
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_port = htons(50000); // 포트 번호 설정
    inet_pton(AF_INET, "192.168.44.1", &(serverAdd.sin_addr.s_addr)); // 서버 IP 주소 설정하기 
    // 서버 ip주소 출력해주기 
    char serverIP[INET_ADDRSTRLEN]; // 서버 주소 저장할 버퍼
    inet_ntop(AF_INET, &(serverAdd.sin_addr), serverIP, INET_ADDRSTRLEN);
    printf("Server IP: %s\n", serverIP);

    char buf[MAX_BUF] = "Hello, UDP Time server!!"; //출력되는 메세지 
    sendto(s, buf, 24, 0, (SOCKADDR*)&serverAdd, sizeof(serverAdd));

    char recv_buf[MAX_BUF]; //캐릭터형
    SOCKADDR_IN cli;
    int cli_length = sizeof(cli); //길이
    int pkt_length = recvfrom(s, recv_buf, MAX_BUF, 0, (SOCKADDR*)&cli, &cli_length); //길이 

    for (int i = 0; i < pkt_length; i++) //반복문
    {
        printf("%c", recv_buf[i]); //출력해주기 
    }
    printf("\n"); //프린트해주기 
     
    closesocket(s);//닫기
    WSACleanup();

    return 0;
}
