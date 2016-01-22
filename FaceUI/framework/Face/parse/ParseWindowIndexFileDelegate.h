#ifndef _PARSEWINDOWINDEXFILEDELEGATE_H_
#define _PARSEWINDOWINDEXFILEDELEGATE_H_
/*
	����windows.xml�ļ��������õ�window�����Լ���Ӧ��xml�ļ�������templateobject
*/

class TemplateObject;
namespace Face
{
	using namespace std;
	class ParseResourceIndexFileDelegate : public Face::FaceObject, Face::FaceNotCopyable
	{
	public:
		ParseResourceIndexFileDelegate();
		virtual ~ParseResourceIndexFileDelegate();
	
	public:
		bool Parse(FaceString& _strPath);

	private:
		void _Parse(FaceString& _strPath);
	
	};
}
#endif //_PARSEWINDOWINDEXFILEDELEGATE_H_