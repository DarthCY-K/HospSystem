#include <stdio.h>
#include <string>
#include <time.h>
#include <malloc.h>
#include "RandomCount.h"

#define NameWidth 20	//�������Ƴ���
#define PasswordWidth 32	//�������Ƴ���
#define EmailWidth 20	//�������Ƴ���
#define MedcineNameWidth 32		//ҩƷ�������Ƴ���
#define MedcineProducerNameWidth 64		//ҩƷ�������������Ƴ���

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

UserLink* head_UserLink = (UserLink*)malloc(sizeof(UserLink));

typedef struct MedcineInf
{
	long medcine_Number_0;	//ҩƷ���(����)
	long medcine_Number_1;	//ҩƷ���(����)
	long medcine_ImportTime;	//����ʱ��
	char medcine_Name[MedcineNameWidth];	//ҩƷ����
	char medcine_ProducerName[MedcineProducerNameWidth];	//����������
	int exsit = 0;	//�Ƿ����(0������ 1����)
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
			printf("UserInf.hsp �ļ���Ϣ��ȡʧ�ܣ�����ϵ����Ա\n");
	}


	int LogOrReg = 0;
	printf("��ӭ����ҽԺ��Ϣ����ϵͳ�����ȵ�¼\n");
	printf("��¼(1)\tע��(2)\n");
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
		printf("��������,����������\n");
		getchar();		//����ͣ��
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
		printf("�ļ���ʧ��\n");
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
	//free(head);		//�ᵼ�¶ϵ㣬ԭ��δ֪
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


int MedcineInfReadF()
{

	MedcineLink* head = head_MedcineLink;
	MedcineLink* q;
	MedcineLink* p;
	p = q = head;
	FILE* fp = fopen("UserInf.hsp", "r");
	if (fp == NULL)
	{
		printf("�ļ���ʧ��\n");
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
	//free(head);		//�ᵼ�¶ϵ㣬ԭ��δ֪
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
		printf("�ļ���ʧ��\n");
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



void LoginF()	//��¼����
{

	char Input_Account[NameWidth], Input_Password[PasswordWidth];	//�û�������˺ź�����
	printf("�������û���������\n");

	printf("�˺ţ�");
	scanf("%s", Input_Account);
	UserLink* head = head_UserLink;
	UserLink* p_mov = head_UserLink;
	system("CLS");
CheckName:
	printf("��֤�У����Ժ�...\n");
	while (p_mov)
	{
		if (strcmp(Input_Account, p_mov->User_Name) == 0)			//�û�����ȷ
		{
			printf("���룺");
			scanf("%s", Input_Password);

		CheckPass:
			if (strcmp(Input_Password, p_mov->User_Password) == 0)		//�û�����ȷ ������ȷ
			{
				printf("��֤�ɹ�����������ҽԺ��Ϣϵͳ\n");
				UserSystem(p_mov);
				free(p_mov);
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
		else		//�û�������(ָ���û���������)
		{
			//p_mov->next = (UserLink*)malloc(sizeof(UserLink));
			p_mov = p_mov->next;
			if (p_mov->exsit != 1)
			{
				printf("�û��������ڣ����������룺");
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
	printf("�������û���������\n");
	printf("�û�����");
	getchar();
	gets_s(Input_regName, NameWidth);

	CheckExName:if (checkName_Link)
	{
		while (checkName_Link)
		{
			if (strcmp(Input_regName, checkName_Link->User_Name) == 0)
			{
				printf("��⵽�û����������û���ͻ�����������룡\n");
				printf("�û�����");
				fflush(stdin);
				scanf("%s", Input_regName);
				checkName_Link = head;
				goto CheckExName;
			}
			else
				checkName_Link = checkName_Link->next;		//�ƶ�����һλ
		}
		free(checkName_Link);
	}

	printf("���������룺");
	scanf("%s", Input_regPassword);
	printf("���������䣺");
	scanf("%s", Input_regEmail);

	int UserNumber = 0;		//��������˳�����
	while(p_mov)
	{
		if (p_mov->exsit != 1)		//�������û�
		{
			
			strcpy(p_mov->User_Name, Input_regName);
			strcpy(p_mov->User_Password, Input_regPassword);
			strcpy(p_mov->User_Email, Input_regEmail);
			p_mov->User_Number = UserNumber;
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

	printf("��Ҫ�һ����룬������ע��ʱ��ʹ�õ����䣬���ǽ��ᷢ��һ�ݰ������������ʼ���ע������\n");
CheckEmail:printf("������ע�����䣺");
	scanf("%s", Input_Email);

	SpecialNumber = GetRandomCount(8);
	for (int i = 0; i < 8; i++)
		Str_SpecialNumber[i] = *(SpecialNumber + i);
	printf("%s", SpecialNumber);
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



void UserSystem(UserLink* User)
{
	ReInput_UserSystem:
	int Choose = 0;
	system("CLS");
	printf("%s�����ѽ���ҽԺ��Ϣ����ϵͳ\n\n			��ѡ����ģ��\n\n", User->User_Name);
	printf("1.ҩ����Ϣ����\t2.������Ϣ����\t3.ҽ����Ϣ����\t4.�˳�ϵͳ\n");

	scanf("%d", &Choose);
	switch (Choose)
	{
		case 1:
			printf("��������ҩ����Ϣ����ģ��\n");
			system("CLS");
			MedcineSystem(User);
			break;
		case 2:
			printf("�������벡����Ϣ����ϵͳ\n");
			system("CLS");
			break;
		case 3:
			printf("��������ҽ����Ϣ����ϵͳ\n");
			system("CLS");
		case 4:
			printf("�����˳�ϵͳ\n");
			system("CLS");
			exit(0);
		default:
			printf("������������������\n");
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
			printf("UserInf.hsp �ļ���Ϣ��ȡʧ�ܣ�����ϵ����Ա\n");
	}
	
	printf("%s�����ѽ���ҩ����Ϣ����ϵͳ\n", User->User_Name);
	printf("1.ҩ����Ϣ��ѯ\t2.ҩ����Ϣ�޸�\t3.�˳�ϵͳ\n");
	printf("������ѡ��Ĺ���ģ�飺");
ReInput_MedcineSystem:	
	scanf("%d", &Choose);

	switch (Choose)
	{
		case 1:
			printf("��������ҩ����Ϣ��ѯģ��\n");
			system("CLS");
			MedcineInquire(User);
			break;
		case 2:
			printf("��������ҩ����Ϣ�޸�ģ��\n");
			system("CLS");
			MedcineDeleAdd(User);
			break;
		case 3:
			printf("�����˳�ϵͳ\n");
			system("CLS");
			exit(0);
		default:
			printf("�����������������룺");
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
	printf("%s�����ѽ���ҩ����Ϣ�޸�ģ��\n");
	printf("1.���ҩ����Ϣ\t2.ɾ��ҩ����Ϣ\t3.�޸�ҩ����Ϣ\t4.�˳�ϵͳ\n");
	printf("��ѡ����Ҫ�Ĺ��ܣ�");
ReInput_MedcineDeleAdd:
	scanf("%d", &Choose);

	if (Choose == 1)	//���ҩ����Ϣ
	{
		while (p_mov)
		{
		ReInput_MedcineDeleAdd_Add:
			if (p_mov->exsit != 1)
			{
				printf("������ҩƷ��ţ�");
				scanf("%ld", &p_mov->medcine_Number_0);
				printf("������ҩƷ���α�ţ�");
				scanf("%ld", &p_mov->medcine_Number_1);
				printf("������ҩƷ�ɹ�ʱ�䣺");
				scanf("%ld", &p_mov->medcine_ImportTime);
				printf("������ҩƷ���ƣ�");
				scanf("%s", p_mov->medcine_Name);
				printf("������ҩƷ���������ƣ�");
				scanf("%s", p_mov->medcine_ProducerName);
				p_mov->exsit = 1;
				if (MedcineInfSaveF(p_mov) == 0)
				{
					int Choose_0 = 0;
					system("CLS");
					printf("ҩƷ��Ϣ��ӳɹ�\n");
					printf("�Ƿ������ӣ�(1.�������� 2.�����޸�ģ��)\n");
					printf("��ѡ��");
					scanf("%d", &Choose_0);
					if (Choose_0 == 1)
					{
						goto ReInput_MedcineDeleAdd_Add;
					}
					else if (Choose_0 == 2)
					{
						printf("��������ҩƷ��Ϣ�޸�ģ��\n");
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
	else if (Choose = 2)	//ɾ��ҩ����Ϣ
	{

	}
	else if (Choose = 3)	//�޸�ҩ����Ϣ
	{

	}
	else if (Choose = 4)
	{
		printf("�����˳�ϵͳ\n");
		exit(0);
	}
	else
	{
		printf("�����������������룺");
		goto ReInput_MedcineDeleAdd;
	}
}