#pragma once
#ifndef _WINDOWIMPL_H_
#define _WINDOWIMPL_H_

namespace Face
{
	class WindowControl;
	/*
		�������ʵ�֣���FaceUI�У�һ�������Ĵ��ڱ���ֳ�Window��WindowImpl, WindowControl, WindowControlEvent
		Window�����ڻ��࣬���ṩ��һ������������Ĺ��ܺ�win32���ڽӿ�
		WindowImpl������ʵ���࣬��ʵ����FaceUI���ڣ����ڻ��ơ�windows��Ϣ
		WindowControl��������DirectUI���У�Window���Ǵ�ͳ��������Direct���ڣ���FaceUI�б���ֿ���Window��WindowImpl��
		��ͳ�Ĵ��ڣ���WindowControl���Ǵ��ڿؼ����봰���йص�Direct���Ի��߲���ȫ������WindowControl�С�
		WindowControlEvent��WindowControl��Window�ؼ�������Ϣʵ��.
	*/
	class FACE_API WindowImpl : public Face::Window, public Face::WindowControlEvent, public Face::WindowControl
	{
		friend class UIMgr;
	public:
		WindowImpl();
		virtual ~WindowImpl();

		// window���ڲ���
		void ShowWindow(bool bShow = true, bool bTakeFocus = true);
		fuint ShowModal();
		void Close(fuint ret = IDOK);
		void Center();
		void SetIcon(fuint res);
		void FullScreen();
		void RestoreFullScreen();
	private:
		LRESULT OnNcHitTest(WPARAM wParam, LPARAM lParam);
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
		void OnCreate(WPARAM wParam, LPARAM lParam);
		void OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam);
		void OnClose(WPARAM wParam, LPARAM lParam);
		void OnDestory(WPARAM wParam, LPARAM lParam);
		void OnNcCalcSize(WPARAM wParam, LPARAM lParam);
		void OnPaint(WPARAM wParam, LPARAM lParam);
		void OnSize(WPARAM param, LPARAM lParam);
	protected:
		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) final;
		// ������Ϣ
		virtual void OnWndCreated();
		virtual void OnWndDestory();
		virtual void OnWndInited();
		virtual void OnWndClosed();
		virtual void OnWndSized();
		virtual void OnWndChar(WPARAM code);
		virtual void OnWndKeyDown(WPARAM code);
		virtual void OnWndSysCommand(WPARAM code);
		virtual LRESULT OnWndPreprocessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
		virtual LRESULT OnWndHandleCustomeMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	protected:
		HDC hPaintDC_{ nullptr };
		Rect restoreFullRect_;
	};
}
#endif