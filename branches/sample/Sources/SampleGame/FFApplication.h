#ifndef __FFAPPLICATION_H_
#define __FFAPPLICATION_H_



#include "FFInclude.h"
#include "FFGameManager.h"


class FFApplication
{
protected:
	FFApplication(void);
	FFApplication(const FFApplication&);
	FFApplication& operator=(const FFApplication&);


	virtual ~FFApplication(void);

public:
	static FFApplication* instance();
	static void		 orxFASTCALL Update(const orxCLOCK_INFO* pClockInfo,void* pContext);
	static orxSTATUS orxFASTCALL Init();
	static orxSTATUS orxFASTCALL Run();
	static void		 orxFASTCALL Exit();

	static orxSTATUS orxFASTCALL UserEventHandler(const orxEVENT* pEvent);
	

public:
	void Load();
	void Main(int argc, char** argv);
	void UserEvent(const orxEVENT* pEvent);
	void UpdateAll(const orxCLOCK_INFO* pClockInfo);

public:
	FFGameManager* _manager;


private:
	static FFApplication*	_instance;

};

#endif //__FFAPPLICATION_H_