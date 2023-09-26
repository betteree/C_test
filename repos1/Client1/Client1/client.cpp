//UDP Ŭ���̾�Ʈ
//22112151 �質��
//soc2
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h> // ���̺귯�� ����
#pragma comment(lib,"ws2_32.lib")
#define MAX_BUF 1000 // �ִ� ���� ������ ����

int main() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { 
        printf("Error in starting up Winsock\n"); //�����޼���
        return -1;
    }

    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0); //���� �����ϱ� 
    SOCKADDR_IN serverAdd;
    ZeroMemory(&serverAdd, sizeof(serverAdd));
    serverAdd.sin_family = AF_INET;
    serverAdd.sin_port = htons(50000); // ��Ʈ ��ȣ ����
    inet_pton(AF_INET, "192.168.44.1", &(serverAdd.sin_addr.s_addr)); // ���� IP �ּ� �����ϱ� 
    // ���� ip�ּ� ������ֱ� 
    char serverIP[INET_ADDRSTRLEN]; // ���� �ּ� ������ ����
    inet_ntop(AF_INET, &(serverAdd.sin_addr), serverIP, INET_ADDRSTRLEN);
    printf("Server IP: %s\n", serverIP);

    char buf[MAX_BUF] = "Hello, UDP Time server!!"; //��µǴ� �޼��� 
    sendto(s, buf, 24, 0, (SOCKADDR*)&serverAdd, sizeof(serverAdd));

    char recv_buf[MAX_BUF]; //ĳ������
    SOCKADDR_IN cli;
    int cli_length = sizeof(cli); //����
    int pkt_length = recvfrom(s, recv_buf, MAX_BUF, 0, (SOCKADDR*)&cli, &cli_length); //���� 

    for (int i = 0; i < pkt_length; i++) //�ݺ���
    {
        printf("%c", recv_buf[i]); //������ֱ� 
    }
    printf("\n"); //����Ʈ���ֱ� 
     
    closesocket(s);//�ݱ�
    WSACleanup();

    return 0;
}
