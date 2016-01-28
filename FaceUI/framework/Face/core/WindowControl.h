#pragma once
#ifndef _PAINTMANAGER_H_
#define _PAINTMANAGER_H_

namespace Face
{
	/*
		window ��ķָ��Direct Window�ָ�ɴ�ͳ�������Window�ؼ�
		ǰ�ߴ���Window�������ݣ����ߴ��������������Ӧ�ĸ������Ժ���Ϣ��
	*/ 
	class FACE_API WindowControl : public NotCopyable
	{
	public:
		WindowControl();
		~WindowControl();

		void OnWndCreated(HWND hwnd);
		
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

		void SetCapture();
		void ReleaseCapture();
		bool IsCapture();
	private:
		HWND hPaintWnd_{ nullptr };
		bool isCapture_{ false };

		// �¼�
	};
}
#endif //_PAINTMANAGER_H_