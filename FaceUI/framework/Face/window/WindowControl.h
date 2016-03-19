#pragma once
#ifndef _PAINTMANAGER_H_
#define _PAINTMANAGER_H_

namespace Face
{
	/*
		window ��ķָ��Direct Window�ָ�ɴ�ͳ�������Window�ؼ�
		ǰ�ߴ���Window�������ݣ����ߴ��������������Ӧ�ĸ������Ժ���Ϣ��
	*/ 
	class Size;
	class FACE_API WindowControl : public NotCopyable
	{
	public:
		WindowControl();
		~WindowControl();

		void SetWndHWND(HWND hwnd);
		void SetAttribute(LPCTSTR key, LPCTSTR value);

		// ���϶��ı䴰�ڴ�С�ı߾�
		SYNTHESIZE_PRI_CONST_REF(Rect, dragBorderSize_, DragBorderSize);
		// ���϶��ı�������С�ı߾�
		SYNTHESIZE_PRI_CONST_REF(Rect, caption_, Caption);
		// ��������С
		SYNTHESIZE_PRI_CONST_REF(Size, maxSize_, MaxSize);
		// ������С��С
		SYNTHESIZE_PRI_CONST_REF(Size, minSize_, MinSize);
		// ����Բ�Ǵ�С
		SYNTHESIZE_PRI_CONST_REF(Size, roundCorner_, RoundCorner);

		SYNTHESIZE_PRI(Control*, rootControl_, RootControl);

		void SetWindowSize(int cx, int cy);
		const Size* GetWindowSize();

		void SetCapture();
		void ReleaseCapture();
		bool IsCapture();
	private:
		HWND hPaintWnd_{ nullptr };
		bool isCapture_{ false };
		Size wndSize_;

		// �¼�
	};
}
#endif //_PAINTMANAGER_H_