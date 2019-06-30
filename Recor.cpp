// Recor.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "fetche.h"

//将要发送的邮件内容                                           （这里的From和To只用于在邮件上显示的）  
char EmailContents[] =
"From:DarthCY图书信息管理系统\n"
"To:用户%s\r\n"             //这里只是说明收件人（可以乱填的)  
"Subject:找回密码\r\n\r\n"               //邮件标题  
"用户%s，您的授权码是%ld\n";                   //邮件内容  

//上面的EncodeBase64函数这里就不列出来了  
//上面的ConvertToBase64函数这里就不列出来了  

void EmailSystem(int argc, char* argv[])
{
	system("color 4e");
	char buf[1500];
	char login[128];
	char pass[128];
	ZeroMemory(buf, 1500);
	ZeroMemory(login, 128);
	ZeroMemory(pass, 128);
	//加载Winsock库  
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	//创建TCP套接字  
	SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN dest;
	//端口25  
	dest.sin_port = htons(25);//587也可以  
	dest.sin_family = AF_INET;
	//获取smtp.qq.com服务器域名所代表的IP地址  
	hostent* hptr = gethostbyname("smtp.qq.com");
	memcpy(&dest.sin_addr.S_un.S_addr, hptr->h_addr_list[0], hptr->h_length);
	//连接腾讯的邮件SMTP服务器  
	int ok = connect(sockfd, (SOCKADDR*)& dest, sizeof(SOCKADDR));
	if (ok != 0)
		exit(0);
	//用于向服务器标明用户身份,可以为发件人的服务器域名或者主机名  
	sprintf_s(buf, 1500, "EHLO Aaron-PC\r\n");
	send(sockfd, buf, strlen(buf), 0);
	//接收服务器响应  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "QQ SMTP Server Say: \r\n" << buf << endl;
	//开启安全传输层协议（TLS）  
	//这里的STARTTLS空格的后面要加一些字符才行,这里不是很懂,但这就可以了.  
	sprintf_s(buf, 1500, "STARTTLS a\r\n");
	send(sockfd, buf, strlen(buf), 0);
	//接收服务器响应  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "QQ SMTP Server Say: \r\n" << buf << endl;
	//邮箱认证，发送该命令后依次发送邮箱账号和密码（账号密码均使用Base64编码）  
	sprintf_s(buf, 1500, "AUTH LOGIN\r\n");
	send(sockfd, buf, strlen(buf), 0);
	//接收服务器响应  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Auth Login Receive:\r\n " << buf << endl;
	//发送QQ账号
	ZeroMemory(buf, 1500);
	sprintf_s(buf, 1500, "452710557@qq.com");//你的邮箱账号  
	//将QQ账号转换为Base64编码再发送  
	EncodeBase64(login, buf, strlen(buf));
	sprintf_s(buf, 1500, "%s\r\n", login);
	send(sockfd, buf, strlen(buf), 0);
	cout << "Base64 UserName: " << buf << endl;
	//接收服务器响应  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "User Login Receive: \r\n" << buf << endl;
	//发送密钥（相当于QQ密码,在上面的步骤得到）  
	sprintf_s(buf, 1500, "qkwldxmuqxypbjdj");  //QQ邮箱授权码
	//将密钥转换为Base64编码再发送  
	EncodeBase64(pass, buf, strlen(buf));
	sprintf_s(buf, 1500, "%s\r\n", pass);
	send(sockfd, buf, strlen(buf), 0);
	cout << "Base64 Password:\r\n " << buf << endl;
	//接收服务器响应  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Send Password Receive:\r\n " << buf << endl;
	//发送MAIL FROM命令指定发件人  
	ZeroMemory(buf, 1500);
	sprintf_s(buf, 1500, "MAIL FROM: <mckjsy@qq.com>\r\n");
	send(sockfd, buf, strlen(buf), 0);
	//接收服务器响应  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Set Mail From Receive:\r\n " << buf << endl;
	//发送一个或多个RCPT TO命令指定收件人   
	sprintf_s(buf, 1500, "RCPT TO:<%s>\r\n", "452710557@qq.com"); //收件人
	send(sockfd, buf, strlen(buf), 0);
	//接收服务器响应  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Tell Sendto Receive: \r\n" << buf << endl;
	//发送一个DATA命令表示准备开始发送邮件内容  
	sprintf_s(buf, 1500, "DATA\r\n");
	send(sockfd, buf, strlen(buf), 0);
	//接收服务器响应  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Send Mail Prepare Receive: \r\n" << buf << endl;
	//发送邮件内容,格式：以\r\n.\r\n作为结束标记  
	sprintf_s(buf, 1500, "%s\r\n.\r\n", EmailContents);    //邮件的内容  
	send(sockfd, buf, strlen(buf), 0);
	//接收服务器响应  
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Send Mail Receive: \r\n" << buf << endl;
	//使用QUIT命令退出          
	sprintf_s(buf, 1500, "QUIT\r\n");
	send(sockfd, buf, strlen(buf), 0);
	ZeroMemory(buf, 1500);
	recv(sockfd, buf, 1500, 0);
	cout << "Quit Receive: " << buf << endl;
	//清理工作  
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


//转换为Base64编码函数  
void EncodeBase64(char* dbuf, char* buf128, int len)
{   //参数1：接收新Base64编码的缓冲区   参数2：要转换的字符串缓冲区  参数3：要转换的字符串长度
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



//辅助计算的函数  
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