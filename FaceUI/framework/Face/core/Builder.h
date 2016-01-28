#pragma once
#ifndef _BUILDER_H_
#define _BUILDER_H_

namespace Face
{
	class Control;
	enum ParserType
	{
		FROM_NONE = 1,
		FROM_WNDCLASSNAME,
		FROM_XMLFILE,
		FROM_XMLCONTENT,
	};

	class FACE_API ICustomBuilder : public NotCopyable
	{
	public:
		virtual Control* CreateCustomControls(LPCTSTR pstrClass) = 0;
	};

	class FACE_API XMLBuilder : public Singleton<XMLBuilder>
	{
	public:
		XMLBuilder();
		virtual ~XMLBuilder();

		virtual void Init();
		virtual void Destory();

		/*
			psz: ����������xml�ļ�·����xml�ļ�����
		*/
		Control* Create(LPCTSTR psz, ICustomBuilder *customBuilder = nullptr);

	private:
		ParserType _GetParserType(LPCTSTR psz);
	};
}
#endif