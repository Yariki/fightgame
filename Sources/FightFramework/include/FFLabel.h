#ifndef __FFLABEL_H__
#define __FFLABEL_H__

#include "FFBaseControl.h"


#define LABEL_SECTION "Label"


class FFLabel : public FFBaseControl
{

public:
	FFLabel(FFBaseUiScene* parent, FFVector3& position, orxCHAR* name);
	virtual ~FFLabel();

	virtual void Update(orxOBJECT* obj){}

	void SetCaption(std::string& caption);

};

#endif