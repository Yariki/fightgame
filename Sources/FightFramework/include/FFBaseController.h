#ifndef __FFBASECONTROLLER_H__
#define __FFBASECONTROLLER_H__


class FFBaseController
{
public:
	FFBaseController(){}
	virtual ~FFBaseController(){}


	virtual bool IsUp(bool& isNew) = 0;
	virtual bool IsDown(bool& isNew) = 0;
	virtual bool IsRight(bool& isNew) = 0;
	virtual bool IsLeft(bool& isNew) = 0;

};


#endif //__FFBASECONTROLLER_H__