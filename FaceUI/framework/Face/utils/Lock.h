
#pragma once
#ifndef _FACE_LOCK_H_
#define _FACE_LOCK_H_

namespace Face
{
	/*
		Note: Lock��FaceLock2����ͼ�Ǽ�����Semaphore��Mutex������趨�ȴ�����ʱ��
	*/
	class FACE_API Lock : public NotCopyable
	{
	public:
		Lock();
		~Lock();

	public:
		void Enter();
		void Leave();
	private:
		CRITICAL_SECTION cs_;
	};

	class FACE_API Semaphore : public NotCopyable
	{
	public:
		Semaphore(int iMaxSources = 5, int iEnableSources = 0);
		~Semaphore();
		void Wait(unsigned long ultime = INFINITE);
		void Release(int iEnableSources = 1);
	private:
		HANDLE hSemaphore_;
	};

	class FACE_API Mutex : public NotCopyable
	{
	public:
		Mutex(bool bInitialOwner = false);
		~Mutex();
	
	public:
		void Wait(unsigned long ultime = INFINITE);
		void Release();
	private:
		HANDLE hMutex_;
	};
}
#endif // _FACE_LOCK_H_
