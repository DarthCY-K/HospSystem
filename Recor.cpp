// Recor.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "fetche.h"

//��Ҫ���͵��ʼ�����                                           �������From��Toֻ�������ʼ�����ʾ�ģ�  
char EmailContents[] =
"From:DarthCYͼ����Ϣ����ϵͳ\n"
"To:�û�%s\r\n"             //����ֻ��˵���ռ��ˣ����������)  
"Subject:�һ�����\r\n\r\n"               //�ʼ�����  
"�û�%s��������Ȩ����%ld\n";                   //�ʼ�����  

//�����EncodeBase64��������Ͳ��г�����  
//�����ConvertToBase64��������Ͳ��г�����  

void EmailSystem(int argc, char* argv[])
{
	system("color 4e");
	char buf[1500];
	char login[128];
	char pass[128];
	ZeroMemory(buf, 1500);
	ZeroMemory(login, 128);
	ZeroMemory(pass, 128);
	//����Winsock��  
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	//����TCP�׽���  
	SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN dest;
	//�˿�25  
	dest.sin_port = htons(25);//587Ҳ����  
	dest.sin_family = AF_INET;
	//��ȡsmtp.qq.com�����������������IP��ַ  
	hostent* hptr = gethostbyname("smtp.qq.com");
	memcpy(&dest.sin_addr.S_un.S_addr, hptr->h_addr_list[0], hptr->h_length);
	//������Ѷ���ʼ�SMTP������  
	int ok = connect(sockfd, (SOCKADDR*)& dest, sizeof(SOCKADDR));
	if (ok != 0)
		exit(0);
	//����������������û����,����Ϊ�����˵ķ�������������������  
	sprintf_s(buf, 1500, "EHLO Aaron-PC\r\n");
	send(sockfd, buf, strlen(buf), 0);
	//���շ�������Ӧ  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "QQ SMTP Server Say: \r\n" << buf << endl;
	//������ȫ�����Э�飨TLS��  
	//�����STARTTLS�ո�ĺ���Ҫ��һЩ�ַ�����,���ﲻ�Ǻܶ�,����Ϳ�����.  
	sprintf_s(buf, 1500, "STARTTLS a\r\n");
	send(sockfd, buf, strlen(buf), 0);
	//���շ�������Ӧ  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "QQ SMTP Server Say: \r\n" << buf << endl;
	//������֤�����͸���������η��������˺ź����루�˺������ʹ��Base64���룩  
	sprintf_s(buf, 1500, "AUTH LOGIN\r\n");
	send(sockfd, buf, strlen(buf), 0);
	//���շ�������Ӧ  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Auth Login Receive:\r\n " << buf << endl;
	//����QQ�˺�
	ZeroMemory(buf, 1500);
	sprintf_s(buf, 1500, "452710557@qq.com");//��������˺�  
	//��QQ�˺�ת��ΪBase64�����ٷ���  
	EncodeBase64(login, buf, strlen(buf));
	sprintf_s(buf, 1500, "%s\r\n", login);
	send(sockfd, buf, strlen(buf), 0);
	cout << "Base64 UserName: " << buf << endl;
	//���շ�������Ӧ  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "User Login Receive: \r\n" << buf << endl;
	//������Կ���൱��QQ����,������Ĳ���õ���  
	sprintf_s(buf, 1500, "qkwldxmuqxypbjdj");  //QQ������Ȩ��
	//����Կת��ΪBase64�����ٷ���  
	EncodeBase64(pass, buf, strlen(buf));
	sprintf_s(buf, 1500, "%s\r\n", pass);
	send(sockfd, buf, strlen(buf), 0);
	cout << "Base64 Password:\r\n " << buf << endl;
	//���շ�������Ӧ  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Send Password Receive:\r\n " << buf << endl;
	//����MAIL FROM����ָ��������  
	ZeroMemory(buf, 1500);
	sprintf_s(buf, 1500, "MAIL FROM: <mckjsy@qq.com>\r\n");
	send(sockfd, buf, strlen(buf), 0);
	//���շ�������Ӧ  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Set Mail From Receive:\r\n " << buf << endl;
	//����һ������RCPT TO����ָ���ռ���   
	sprintf_s(buf, 1500, "RCPT TO:<%s>\r\n", "452710557@qq.com"); //�ռ���
	send(sockfd, buf, strlen(buf), 0);
	//���շ�������Ӧ  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Tell Sendto Receive: \r\n" << buf << endl;
	//����һ��DATA�����ʾ׼����ʼ�����ʼ�����  
	sprintf_s(buf, 1500, "DATA\r\n");
	send(sockfd, buf, strlen(buf), 0);
	//���շ�������Ӧ  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Send Mail Prepare Receive: \r\n" << buf << endl;
	//�����ʼ�����,��ʽ����\r\n.\r\n��Ϊ�������  
	sprintf_s(buf, 1500, "%s\r\n.\r\n", EmailContents);    //�ʼ�������  
	send(sockfd, buf, strlen(buf), 0);
	//���շ�������Ӧ  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Send Mail Receive: \r\n" << buf << endl;
	//ʹ��QUIT�����˳�          
	sprintf_s(buf, 1500, "QUIT\r\n");
	send(sockfd, buf, strlen(buf), 0);
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Quit Receive: " << buf << endl;
	//������  
	closesocket(sockfd);
	WSACleanup();
	getchar();

	return;
}


struct Base64Date6
{
	unsigned int d4 : 6;
	unsigned int d3 : 6;
	unsigned int d2 : 6;
	unsigned int d1 : 6;
};


//ת��ΪBase64���뺯��  
void EncodeBase64(char* dbuf, char* buf128, int len)
{   //����1��������Base64����Ļ�����   ����2��Ҫת�����ַ���������  ����3��Ҫת�����ַ�������
	struct Base64Date6* ddd = NULL;
	int           i = 0;
	char          buf[256] = { 0 };
	char* tmp = NULL;
	char          cc = '\0';

	memset(buf, 0, 256);
	strcpy_s(buf, 256, buf128);
	for (i = 1; i <= len / 3; i++)
	{
		tmp = buf + (i - 1) * 3;
		cc = tmp[2];
		tmp[2] = tmp[0];
		tmp[0] = cc;
		ddd = (struct Base64Date6*)tmp;
		dbuf[(i - 1) * 4 + 0] = ConvertToBase64((unsigned int)ddd->d1);
		dbuf[(i - 1) * 4 + 1] = ConvertToBase64((unsigned int)ddd->d2);
		dbuf[(i - 1) * 4 + 2] = ConvertToBase64((unsigned int)ddd->d3);
		dbuf[(i - 1) * 4 + 3] = ConvertToBase64((unsigned int)ddd->d4);
	}
	if (len % 3 == 1)
	{
		tmp = buf + (i - 1) * 3;
		cc = tmp[2];
		tmp[2] = tmp[0];
		tmp[0] = cc;
		ddd = (struct Base64Date6*)tmp;
		dbuf[(i - 1) * 4 + 0] = ConvertToBase64((unsigned int)ddd->d1);
		dbuf[(i - 1) * 4 + 1] = ConvertToBase64((unsigned int)ddd->d2);
		dbuf[(i - 1) * 4 + 2] = '=';
		dbuf[(i - 1) * 4 + 3] = '=';
	}
	if (len % 3 == 2)
	{
		tmp = buf + (i - 1) * 3;
		cc = tmp[2];
		tmp[2] = tmp[0];
		tmp[0] = cc;
		ddd = (struct Base64Date6*)tmp;
		dbuf[(i - 1) * 4 + 0] = ConvertToBase64((unsigned int)ddd->d1);
		dbuf[(i - 1) * 4 + 1] = ConvertToBase64((unsigned int)ddd->d2);
		dbuf[(i - 1) * 4 + 2] = ConvertToBase64((unsigned int)ddd->d3);
		dbuf[(i - 1) * 4 + 3] = '=';
	}
	return;
}



//��������ĺ���  
char ConvertToBase64(char uc)
{
	if (uc < 26)
	{
		return 'A' + uc;
	}
	if (uc < 52)
	{
		return 'a' + (uc - 26);
	}
	if (uc < 62)
	{
		return '0' + (uc - 52);
	}
	if (uc == 62)
	{
		return '+';
	}
	return '/';
}