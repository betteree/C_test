//UDP ����
//22112151 �質��
//soc2
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#define MAX_BUF 1000

int main() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Error in starting up Winsock\n"); //�����޼��� ���
        return -1;
    }
    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0); //���� �����ϱ�
    SOCKADDR_IN serverAdd;
    ZeroMemory(&serverAdd, sizeof(serverAdd));
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_port = htons(50000); //��Ʈ ��ȣ�� 50000������ ��������
    serverAdd.sin_addr.s_addr = INADDR_ANY; // ��� IP �ּҿ��� ����

    if (bind(s, (SOCKADDR*)&serverAdd, sizeof(serverAdd)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(s);
        WSACleanup();
        return -1;
    }

    while (true) {
        SOCKADDR_IN clientInfo; // ������ ������ ����ü�̴� 
        int clientAddrLen = sizeof(clientInfo); //�ּ� ������ �����̴� 

        char recv_buf[MAX_BUF]; // ���ſ� ����
        int pkt_length = recvfrom(s, recv_buf, MAX_BUF, 0, (SOCKADDR*)&clientInfo, &clientAddrLen); // ������ ����

        char send_buf[MAX_BUF] = "Hi, Client. Current time is ..."; //�޼����� ��� ���� ������ 
        sendto(s, send_buf, 31, 0, (SOCKADDR*)&clientInfo, sizeof(clientInfo));

        // Ŭ���̾�Ʈ ������ �������� ���
        char clientIP[INET_ADDRSTRLEN]; // Ŭ���̾�Ʈ ���ڿ� ����
        inet_ntop(AF_INET, &(clientInfo.sin_addr), clientIP, INET_ADDRSTRLEN);
        printf(" %s ,%d\n", clientIP, ntohs(clientInfo.sin_port)); // Ŭ���̾�Ʈ IP �ּ� ���
        // Ŭ���̾�Ʈ ��Ʈ ��ȣ ���

        for (int i = 0; i < pkt_length; i++) {
            printf("%c", recv_buf[i]);// ������ֱ� 
        }
        printf("\n");
    }

    closesocket(s); //�ݾ��ֱ�
    WSACleanup();

    return 0;
}


