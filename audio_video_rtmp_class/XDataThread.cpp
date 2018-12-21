#include "XDataThread.h"
void XDataThread::Clear()
{
	mutex.lock();
	while (!datas.empty())
	{
		datas.front().Drop();
		datas.pop_front();
	}
	mutex.unlock();
}
//XDataThread::
//���б��β����
void XDataThread::Push(XData d)
{
	mutex.lock();
	//size������ǿ�
	if (datas.size() > maxList)
	{
		datas.front().Drop();
		datas.pop_front();
	}
	datas.push_back(d);
	mutex.unlock();
}

//��ȡ�б������������
XData XDataThread::Pop()
{
	mutex.lock();
	if (datas.empty())
	{
		mutex.unlock();
		return XData();
	}
	XData d = datas.front();
	datas.pop_front();
	mutex.unlock();
	return d;
}

//�����߳�
bool XDataThread::Start()
{
	isExit = false;
	QThread::start();
	return true;
}

//�˳��̲߳��ҵȴ��߳��˳���������
void XDataThread::Stop()
{
	//�Ȱ��߳��˳�
	isExit = true;
	wait();
}

XDataThread::XDataThread()
{
}


XDataThread::~XDataThread()
{
}
