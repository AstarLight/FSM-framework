/*********************************************************************
Author:Li Junshi
File Decription: Finite State Machine general framework
File Created Time: 2017-06-23
Please send email to lijunshi2015@163.com if you have any question.
*********************************************************************/

#include <stdio.h>
//#include <windows.h> //windows
#include <unistd.h>  //linux

//�������Ƕ�����С��һ���״̬����
enum
{
	GET_UP,
	GO_TO_SCHOOL,
	HAVE_LUNCH,
	DO_HOMEWORK,
	SLEEP,
};

//���Ƕ�����¼������¼���
enum
{
	EVENT1 = 1,
	EVENT2,
	EVENT3,
};


typedef struct FsmTable_s
{
	int event;   //�¼�
	int CurState;  //��ǰ״̬
	void (*eventActFun)();  //����ָ��
	int NextState;  //��һ��״̬
}FsmTable_t;


typedef struct FSM_s
{
	FsmTable_t* FsmTable;   //ָ���״̬��
	int curState;  //FSM��ǰ������״̬

}FSM_t;


int g_max_num;  //״̬���ﺬ�е�״̬����



void GetUp()
{
	// do something
	printf("xiao ming gets up!\n");

}

void Go2School()
{
	// do something
	printf("xiao ming goes to school!\n");
}

void HaveLunch()
{
	// do something
	printf("xiao ming has lunch!\n");
}

void DoHomework()
{
	// do something
	printf("xiao ming does homework!\n");
}

void Go2Bed()
{
	// do something
	printf("xiao ming goes to bed!\n");
}

/*״̬��ע��*/
void FSM_Regist(FSM_t* pFsm, FsmTable_t* pTable)
{
	pFsm->FsmTable = pTable;
}

/*״̬Ǩ��*/
void FSM_StateTransfer(FSM_t* pFsm, int state)
{
	pFsm->curState = state;
}


/*�¼�����*/
void FSM_EventHandle(FSM_t* pFsm, int event)
{
	FsmTable_t* pActTable = pFsm->FsmTable;
	void (*eventActFun)() = NULL;  //����ָ���ʼ��Ϊ��
	int NextState;
	int CurState = pFsm->curState;
	int flag = 0; //��ʶ�Ƿ���������

	/*��ȡ��ǰ��������*/
	for (int i = 0; i<g_max_num; i++)
	{
		//���ҽ�����ǰ״̬������ָ�����¼����Ҳ�ִ����
		if (event == pActTable[i].event && CurState == pActTable[i].CurState)
		{
			flag = 1;
			eventActFun = pActTable[i].eventActFun;
			NextState = pActTable[i].NextState;
			break;
		}
	}


	if (flag) //�������������
	{
		/*����ִ��*/
		if (eventActFun)
		{
			eventActFun();
		}

		//��ת����һ��״̬
		FSM_StateTransfer(pFsm, NextState);
	}
	else
	{
		// do nothing
	}
}

FsmTable_t XiaoMingTable[] =
{
	//{�������¼�����ǰ��״̬����ҪҪִ�еĺ�������һ��״̬}
	{ EVENT1,  SLEEP,           GetUp,        GET_UP },
	{ EVENT2,  GET_UP,          Go2School,    GO_TO_SCHOOL },
	{ EVENT3,  GO_TO_SCHOOL,    HaveLunch,    HAVE_LUNCH },
	{ EVENT1,  HAVE_LUNCH,      DoHomework,   DO_HOMEWORK },
	{ EVENT2,  DO_HOMEWORK,     Go2Bed,       SLEEP },

	//add your codes here
};

//��ʼ��FSM
void InitFsm(FSM_t* pFsm)
{
	g_max_num = sizeof(XiaoMingTable) / sizeof(FsmTable_t);
	pFsm->curState = SLEEP;
	FSM_Regist(pFsm, XiaoMingTable);
}


//�����õ�
void test(int *event)
{
	if (*event == 3)
	{
		*event = 1;
	}
	else
	{
		(*event)++;
	}
	
}


int main()
{
	FSM_t fsm;
	InitFsm(&fsm);
	int event = EVENT1; 
	//С����һ��,�ܶ���ʼ��һ����һ�죬��������ͬ�Ļ
	while (1)
	{
		printf("event %d is coming...\n", event);
		FSM_EventHandle(&fsm, event);
		printf("fsm current state %d\n", fsm.curState);
		test(&event); 
		Sleep(1);  //����1�룬����۲�
	}

	return 0;
}
