#ifndef _PARSEWINDOWINDEXFILEDELEGATE_H_
#define _PARSEWINDOWINDEXFILEDELEGATE_H_
/*
	����windows.xml�ļ��������õ�window�����Լ���Ӧ��xml�ļ�������templateobject
*/

class TemplateObject;
namespace Face
{
	using namespace std;
	class ParseResourceIndexFileDelegate : public Object, Face::NotCopyable
	{
	public:
		ParseResourceIndexFileDelegate();
		virtual ~ParseResourceIndexFileDelegate();
	
	public:
		bool Parse(String& _strPath);

	private:
		void _Parse(String& _strPath);
	
	};
}
#endif //_PARSEWINDOWINDEXFILEDELEGATE_H_