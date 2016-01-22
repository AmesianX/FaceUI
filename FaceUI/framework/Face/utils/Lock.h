
#pragma once
#ifndef _FACE_LOCK_H_
#define _FACE_LOCK_H_

namespace Face
{
	/*
		Note: FaceLock��FaceLock2����ͼ�Ǽ�����FaceSemaphore��FaceMutex������趨�ȴ�����ʱ��
	*/
	class FACE_API FaceLock : public FaceNotCopyable
	{
	public:
		FaceLock();
		~FaceLock();

	public:
		void Enter();
		void Leave();
	private:
		CRITICAL_SECTION cs_;
	};

	class FACE_API FaceSemaphore : public FaceNotCopyable
	{
	public:
		FaceSemaphore(int iMaxSources = 5, int iEnableSources = 0);
		~FaceSemaphore();
		void Wait(unsigned long ultime = INFINITE);
		void Release(int iEnableSources = 1);
	private:
		HANDLE hSemaphore_;
	};

	class FACE_API FaceMutex : public FaceNotCopyable
	{
	public:
		FaceMutex(bool bInitialOwner = false);
		~FaceMutex();
	
	public:
		void Wait(unsigned long ultime = INFINITE);
		void Release();
	private:
		HANDLE hMutex_;
	};
}
#endif // _FACE_LOCK_H_
