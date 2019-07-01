#include <stdio.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include "RandomCount.h"

#define NameWidth 20	//�������Ƴ���
#define PasswordWidth 32	//�������Ƴ���
#define EmailWidth 20	//�������Ƴ���

int read_TimesUser = 0;
int read_TimesMedcine = 0;

typedef struct UserInf
{
	int User_Number = 0;	//�û����
	char User_Name[NameWidth];	//�û�����
	char User_Password[PasswordWidth];	//�û�����
	char User_Email[EmailWidth];	//�û�����
	int exsit = 0;	//�û��Ƿ����(0������ 1����)
	struct UserInf* next;
}UserLink;

typedef struct MedcineInf
{
	long medcine_Number;	//ҩƷ���
	char medcine_Name[20];	//ҩƷ����
	char medcine_ProducerName[10];	//����������
	int exsist = 0;	//�Ƿ����(0������ 1����)
	struct MedcineInf* next;
}MedcineLink;

UserLink* UserInfReadF();
int UserInfSaveF(UserLink* User);
int UserInfSave_All_F();

void LoginF();
void RegisterF();
void FindPassword(UserLink* User);

void UserSystem(int UserIndex);


int main()
{
	if (read_TimesUser == 0)
	{
		if (UserInfReadF() == 0)
			read_TimesUser++;
		else
			printf("UserInf.hsp �ļ���Ϣ��ȡʧ�ܣ�����ϵ����Ա\n");
	}


	int LogOrReg = 0;
	printf("��ӭ����ҽԺ��Ϣ����ϵͳ�����ȵ�¼\n");
	printf("��¼(1)\tע��(2)\n");
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
		printf("��������,����������\n");
		main();
		break;
	}
	return 0;
}

UserLink* UserInfReadF()
{
	UserLink* head = (UserLink*)malloc(sizeof(UserLink));
	UserLink* p, * q;
	p = q = head;
	FILE* fp = fopen("UserInf.hsp", "r");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��\n");
		return NULL;
	}
	while (!feof(fp))
	{
		q = (UserLink*)malloc(sizeof(UserLink));
		fscanf(fp, "%d", &q->User_Number);
		fscanf(fp, "%s", &q->User_Name);
		fscanf(fp, "%s", &q->User_Password);
		fscanf(fp, "%s", &q->User_Email);
		fscanf(fp, "%d", &q->exsit);
	}
	p->next = NULL;
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
		printf("�ļ���ʧ��\n");
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
		return 0;
}

int UserInfSave_All_F()
{
	//int i = 0;
	//FILE* fp;
	//if (fopen_s(&fp, "UserInf.darthcy", "w"))
	//{
	//	printf("can not open the file\n");
	//	return 1;									//�ļ���ʧ�ܣ�����һ��1
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



void LoginF()	//��¼����
{
	int i = 0;
	char Input_Account[20], Input_Password[20];	//�û�������˺ź�����
	UserLink* head = (UserLink*)malloc(sizeof(UserLink));
	UserLink* p_mov = head;
	printf("�������û���������\n");

	printf("�˺ţ�");
	scanf("%s", Input_Account);


CheckName:
	printf("��֤�У����Ժ�...\n");

	for (int i = 0; i < 100; i++)
	{
		if (strcmp(Input_Account, p_mov->User_Name) == 0)			//�û�����ȷ
		{
			printf("���룺");
			scanf("%s", Input_Password);

		CheckPass:
			if (strcmp(Input_Password, p_mov->User_Password) == 0)		//�û�����ȷ ������ȷ
			{
					printf("��֤�ɹ�����������ҽԺ��Ϣϵͳ\n");
					UserSystem(i);
					exit(0);
			}
			else		//�û�����ȷ �������

			{
				int yOn = 0;
				printf("������������������������ѡ���һ�����\n");
				printf("1.��������\t2.�һ�����\n");
				scanf("%d", &yOn);
				if (yOn == 1)
				{
					printf("���������룺");
					scanf("%s", Input_Password);
					goto CheckPass;		//����������֤
				}
				else
				{
					FindPassword(p_mov);		//ǰ���һ����뺯��
					exit(0);
				}
			}
		}
		else		//�û�������
		{
			if (i == 9 && strcmp(Input_Account, p_mov->User_Name) != 0)
			{
				printf("���û������ڣ������������û�����");
				scanf("%s", Input_Account);
				goto CheckName;		//�����û�����֤

			}
		}
		p_mov = p_mov->next;
	}
}

void RegisterF()
{
	UserLink* head = (UserLink*)malloc(sizeof(UserLink));
	UserLink* p_mov = head;
	char Input_regName[NameWidth], Input_regPassword[PasswordWidth], Input_regEmail[EmailWidth];
	printf("�������û���������\n");
	printf("�û�����");
	getchar();
	gets_s(Input_regName, NameWidth);

CheckExName:for (int i = 0; i < 100; i++)
{
	if (strcmp(Input_regName, p_mov->User_Name) == 0)
	{
		printf("��⵽�û����������û���ͻ�����������룡\n");
		printf("�û�����");
		scanf("%s", Input_regName);
		goto CheckExName;
	}
	else
		break;
}

			printf("���������룺");
			gets_s(Input_regPassword, PasswordWidth);
			printf("���������䣺");
			gets_s(Input_regEmail, EmailWidth);

			for (int i = 0; i < 100; i++)
			{
				if (p_mov)
				{
					strcpy(p_mov->User_Name, Input_regName);
					strcpy(p_mov->User_Password, Input_regPassword);
					strcpy(p_mov->User_Email, Input_regEmail);
					p_mov->exsit = 1;

					if (UserInfSaveF(p_mov) == 0)
					{
						printf("ע��ɹ��������������˵�\n");
						main();
					}
					else
					{
						printf("ע��ʧ�ܣ�����ϵ����Ա\n");
						printf("�����������˵�\n");
						main();
					}
					exit(0);
				}
				else if (i == 99 && p_mov->exsit == 1)
				{
					printf("��ϵͳ��ע����������������ϵ����Ա���ӿ�ע������\n");
					printf("ע��ʧ�ܣ������������˵�\n");
					main();
					exit(0);
				}
				p_mov = p_mov->next;
			}
}

void FindPassword(UserLink* User)
{
	UserLink* p_mov = User;
	char Input_Email[20];
	char* SpecialNumber;
	char Str_SpecialNumber[8],Input_SpecialNumber[8];

	printf("��Ҫ�һ����룬������ע��ʱ��ʹ�õ����䣬���ǽ��ᷢ��һ�ݰ������������ʼ���ע������\n");
CheckEmail:printf("������ע�����䣺");
	scanf("%s", Input_Email);

	SpecialNumber = GetRandomCount(8);
	for (int i = 0; i < 8; i++)
		Str_SpecialNumber[i] = *(SpecialNumber + i);
	free(SpecialNumber);
	
	if (strcmp(Input_Email, p_mov->User_Email) == 0)
	{

		printf("��������ѷ��������䣬�����\n");
	Re_specNumber:
		printf("������������룺");
		scanf("%d", &Input_SpecialNumber);

		if (strcmp(Input_SpecialNumber, Str_SpecialNumber) == 0)
		{
			printf("���������֤�ɹ�\n");
			printf("�����������룺");
			scanf("%s", p_mov->User_Password);

			if (UserInfSave_All_F() == 0)
			{
				printf("�޸ĳɹ������������˺���֤ϵͳ\n");
				LoginF();
				return;// exit(0);
			}
			else
			{
				printf("UserInf.hsp �ļ�����ʧ�ܣ�����ϵ����Ա\n");
				printf("�����������˵�\n");
				main();
				return;// exit(0);
			}
			return;

		}
		else
		{
			printf("���������֤ʧ�ܣ����������룡\n");
			goto Re_specNumber;
		}


	}
	else
	{
		int yOn;
		printf("ע����������Ƿ��ٴ����룿\n");
		printf("1.��/t2.��\n");
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