#pragma once
#ifndef _CONTROL_H_
#define _CONTROL_H_

namespace Face
{
	class FACE_API Control : public NotCopyable
	{
	public:
		Control();
		virtual ~Control();

		OBJECT_CREATE(Control);

		/*
			�ڲ��¼�ת�����ⲿ�¼�
		*/
	};
}
#endif //_CONTROL_H_