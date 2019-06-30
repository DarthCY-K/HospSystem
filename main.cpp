#include <stdio.h>
#include <string>
#include <time.h>
#include "RandomCount.h"

#define NameWidth 20	//姓名限制长度
#define PasswordWidth 32	//密码限制长度
#define EmailWidth 20	//邮箱限制长度

int read_TimesUser = 0;
int read_TimesMedcine = 0;

struct UserInf
{
	int User_Number = 0;	//用户编号
	char User_Name[NameWidth];	//用户姓名
	char User_Password[PasswordWidth];	//用户密码
	char User_Email[EmailWidth];	//用户邮箱
	int exsit = 0;	//用户是否存在(0不存在 1存在)
	int Admin = 0;	//用户是否为管理员(0为用户 1为管理员)

}UserInf[100];

struct MedcineInf
{
	long medcine_Number;	//药品编号
	char medcine_Name[20];	//药品名字
	char medcine_ProducerName[10];	//生产者名字
	int exsist = 0;	//是否存在(0不存在 1存在)
}MedcineInf[100];



int UserInfReadF();
int UserInfSaveF(int i);
int UserInfSave_All_F();

void LoginF();
void RegisterF();
void FindPassword(int i);

void UserSystem(int UserIndex);
void AdminSystem(int UserIndex);


int main()
{
	if (read_TimesUser == 0)
	{
		if (UserInfReadF() == 0)
			read_TimesUser++;
		else
			printf("UserInf.hsp 文件信息读取失败，请联系管理员\n");
	}


	int LogOrReg = 0;
	printf("欢迎进入医院信息管理系统，请先登录\n");
	printf("登录(1)\t注册(2)\n");
	scanf("%d", &LogOrReg);
	switch (LogOrReg)
	{
	case 1:
		LoginF();
		break;
	case 2:
		RegisterF();
		break;
	default:
		printf("输入有误,请重新输入\n");
		main();
		break;
	}
	return 0;
}

int UserInfReadF()
{
	int i = 0;
	FILE* fp;
	if (fopen_s(&fp, "UserInf.hsp", "r"))
	{
		printf("can not open the file\n");
		return 1;									//文件打开失败，返回一个1
	}
	if (fp)
		while (!feof(fp) && i < 100)
		{
			fscanf(fp, "%d", &UserInf[i].User_Number);
			fscanf(fp, "%s", UserInf[i].User_Name);
			fscanf(fp, "%s", UserInf[i].User_Password);
			fscanf(fp, "%s", UserInf[i].User_Email);
			fscanf(fp, "%d", &UserInf[i].exsit);
			fscanf(fp, "%d", &UserInf[i].Admin);
			i++;
		}
	fclose(fp);
	return 0;										//用户信息写入成功，返回一个0
}

int UserInfSaveF(int i)
{
	FILE* fp;
	if (fopen_s(&fp, "UserInf.hsp", "a"))
	{
		printf("can not open the file\n");
		return 1;									//文件打开失败，返回一个1
	}
	bool doOnce = false;
	if (!feof(fp))
		do {
			fprintf(fp, "%d     ", UserInf[i].User_Number);
			fprintf(fp, "%s     ", UserInf[i].User_Name);
			fprintf(fp, "%s     ", UserInf[i].User_Password);
			fprintf(fp, "%s     ", UserInf[i].User_Email);
			fprintf(fp, "%d     ", UserInf[i].exsit);
			fprintf(fp, "%d\n", UserInf[i].Admin);
		} while (doOnce != false);
		fclose(fp);
		return 0;
}

int UserInfSave_All_F()
{
	int i = 0;
	FILE* fp;
	if (fopen_s(&fp, "UserInf.darthcy", "w"))
	{
		printf("can not open the file\n");
		return 1;									//文件打开失败，返回一个1
	}
	while (!feof(fp) && i < 100 && UserInf[i].exsit == 1)
	{
		fprintf(fp, "%d     ", UserInf[i].User_Number);
		fprintf(fp, "%s     ", UserInf[i].User_Name);
		fprintf(fp, "%s     ", UserInf[i].User_Password);
		fprintf(fp, "%s     ", UserInf[i].User_Email);
		fprintf(fp, "%d     ", UserInf[i].exsit);
		fprintf(fp, "%d\n", UserInf[i].Admin);
		i++;
	}
	fclose(fp);
	return 0;
}

void LoginF()	//登录函数
{
	int i = 0;
	char Input_Account[20], Input_Password[20];	//用户输入的账号和密码
	printf("请输入用户名和密码\n");

	printf("账号：");
	scanf("%s", Input_Account);


CheckName:
	printf("验证中，请稍后...\n");

	for (int i = 0; i < 100; i++)
	{
		if (strcmp(Input_Account, UserInf[i].User_Name) == 0)			//用户名正确
		{
			printf("密码：");
			scanf("%s", Input_Password);

		CheckPass:
			if (strcmp(Input_Password, UserInf[i].User_Password) == 0)		//用户名正确 密码正确
			{

				if (UserInf[i].Admin == 0)
				{
					printf("认证成功，即将进入医院信息系统\n");
					UserSystem(i);
					exit(0);
				}
				else
				{
					printf("认证成功，即将进入医院信息系统后台\n");
					AdminSystem(i);
					exit(0);
				}
			}
			else		//用户名正确 密码错误

			{
				int yOn = 0;
				printf("密码输入错误，请重新输入或是选择找回密码\n");
				printf("1.重新输入\t2.找回密码\n");
				scanf("%d", &yOn);
				if (yOn == 1)
				{
					printf("请输入密码：");
					scanf("%s", Input_Password);
					goto CheckPass;		//返回密码验证
				}
				else
				{
					FindPassword(i);		//前往找回密码函数
					exit(0);
				}
			}
		}
		else		//用户名错误
		{
			for (int j = 0; j < 10; j++)
				if (strcmp(Input_Account, UserInf[j].User_Name) == 0)
				{
					j = 10;
				}
				else if (j == 9 && strcmp(Input_Account, UserInf[j].User_Name) != 0)
				{
					printf("此用户不存在，请重新输入用户名：");
					scanf("%s", Input_Account);
					goto CheckName;		//返回用户名验证

				}
		}
	}
}

void RegisterF()
{
	char Input_regName[NameWidth], Input_regPassword[PasswordWidth], Input_regEmail[EmailWidth];
	printf("请输入用户名和密码\n");
	printf("用户名：");
	getchar();
	gets_s(Input_regName, NameWidth);

CheckExName:for (int i = 0; i < 100; i++)
{
	if (strcmp(Input_regName, UserInf[i].User_Name) == 0)
	{
		printf("检测到用户名与已有用户冲突，请重新输入！\n");
		printf("用户名：");
		scanf("%s", Input_regName);
		goto CheckExName;
	}
	else
		break;
}

			printf("请输入密码：");
			gets_s(Input_regPassword, 20);
			printf("请输入邮箱：");
			gets_s(Input_regEmail, 20);

			for (int i = 0; i < 100; i++)
			{
				if (UserInf[i].exsit == 0)
				{
					strcpy(UserInf[i].User_Name, Input_regName);
					strcpy(UserInf[i].User_Password, Input_regPassword);
					strcpy(UserInf[i].User_Email, Input_regEmail);
					UserInf[i].exsit = 1;

					if (UserInfSaveF(i) == 0)
					{
						printf("注册成功，即将返回主菜单\n");
						main();
					}
					else
					{
						printf("注册失败，请联系管理员\n");
						printf("即将返回主菜单\n");
						main();
					}
					exit(0);
				}
				else if (i == 99 && UserInf[i].exsit == 1)
				{
					printf("此系统可注册人数已满，请联系管理员增加可注册数量\n");
					printf("注册失败，即将返回主菜单\n");
					main();
					exit(0);
				}
			}
}

void FindPassword(int i)
{
	char Input_Email[20];
	char* SpecialNumber;
	char Str_SpecialNumber[8],Input_SpecialNumber[8];

	printf("若要找回密码，请输入注册时所使用的邮箱，我们将会发送一份包含特殊代码的邮件至注册邮箱\n");
CheckEmail:printf("请输入注册邮箱：");
	scanf("%s", Input_Email);

	SpecialNumber = GetRandomCount(8);
	for (int i = 0; i < 8; i++)
		Str_SpecialNumber[i] = *(SpecialNumber + i);
	free(SpecialNumber);
	

	if (strcmp(Input_Email, UserInf[i].User_Email) == 0)
	{

		printf("特殊代码已发送至邮箱，请查收\n");
	Re_specNumber:
		printf("请输入特殊代码：");
		scanf("%d", &Input_SpecialNumber);

		if (strcmp(Input_SpecialNumber, Str_SpecialNumber) == 0)
		{
			printf("特殊代码验证成功\n");
			printf("请输入新密码：");
			scanf("%s", UserInf[i].User_Password);

			if (UserInfSave_All_F() == 0)
			{
				printf("修改成功！即将返回账号验证系统\n");
				LoginF();
				return;// exit(0);
			}
			else
			{
				printf("UserInf.hsp 文件保存失败，请联系管理员\n");
				printf("即将返回主菜单\n");
				main();
				return;// exit(0);
			}
			return;

		}
		else
		{
			printf("特殊代码验证失败，请重新输入！\n");
			goto Re_specNumber;
		}


	}
	else
	{
		int yOn;
		printf("注册邮箱错误，是否再次输入？\n");
		printf("1.是/t2.否\n");
		scanf("%d", &yOn);
		if (yOn == 1)
			goto CheckEmail;
		else
		{
			main();
			exit(0);
		}

	}

}



void UserSystem(int UserIndex)
{

}

void AdminSystem(int UserIndex)
{

}