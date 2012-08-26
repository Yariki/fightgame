#ifndef __FFPREVIEW_H__
#define __FFPREVIEW_H__

#include "FFBaseControl.h"
#include "display\orxGraphic.h"

#define PREVIEW_SECTION "Preview"
#define PREVIEW_CAPTION "PreviewCaption"

#define  MAX_LINK_OBJECT 2

class FFPreview : public FFBaseControl
{
protected:
    bool _onlyOnce;
    FFVector3 _scale;
    int _number;
    orxCHAR _filePreview[MAX_NAME];
	std::vector<orxOBJECT*> _listLink;
	

	ITEMCHOOSE	_OnChoose;

public:
    FFPreview(FFBaseUiScene* parent,FFVector3& position, orxCHAR* name,const orxCHAR* filepreview, ITEMCHOOSE onitemchoose, int number);
    virtual ~FFPreview();

public:
    void Update(orxOBJECT* obj);
    void SetScale(FFVector3* scale);
    int GetNumber() { return _number;}

	bool LinkObject(orxOBJECT* obj);
	bool UnlinkObject(orxOBJECT* obj);

private:
	template<typename T>
	void remove(std::vector<T>* vec, size_t pos);

};


#endif //__FFPREVIEW_H__