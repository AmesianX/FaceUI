
#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#pragma once

namespace Face
{
	class Control;
	class WndConfig;
	class WindowImpl;
	class MessageListener;
	class WindowControlEvent;

	// �û�����ʵ���Լ��Զ���ؼ��Ĵ����ӿ�
	class FACE_API ICustomBuilder : public NotCopyable
	{
	public:
		virtual Control* CreateCustomControls(LPCTSTR pstrClassName) = 0;
	};

	class FACE_API ITranslateAccelerator : public NotCopyable
	{
	public:
		virtual LRESULT TranslateAccelerator(MSG *pMsg) = 0;
	};

	/*
		FaceUI�д��ںͿؼ��Ĺ�����
		��Ϣת����
		�ṩ�˼��ټ���Ϣ�����б������¼��б��Լ��������ؼ������б�
	*/
	class FACE_API UIMgr : public Singleton<UIMgr>
	{
	public:
		template<typename T>
		class ControlFactory
		{
		public:
			ControlFactory(const WString& key)
			{
				UIMgr::getInstance()->regControlsMap_->emplace(key, []()->Control* {return new T; });
			}
		};

		typedef Control* (_cdecl *CONTROL_CREATER)();
		typedef std::list<ITranslateAccelerator*> MsgAcceleratorList;
		typedef std::map<WString, WndConfig*> WndsConfigMap;
		typedef std::map<HWND, WindowControlEvent*> WndsEventMap;
		typedef std::map<WString, std::function<Control*()> > ControlsMap;

		virtual void Init(); 
		virtual void Destory();

		void AddWndConfig(LPCTSTR wndClassName, WndConfig* _pWo);
		WndConfig* GetWndConfig(LPCTSTR wndClassName);
		WndConfig* GetMainWndConfig();
		void MessageLoop();

		void RegisterTranslateAccelerator(ITranslateAccelerator *acclerator);
		void RemoveTranslateAccelerator(ITranslateAccelerator *acclerator);
		bool TranslateMessage(const LPMSG pMsg);
		void TranslateAccelerator(MSG *msg);

		bool RegisterWndEvent(HWND hwnd, WindowControlEvent *event);
		bool RemoveWndEvent(HWND hwnd);
		bool RemoveWndEvent(WindowControlEvent *event);

		void NotifyHandler(HWND hwnd, Control* notifyControl, NOTIFY msg, WPARAM wParam = 0, LPARAM lParam = 0);

		void ShowWindow(LPCTSTR wndClassName, bool bShow = true, bool bTakeFocus = true);
		fuint ShowModal(HWND hParent, LPCTSTR wndClassName);
		void CloseWindow(LPCTSTR wndClassName, fuint ret = IDOK);

		void OnWndFinalMessage(LPCTSTR wndClassName);
		void RegisterCustomControlsBuilder(ICustomBuilder *creater);
		Control* CreateControl(LPCTSTR pszType);
	private:
		WindowControlEvent* GetWndEvent(HWND hwnd);
	private:
		WndsConfigMap		*wndsConfigMap_{ nullptr };
		MsgAcceleratorList	*acceleratorList_{ nullptr };
		WndsEventMap		*eventMap_{ nullptr };
		ICustomBuilder		*customBuilder_{ nullptr };
		ControlsMap			*regControlsMap_{ nullptr };
	};
}

#define REGISTER_VALUE_NAME(T) reg_msg_##T##_
#define REGISTER_CREATER(T, key) Face::UIMgr::ControlFactory<T> REGISTER_VALUE_NAME(T)(key);

#endif //_WINDOWMANAGER_H_