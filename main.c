/*********************************************************************
Author:Li Junshi
File Decription: Finite State Machine general framework
File Created Time: 2017-06-23
Please send email to lijunshi2015@163.com if you have any question.
*********************************************************************/

#include <stdio.h>
//#include <windows.h> //windows
#include <unistd.h>  //linux

//比如我们定义了小明一天的状态如下
enum
{
	GET_UP,
	GO_TO_SCHOOL,
	HAVE_LUNCH,
	DO_HOMEWORK,
	SLEEP,
};

//我们定义的事件有以下几个
enum
{
	EVENT1 = 1,
	EVENT2,
	EVENT3,
};


typedef struct FsmTable_s
{
	int event;   //事件
	int CurState;  //当前状态
	void (*eventActFun)();  //函数指针
	int NextState;  //下一个状态
}FsmTable_t;


typedef struct FSM_s
{
	FsmTable_t* FsmTable;   //指向的状态表
	int curState;  //FSM当前所处的状态

}FSM_t;


int g_max_num;  //状态表里含有的状态个数



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

/*状态机注册*/
void FSM_Regist(FSM_t* pFsm, FsmTable_t* pTable)
{
	pFsm->FsmTable = pTable;
}

/*状态迁移*/
void FSM_StateTransfer(FSM_t* pFsm, int state)
{
	pFsm->curState = state;
}


/*事件处理*/
void FSM_EventHandle(FSM_t* pFsm, int event)
{
	FsmTable_t* pActTable = pFsm->FsmTable;
	void (*eventActFun)() = NULL;  //函数指针初始化为空
	int NextState;
	int CurState = pFsm->curState;
	int flag = 0; //标识是否满足条件

	/*获取当前动作函数*/
	for (int i = 0; i<g_max_num; i++)
	{
		//当且仅当当前状态下来个指定的事件，我才执行它
		if (event == pActTable[i].event && CurState == pActTable[i].CurState)
		{
			flag = 1;
			eventActFun = pActTable[i].eventActFun;
			NextState = pActTable[i].NextState;
			break;
		}
	}


	if (flag) //如果满足条件了
	{
		/*动作执行*/
		if (eventActFun)
		{
			eventActFun();
		}

		//跳转到下一个状态
		FSM_StateTransfer(pFsm, NextState);
	}
	else
	{
		// do nothing
	}
}

FsmTable_t XiaoMingTable[] =
{
	//{到来的事件，当前的状态，将要要执行的函数，下一个状态}
	{ EVENT1,  SLEEP,           GetUp,        GET_UP },
	{ EVENT2,  GET_UP,          Go2School,    GO_TO_SCHOOL },
	{ EVENT3,  GO_TO_SCHOOL,    HaveLunch,    HAVE_LUNCH },
	{ EVENT1,  HAVE_LUNCH,      DoHomework,   DO_HOMEWORK },
	{ EVENT2,  DO_HOMEWORK,     Go2Bed,       SLEEP },

	//add your codes here
};

//初始化FSM
void InitFsm(FSM_t* pFsm)
{
	g_max_num = sizeof(XiaoMingTable) / sizeof(FsmTable_t);
	pFsm->curState = SLEEP;
	FSM_Regist(pFsm, XiaoMingTable);
}


//测试用的
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
	//小明的一天,周而复始的一天又一天，进行着相同的活动
	while (1)
	{
		printf("event %d is coming...\n", event);
		FSM_EventHandle(&fsm, event);
		printf("fsm current state %d\n", fsm.curState);
		test(&event); 
		//sleep(1); //linux 下使用小写的sleep
		Sleep(1);  //休眠1秒，方便观察
	}

	return 0;
}
