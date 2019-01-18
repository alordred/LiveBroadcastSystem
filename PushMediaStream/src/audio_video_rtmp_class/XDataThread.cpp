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
//在列表结尾插入
void XDataThread::Push(XData d)
{
	mutex.lock();
	//size大可能是坑
	if (datas.size() > maxList)
	{
		datas.front().Drop();
		datas.pop_front();
	}
	datas.push_back(d);
	mutex.unlock();
}

//读取列表中最早的数据
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

//启动线程
bool XDataThread::Start()
{
	isExit = false;
	QThread::start();
	return true;
}

//退出线程并且等待线程退出（阻塞）
void XDataThread::Stop()
{
	//先把线程退出
	isExit = true;
	wait();
}

XDataThread::XDataThread()
{
}


XDataThread::~XDataThread()
{
}
