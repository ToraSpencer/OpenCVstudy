#include <stdlib.h>

/***************************************************************************
***************************************************************************/
// ȫ�ֱ��������Ͷ���



/***************************************************************************
***************************************************************************/
// extern����
extern void(*pfun[100])(void);
extern int inputTag, inputNum, interfaceLevel;


/***************************************************************************
***************************************************************************/
// ��������
void reset_pfun(void);
void traverse_pfun(void);


/***************************************************************************
***************************************************************************/
// extern����




/***************************************************************************
***************************************************************************/
// ��������


/*. BA------------------------------------------------------------------------
**	reset_fun()��������������ָ������pfun[100]��λ������������Ԫ����ΪNULL;
**
**
**	���������
**			��
**
**	���������
**			��
**
*. EA------------------------------------------------------------------------
*/
void reset_pfun(void)
{
	// 1. ��������ָ���ָ�룬ָ��pfun�еĵ�һ��Ԫ�أ�
	void(**ppf)(void) = NULL;
	int finishCount = 1;
	ppf = &pfun[0];


	// 2. ʹ��ѭ������pfun�е�����Ԫ�ض���ֵΪNULL;
	*ppf = NULL;
	while (finishCount < 100)
	{
		ppf++;
		*ppf = NULL;
		finishCount++;
	}

}



/*. BA------------------------------------------------------------------------
**	traverse_pfun()����������������pfun�����еķǿպ���ָ�롣
**
**
**	���������
**			��
**
**	���������
**			��
**
*. EA------------------------------------------------------------------------
*/
void traverse_pfun(void)
{
	// 1. ��������ָ���ָ�룬ָ��pfun�еĵ�һ��Ԫ�أ�
	void(**ppf)(void) = NULL;
	int finishCount = 0;
	ppf = &pfun[0];


	// 2. ʹ��ѭ�����������pfun�����зǿյĺ���ָ�룺
	while ((*ppf != NULL) && (finishCount < 99))
	{
		(**ppf)();
		ppf++;
		finishCount++;

	}

}


