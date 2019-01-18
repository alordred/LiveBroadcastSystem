#pragma once
#include <QThread>
#include <QMutex>
#include "XData.h"
#include <list>
class XDataThread:public QThread
{
public:
	//�������б��С���б����ֵ������ɾ����ɵ�����
	int maxList = 100;

	//���б��β����
	virtual void Push(XData d);

	//��ȡ�б�����������ݣ�����������Ҫ����XData.Drop����
	virtual XData Pop();

	//�����߳�
	virtual bool Start();

	//�˳��̲߳��ҵȴ��߳��˳���������
	virtual void Stop();

	virtual void Clear();
	XDataThread();
	virtual ~XDataThread();
protected:
	//��Ž�������
	std::list<XData> datas;
	//���������б��С
	int dataCout = 0;
	//������� datas
	QMutex mutex;

	//�����߳��˳�
	bool isExit = false;
};

