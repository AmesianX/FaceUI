#pragma once
#ifndef _WINDOW_H_
#define _WINDOW_H_

namespace Face
{
	class FACE_API Window : public Face::NotCopyable
	{
		friend class UIMgr;
	public:
		Window();
		virtual ~Window();
		HWND GetHWND() const;
		operator HWND() const;

		const WString& GetWndClassName();

		// ��������
		LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
		LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);

	private:
		bool RegisterWndClass(LPCTSTR className, fuint style);
		bool SuperClass(LPCTSTR superClassName, LPCTSTR className);
		HWND Create(HWND hwndParent, LPCTSTR className, LPCTSTR pstrName, LPCTSTR superClassName = L"", DWORD dwStyle = UI_WNDSTYLE_FRAME, DWORD dwExStyle = UI_WNDSTYLE_EX_FRAME, fuint classStyle = UI_CLASSSTYLE_FRAME);
	protected:
		virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

		static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	private:
		HWND hWnd_{ nullptr };
		WNDPROC oldWndProc_;
		WString wndClassName_{ WString(L"") };
	};
}
#endif