#include <stdio.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include "RandomCount.h"

#define NameWidth 20	//姓名限制长度
#define PasswordWidth 32	//密码限制长度
#define EmailWidth 20	//邮箱限制长度
#define MedcineNameWidth 32		//药品名称限制长度
#define MedcineProducerNameWidth 64		//药品生产商名称限制长度

int read_TimesUser = 0;
int read_TimesMedcine = 0;

typedef struct UserInf
{
	int User_Number = 0;	//用户编号
	char User_Name[NameWidth];	//用户姓名
	char User_Password[PasswordWidth];	//用户密码
	char User_Email[EmailWidth];	//用户邮箱
	int exsit = 0;	//用户是否存在(0不存在 1存在)
	struct UserInf* next;
}UserLink;

UserLink* head_UserLink = (UserLink*)malloc(sizeof(UserLink));

typedef struct MedcineInf
{
	long medcine_Number_0;	//药品编号(单个)
	long medcine_Number_1;	//药品编号(批次)
	long medcine_ImportTime;	//进货时间
	char medcine_Name[MedcineNameWidth];	//药品名字
	char medcine_ProducerName[MedcineProducerNameWidth];	//生产者名字
	int exsit = 0;	//是否存在(0不存在 1存在)
	struct MedcineInf* next;
}MedcineLink;

MedcineLink* head_MedcineLink = (MedcineLink*)malloc(sizeof(MedcineLink));

int UserInfReadF();
int UserInfSaveF(UserLink* User);
int UserInfSave_All_F();

void LoginF();
void RegisterF();
void FindPassword(UserLink* User);

void UserSystem(UserLink* User);

void MedcineSystem(UserLink* User);
	void MedcineDeleAdd(UserLink* User);
	void MedcineInquire(UserLink* User);

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
		system("CLS");
		LoginF();
		break;
	case 2:
		system("CLS");
		RegisterF();
		break;
	default:
		printf("输入有误,请重新输入\n");
		getchar();		//用于停顿
		system("CLS");
		main();
		break;
	}
	return 0;
}


int UserInfReadF()
{
	
	UserLink* head = head_UserLink;
	UserLink* q;
	UserLink* p;
	p = q = head;
	FILE* fp = fopen("UserInf.hsp", "r");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return 1;
	}
	while (!feof(fp))
	{
		q = (UserLink*)malloc(sizeof(UserLink));
		fscanf(fp, "%d", &p->User_Number);
		fscanf(fp, "%s", p->User_Name);
		fscanf(fp, "%s", &p->User_Password);
		fscanf(fp, "%s", p->User_Email);
		fscanf(fp, "%d", &p->exsit);
		p->next = q;
		p = q;
	}
	p->next = NULL;
	//free(p);
	//free(q);
	//free(head);		//会导致断点，原因未知
	return 0;
}

int UserInfSaveF(UserLink* User)
{
	UserLink* head = User;
	UserLink* p, * q;
	p = q = head;
	FILE* fp = fopen("UserInf.hsp", "a");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return NULL;
	}
	bool doOnce = false;
	if (!feof(fp))
		do {
			fprintf(fp, "%d     ", q->User_Number);
			fprintf(fp, "%s     ", &q->User_Name);
			fprintf(fp, "%s     ", &q->User_Password);
			fprintf(fp, "%s     ", &q->User_Email);
			fprintf(fp, "%d\n", q->exsit);
		} while (doOnce != false);
	fclose(fp);
	p->next = NULL;
	//free(p);
	//free(q);
	//free(head);
	return 0;
}

int UserInfSave_All_F()
{
	//int i = 0;
	//FILE* fp;
	//if (fopen_s(&fp, "UserInf.darthcy", "w"))
	//{
	//	printf("can not open the file\n");
	//	return 1;									//文件打开失败，返回一个1
	//}
	//while (!feof(fp) && i < 100 && UserInf[i].exsit == 1)
	//{
	//	fprintf(fp, "%d     ", UserInf[i].User_Number);
	//	fprintf(fp, "%s     ", UserInf[i].User_Name);
	//	fprintf(fp, "%s     ", UserInf[i].User_Password);
	//	fprintf(fp, "%s     ", UserInf[i].User_Email);
	//	fprintf(fp, "%d\n", UserInf[i].exsit);
	//	i++;
	//}
	//fclose(fp);
	return 0;
}


int MedcineInfReadF()
{

	MedcineLink* head = head_MedcineLink;
	MedcineLink* q;
	MedcineLink* p;
	p = q = head;
	FILE* fp = fopen("UserInf.hsp", "r");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return 1;
	}
	while (!feof(fp))
	{
		q = (MedcineLink*)malloc(sizeof(UserLink));
		fscanf(fp, "%ld", &p->medcine_Number_0);
		fscanf(fp, "%ld", &p->medcine_Number_1);
		fscanf(fp, "%ld", &p->medcine_ImportTime);
		fscanf(fp, "%s", p->medcine_Name);
		fscanf(fp, "%s", p->medcine_ProducerName);
		fscanf(fp, "%d", &p->exsit);
		p->next = q;
		p = q;
	}
	p->next = NULL;
	//free(p);
	//free(q);
	//free(head);		//会导致断点，原因未知
	return 0;
}

int MedcineInfSaveF(MedcineLink* Medcine)
{
	MedcineLink* head = Medcine;
	MedcineLink* p, * q;
	p = q = head;
	FILE* fp = fopen("MedcineInf.hsp", "a");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		return 1;
	}
	bool doOnce = false;
	if (!feof(fp))
		do {
			fprintf(fp, "%ld     ", q->medcine_Number_0);
			fprintf(fp, "%ld     ", q->medcine_Number_1);
			fprintf(fp, "%ld     ", q->medcine_ImportTime);
			fprintf(fp, "%s     ", &q->medcine_Name);
			fprintf(fp, "%s     ", &q->medcine_ProducerName);
			fprintf(fp, "%d\n", q->exsit);
		} while (doOnce != false);
		fclose(fp);
		p->next = NULL;
		//free(p);
		//free(q);
		//free(head);
		return 0;
}



void LoginF()	//登录函数
{

	char Input_Account[NameWidth], Input_Password[PasswordWidth];	//用户输入的账号和密码
	printf("请输入用户名和密码\n");

	printf("账号：");
	scanf("%s", Input_Account);
	UserLink* head = head_UserLink;
	UserLink* p_mov = head_UserLink;
	system("CLS");
CheckName:
	printf("验证中，请稍后...\n");
	while (p_mov)
	{
		if (strcmp(Input_Account, p_mov->User_Name) == 0)			//用户名正确
		{
			printf("密码：");
			scanf("%s", Input_Password);

		CheckPass:
			if (strcmp(Input_Password, p_mov->User_Password) == 0)		//用户名正确 密码正确
			{
				printf("认证成功，即将进入医院信息系统\n");
				UserSystem(p_mov);
				free(p_mov);
				exit(0);
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
					FindPassword(p_mov);		//前往找回密码函数
					exit(0);
				}
			}
		}
		else		//用户名错误(指的用户名不存在)
		{
			//p_mov->next = (UserLink*)malloc(sizeof(UserLink));
			p_mov = p_mov->next;
			if (p_mov->exsit != 1)
			{
				printf("用户名不存在，请重新输入：");
				scanf("%s", Input_Account);
				p_mov = head;
				goto CheckName;
			}
		}
	}
	free(p_mov);
}

void RegisterF()
{
	UserLink* head = head_UserLink;
	UserLink* checkName_Link = head;
	UserLink* p_mov = head;
	char Input_regName[NameWidth], Input_regPassword[PasswordWidth], Input_regEmail[EmailWidth];
	printf("请输入用户名和密码\n");
	printf("用户名：");
	getchar();
	gets_s(Input_regName, NameWidth);

	CheckExName:if (checkName_Link)
	{
		while (checkName_Link)
		{
			if (strcmp(Input_regName, checkName_Link->User_Name) == 0)
			{
				printf("检测到用户名与已有用户冲突，请重新输入！\n");
				printf("用户名：");
				fflush(stdin);
				scanf("%s", Input_regName);
				checkName_Link = head;
				goto CheckExName;
			}
			else
				checkName_Link = checkName_Link->next;		//移动到下一位
		}
		free(checkName_Link);
	}

	printf("请输入密码：");
	scanf("%s", Input_regPassword);
	printf("请输入邮箱：");
	scanf("%s", Input_regEmail);

	int UserNumber = 0;		//用于链表顺序计数
	while(p_mov)
	{
		if (p_mov->exsit != 1)		//不存在用户
		{
			
			strcpy(p_mov->User_Name, Input_regName);
			strcpy(p_mov->User_Password, Input_regPassword);
			strcpy(p_mov->User_Email, Input_regEmail);
			p_mov->User_Number = UserNumber;
			p_mov->exsit = 1;

			if (UserInfSaveF(p_mov) == 0)
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
			free(p_mov);
			exit(0);
		}
		else
		{
			UserNumber++;
			p_mov->next = (UserLink*)malloc(sizeof(UserLink));
			p_mov = p_mov->next;
		}

	}
	free(p_mov);
}

void FindPassword(UserLink* User)
{
	UserLink* p_mov = User;
	char Input_Email[20];
	char* SpecialNumber;
	char Str_SpecialNumber[8],Input_SpecialNumber[8];

	printf("若要找回密码，请输入注册时所使用的邮箱，我们将会发送一份包含特殊代码的邮件至注册邮箱\n");
CheckEmail:printf("请输入注册邮箱：");
	scanf("%s", Input_Email);

	SpecialNumber = GetRandomCount(8);
	for (int i = 0; i < 8; i++)
		Str_SpecialNumber[i] = *(SpecialNumber + i);
	printf("%s", SpecialNumber);
	free(SpecialNumber);
	
	if (strcmp(Input_Email, p_mov->User_Email) == 0)
	{

		printf("特殊代码已发送至邮箱，请查收\n");
	Re_specNumber:
		printf("请输入特殊代码：");
		scanf("%d", &Input_SpecialNumber);

		if (strcmp(Input_SpecialNumber, Str_SpecialNumber) == 0)
		{
			printf("特殊代码验证成功\n");
			printf("请输入新密码：");
			scanf("%s", p_mov->User_Password);

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



void UserSystem(UserLink* User)
{
	ReInput_UserSystem:
	int Choose = 0;
	system("CLS");
	printf("%s，您已进入医院信息管理系统\n\n			请选择功能模块\n\n", User->User_Name);
	printf("1.药物信息管理\t2.病人信息管理\t3.医生信息管理\t4.退出系统\n");

	scanf("%d", &Choose);
	switch (Choose)
	{
		case 1:
			printf("即将进入药物信息管理模块\n");
			system("CLS");
			MedcineSystem(User);
			break;
		case 2:
			printf("即将进入病人信息管理系统\n");
			system("CLS");
			break;
		case 3:
			printf("即将进入医生信息管理系统\n");
			system("CLS");
		case 4:
			printf("即将退出系统\n");
			system("CLS");
			exit(0);
		default:
			printf("输入有误，请重新输入\n");
			goto ReInput_UserSystem;
			break;
	}
	
}



void MedcineSystem(UserLink* User)
{
	int Choose = 0;
	if (read_TimesMedcine == 0)
	{
		if (MedcineInfReadF() == 0)
			read_TimesMedcine++;
		else
			printf("UserInf.hsp 文件信息读取失败，请联系管理员\n");
	}
	
	printf("%s，您已进入药物信息管理系统\n", User->User_Name);
	printf("1.药物信息查询\t2.药物信息修改\t3.退出系统\n");
	printf("请输入选择的功能模块：");
ReInput_MedcineSystem:	
	scanf("%d", &Choose);

	switch (Choose)
	{
		case 1:
			printf("即将进入药物信息查询模块\n");
			system("CLS");
			MedcineInquire(User);
			break;
		case 2:
			printf("即将进入药物信息修改模块\n");
			system("CLS");
			MedcineDeleAdd(User);
			break;
		case 3:
			printf("即将退出系统\n");
			system("CLS");
			exit(0);
		default:
			printf("输入有误，请重新输入：");
			goto ReInput_MedcineSystem;
			break;
	}

}

void MedcineInquire(UserLink* User)
{

}

void MedcineDeleAdd(UserLink* User)
{
	int Choose = 0;
	MedcineLink* head = head_MedcineLink;
	MedcineLink* p_mov = head;
	printf("%s，您已进入药物信息修改模块\n");
	printf("1.添加药物信息\t2.删除药物信息\t3.修改药物信息\t4.退出系统\n");
	printf("请选择需要的功能：");
ReInput_MedcineDeleAdd:
	scanf("%d", &Choose);

	if (Choose == 1)	//添加药物信息
	{
		while (p_mov)
		{
		ReInput_MedcineDeleAdd_Add:
			if (p_mov->exsit != 1)
			{
				printf("请输入药品编号：");
				scanf("%ld", &p_mov->medcine_Number_0);
				printf("请输入药品批次编号：");
				scanf("%ld", &p_mov->medcine_Number_1);
				printf("请输入药品采购时间：");
				scanf("%ld", &p_mov->medcine_ImportTime);
				printf("请输入药品名称：");
				scanf("%s", p_mov->medcine_Name);
				printf("请输入药品生产商名称：");
				scanf("%s", p_mov->medcine_ProducerName);
				p_mov->exsit = 1;
				if (MedcineInfSaveF(p_mov) == 0)
				{
					int Choose_0 = 0;
					system("CLS");
					printf("药品信息添加成功\n");
					printf("是否继续添加？(1.继续输入 2.返回修改模块)\n");
					printf("请选择：");
					scanf("%d", &Choose_0);
					if (Choose_0 == 1)
					{
						goto ReInput_MedcineDeleAdd_Add;
					}
					else if (Choose_0 == 2)
					{
						printf("即将返回药品信息修改模块\n");
						system("CLS");
						MedcineSystem(User);
						exit(0);
					}
				}

			}
			else
			{
				p_mov->next = (MedcineLink*)malloc(sizeof(MedcineLink));
				p_mov = p_mov->next;
			}
		}
	}
	else if (Choose = 2)	//删除药物信息
	{

	}
	else if (Choose = 3)	//修改药物信息
	{

	}
	else if (Choose = 4)
	{
		printf("即将退出系统\n");
		exit(0);
	}
	else
	{
		printf("输入有误，请重新输入：");
		goto ReInput_MedcineDeleAdd;
	}
}