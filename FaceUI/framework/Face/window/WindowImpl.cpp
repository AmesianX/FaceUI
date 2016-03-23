#include "stdafx.h"

namespace Face
{
	WindowImpl::WindowImpl()
	{}

	WindowImpl::~WindowImpl()
	{}

	void WindowImpl::OnCreate(WPARAM wParam, LPARAM lParam)
	{
		auto setting = UIMgr::getInstance()->GetWndConfig(GetWndClassName().Buffer());
		CHECK_ERROR(setting, L"Create window failed.");
		
		WindowControl::SetWndHWND(this->GetHWND());
		this->OnWndCreated();
	}

	LRESULT WindowImpl::OnNcHitTest(WPARAM wParam, LPARAM lParam)
	{
		POINT pt;
		pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
		::ScreenToClient(*this, &pt);

		RECT rcClient;
		::GetClientRect(*this, &rcClient);

		if (!::IsZoomed(*this))
		{
			RECT rcSizeBox = GetDragBorderSize();
			if (pt.y < rcClient.top + rcSizeBox.top)
			{
				if (pt.x < rcClient.left + rcSizeBox.left)
					return HTTOPLEFT;
				if (pt.x > rcClient.right - rcSizeBox.right)
					return HTTOPRIGHT;
				return HTTOP;
			}
			else if (pt.y > rcClient.bottom - rcSizeBox.bottom)
			{
				if (pt.x < rcClient.left + rcSizeBox.left)
					return HTBOTTOMLEFT;
				if (pt.x > rcClient.right - rcSizeBox.right)
					return HTBOTTOMRIGHT;
				return HTBOTTOM;
			}

			if (pt.x < rcClient.left + rcSizeBox.left)
				return HTLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right)
				return HTRIGHT;
		}

		RECT rcCaption = GetCaption();
		if (pt.x >= rcClient.left + rcCaption.left
			&& pt.x < rcClient.right - rcCaption.right
			&& pt.y >= rcCaption.top
			&& pt.y < rcCaption.bottom)
		{
			return HTCAPTION;
			/*CControlUI* pControl = static_cast<CControlUI*>(FindControl(pt));
			if (pControl != NULL && !pControl->IsClientArea())
			{
				// ����ǻ�ؼ�����Ҫ����HTCLIENT����Ӧ����¼�
				// ������ǣ��򷵻�HTCAPTION����������϶�
				return HTCAPTION;
			}*/
		}

		return HTCLIENT;
	}

	void WindowImpl::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam)
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &oMonitor);
		Rect rcWork = oMonitor.rcWork;
		Rect rcMonitor = oMonitor.rcMonitor;
		rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

		// �������ʱ����ȷ��ԭ������
		lpMMI->ptMaxPosition.x = rcWork.left;
		lpMMI->ptMaxPosition.y = rcWork.top;

		lpMMI->ptMaxTrackSize.x = rcWork.GetWidth();
		lpMMI->ptMaxTrackSize.y = rcWork.GetHeight();

		// TODO ʹ�ô������Կ�����С���ڳߴ�
		lpMMI->ptMinTrackSize.x = GetMinSize().cx;
		lpMMI->ptMinTrackSize.y = GetMinSize().cy;
	}

	void WindowImpl::OnClose(WPARAM wParam, LPARAM lParam)
	{
		::SetFocus(nullptr);
		HWND hwndParent = GetWindowOwner(*this);
		if (hwndParent != nullptr)
			::SetFocus(hwndParent);
		this->OnWndClosed();
	}

	void WindowImpl::OnDestory(WPARAM wParam, LPARAM lParam)
	{
		::ReleaseDC(*this, hPaintDC_);
		hPaintDC_ = nullptr;
	}

	void WindowImpl::OnNcCalcSize(WPARAM wParam, LPARAM lParam)
	{
		LPRECT pRect = nullptr;

		if (wParam == TRUE)
		{
			LPNCCALCSIZE_PARAMS pParam = (LPNCCALCSIZE_PARAMS)lParam;
			pRect = &pParam->rgrc[0];
		}
		else
		{
			pRect = (LPRECT)lParam;
		}

		if (::IsZoomed(*this))
		{	
			// ���ʱ�����㵱ǰ��ʾ�����ʺϿ�߶�
			// Win7��Ļ��չģʽ���ᳬ���߽�
			MONITORINFO oMonitor = {};
			oMonitor.cbSize = sizeof(oMonitor);
			::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &oMonitor);
			Rect rcWork = oMonitor.rcWork;
			Rect rcMonitor = oMonitor.rcMonitor;
			rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

			pRect->right = pRect->left + rcWork.GetWidth();
			pRect->bottom = pRect->top + rcWork.GetHeight();
		}
	}

	void WindowImpl::OnPaint(WPARAM wParam, LPARAM lParam)
	{}

	void WindowImpl::OnSize(WPARAM param, LPARAM lParam)
	{
		Size round = GetRoundCorner();
		if (!::IsIconic(*this) && (round.cx != 0 || round.cy != 0)) 
		{
			Rect rcWnd;
			::GetClientRect(*this, &rcWnd);
			rcWnd.Offset(-rcWnd.left, -rcWnd.top);
			rcWnd.right++; rcWnd.bottom++;
			HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, round.cx, round.cy);
			::SetWindowRgn(*this, hRgn, TRUE);
			::DeleteObject(hRgn);
			this->OnWndSized();
		}
	}

	LRESULT WindowImpl::WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (!::IsWindow(*this))
		{
			return false;
		}

		bool bHandled = false;
		LRESULT lRes = this->HandleMessage(uMsg, wParam, lParam, bHandled);
		if (bHandled == true)
		{
			return lRes;
		}
		lRes = this->OnWndHandleCustomeMessage(uMsg, wParam, lParam, bHandled);
		if (bHandled == true)
		{
			return lRes;
		}

		return __super::WindowProc(uMsg, wParam, lParam);
	}

	LRESULT WindowImpl::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
	{
		LRESULT lRes = S_OK;
		switch (uMsg)
		{
			case WM_CREATE:
			{
				OnCreate(wParam, lParam);
				bHandled = true;
				break;
			}
			case WM_CLOSE:
			{
				OnClose(wParam, lParam);
				break;
			}
			case WM_DESTROY:
			{
				OnDestory(wParam, lParam);
				lRes = S_FALSE;
				break;
			}
			case WM_NCACTIVATE:
			{
				bHandled = true;
				if (wParam == FALSE)
				{
					lRes = S_FALSE;
				}
				break;
			}
			case WM_NCCALCSIZE:
			{
				OnNcCalcSize(wParam, lParam);
				bHandled = true;
				if (::IsZoomed(*this))
				{
					return WVR_REDRAW;
				}
				break;
			}
			case WM_NCPAINT:
			{
				bHandled = false;
				break;
			}
			case WM_PAINT:
			{
				OnPaint(wParam, lParam);
				bHandled = true;
				break;
			}
			case WM_ERASEBKGND:
			{
				bHandled = true;
				lRes = S_FALSE;
				break;
			}
			case WM_NCHITTEST:	
			{
				bHandled = true;
				return OnNcHitTest(wParam, lParam);
				break;
			}
			case WM_GETMINMAXINFO:	
			{
				OnGetMinMaxInfo(wParam, lParam);
				bHandled = true;
				break;
			}
			case WM_SIZE:			
			{
				OnSize(wParam, lParam);
				bHandled = true;
				break;
			}
			case WM_TIMER:
				break;
			case WM_SETCURSOR:
			{
				if (LOWORD(lParam) != HTCLIENT)
					break;
				if (IsCapture())
				{
					bHandled = true;
					return TRUE;
				}
				// TODO����ؼ������¼�
				bHandled = true;
				break;
			}
			case WM_CHAR:	
				OnWndChar(wParam);
				break;
			case WM_SYSCOMMAND:		
				if (wParam == SC_CLOSE)
				{
					SendMessage(WM_CLOSE);
				}
				OnWndSysCommand(wParam);
				bHandled = true;
				break;
			case WM_KEYUP:
				// TODO����ؼ������¼�
				bHandled = true;
				break;
			case WM_KEYDOWN:
				OnWndKeyDown(wParam);
				bHandled = true;
				break;
			case WM_LBUTTONUP:	
				// TODO:��ؼ������¼�
				bHandled = true;
				break;
			case WM_LBUTTONDOWN:
				// TODO:��ؼ������¼�
				bHandled = true;
				break;
			case WM_LBUTTONDBLCLK:
				// TODO:��ؼ������¼�
				bHandled = true;
				break;
			case WM_RBUTTONDOWN:
				// TODO:��ؼ������¼�
				bHandled = true;
				break;
			case  WM_RBUTTONUP:
				// TODO:��ؼ������¼�
				bHandled = true;
				break;
			case WM_RBUTTONDBLCLK:
				// TODO:��ؼ������¼�
				bHandled = true;
				break;
			case WM_MOUSEWHEEL:
				// TODO:��ؼ������¼�
				bHandled = true;
				break;
			case WM_MOUSEMOVE:	
				// TODO:��ؼ������¼�
				bHandled = true;
				break;
			case WM_MOUSEHOVER:	
				// TODO:��ؼ������¼�
				bHandled = true;
				break;
			case WM_MOUSELEAVE:
				bHandled = true;
				break;
			case WM_NCCREATE:
			{
				this->OnWndCreated();
				break;
			}
			case WM_NCDESTROY:
			{
				this->OnWndDestory();
				break; 
			}
			default:				
				bHandled = false; 
				break;
		}

		return lRes;
	}

	// ���ڹرղ���
	void WindowImpl::OnWndClosed()
	{}

	// ���ڴ�����ɣ�����ֻ����FindControl����
	void WindowImpl::OnWndCreated()
	{}

	void WindowImpl::OnWndInited()
	{}

	// ��������
	void WindowImpl::OnWndDestory()
	{}

	// ���ڳߴ�ı���Ϣ
	void WindowImpl::OnWndSized()
	{
		// TODO����������ؼ����ʹ�С�ı����Ϣ
	}

	// �����ַ�����Ϣ
	void WindowImpl::OnWndChar(WPARAM code)
	{}

	// ������Ϣ
	void WindowImpl::OnWndKeyDown(WPARAM code)
	{}

	void WindowImpl::OnWndSysCommand(WPARAM code)
	{}

	LRESULT WindowImpl::OnWndPreprocessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
	{
		bHandled = false;
		return 0;
	}

	LRESULT WindowImpl::OnWndHandleCustomeMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
	{
		bHandled = false;
		return 0;
	}

	void WindowImpl::ShowWindow(bool bShow/* = true */, bool bTakeFocus/* = true */)
	{
		CHECK_ERROR(::IsWindow(*this), L"Not window");
		::ShowWindow(*this, bShow ? (bTakeFocus ? SW_SHOWNORMAL : SW_SHOWNOACTIVATE) : SW_HIDE);
	}

	fuint WindowImpl::ShowModal()
	{
		HWND hWnd = this->GetHWND();
		CHECK_ERROR(::IsWindow(hWnd), L"Not window");
		fuint ret = 0;
		HWND hWndParent = ::GetWindowOwner(hWnd);
		::ShowWindow(hWnd, SW_SHOWNORMAL);	//��������ʾ����
		::EnableWindow(hWndParent, FALSE);	//Ȼ�󽫸��������ò�����
		MSG msg = { 0 };
		//��Ϣѭ����������ʾ�����Ĵ�������������Ϣ
		while (::IsWindow(hWnd) && ::GetMessage(&msg, NULL, 0, 0))
		{
			if (msg.message == WM_CLOSE && msg.hwnd == hWnd)
			{
				ret = msg.wParam;
				::EnableWindow(hWndParent, TRUE);
				::SetFocus(hWndParent);
			}
			// ��Ϣ��ת
			/*if (!CPaintManagerUI::TranslateMessage(&msg))
			{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			}*/

			if (msg.message == WM_QUIT)	//һ���ڶ������յ��˳�����Ϣ���ж���Ϣѭ���������˳�
				break;
		}
		::EnableWindow(hWndParent, TRUE);	//˵����ʾ�Ĵ���Ҫ�˳���Ȼ�󽫸���������Ϊ����
		::SetFocus(hWndParent);	//���ø����ڽ���
								//�˳�
		if (msg.message == WM_QUIT)
			::PostQuitMessage(msg.wParam);
		return ret;
	}

	void WindowImpl::Close(fuint ret/* = IDOK */)
	{
		CHECK_ERROR(::IsWindow(*this), L"Not window");
		PostMessage(WM_CLOSE, (WPARAM)ret, 0L);
	}

	void WindowImpl::Center()
	{
		HWND hWnd = *this;
		CHECK_ERROR(::IsWindow(hWnd), L"Not window");
		CHECK_ERROR((GetWindowStyle(hWnd) & WS_CHILD) == 0, L"It's be child");

		RECT rcDlg = { 0 };
		::GetWindowRect(hWnd, &rcDlg);
		RECT rcArea = { 0 };
		RECT rcCenter = { 0 };
		
		HWND hWndParent = ::GetParent(hWnd);
		HWND hWndCenter = ::GetWindowOwner(hWnd);
		if (hWndCenter != nullptr)
			hWnd = hWndCenter;

		// �������ʾ��ģʽ����Ļ����
		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &oMonitor);
		rcArea = oMonitor.rcWork;

		if (hWndCenter == nullptr)
			rcCenter = rcArea;
		else
			::GetWindowRect(hWndCenter, &rcCenter);

		int dlgWidth = rcDlg.right - rcDlg.left;
		int dlgHeight = rcDlg.bottom - rcDlg.top;

		// Find dialog's upper left based on rcCenter
		int xLeft = (rcCenter.left + rcCenter.right) / 2 - dlgWidth / 2;
		int yTop = (rcCenter.top + rcCenter.bottom) / 2 - dlgHeight / 2;

		// The dialog is outside the screen, move it inside
		if (xLeft < rcArea.left)
			xLeft = rcArea.left;
		else if (xLeft + dlgWidth > rcArea.right)
			xLeft = rcArea.right - dlgWidth;

		if (yTop < rcArea.top)
			yTop = rcArea.top;
		else if (yTop + dlgHeight > rcArea.bottom)
			yTop = rcArea.bottom - dlgHeight;

		::SetWindowPos(hWnd, nullptr, xLeft, yTop, -1, -1, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	void WindowImpl::SetIcon(fuint res)
	{
		HICON hIcon = (HICON)::LoadImage(App::getInstance()->GetAppInstance(), MAKEINTRESOURCE(res), IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
		CHECK_ERROR(hIcon, L"Icon handler is null");
		::SendMessage(*this, WM_SETICON, (WPARAM)TRUE, (LPARAM)hIcon);
		hIcon = (HICON)::LoadImage(App::getInstance()->GetAppInstance(), MAKEINTRESOURCE(res), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
		CHECK_ERROR(hIcon, L"Icon handler is null");
		::SendMessage(*this, WM_SETICON, (WPARAM)FALSE, (LPARAM)hIcon);
	}

	void WindowImpl::FullScreen()
	{
		::GetClientRect(*this, &restoreFullRect_);
		Point point;
		::ClientToScreen(*this, &point);
		restoreFullRect_.left = point.x;
		restoreFullRect_.top = point.y;
		restoreFullRect_.right += point.x;
		restoreFullRect_.bottom += point.y;
		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTONEAREST), &oMonitor);
		Rect rcWork = oMonitor.rcWork;

		::SetWindowPos(*this, nullptr, rcWork.left, rcWork.top, rcWork.GetWidth(), rcWork.GetHeight(), SWP_SHOWWINDOW | SWP_NOZORDER);
	}

	void WindowImpl::RestoreFullScreen()
	{
		::SetWindowPos(*this, NULL, restoreFullRect_.left, restoreFullRect_.top, restoreFullRect_.GetWidth(), restoreFullRect_.GetHeight(), SWP_SHOWWINDOW | SWP_NOZORDER);
	}
}