#ifndef __FFPREVIEW_H__
#define __FFPREVIEW_H__

#include "FFBaseControl.h"
#include "display\orxGraphic.h"

#define PREVIEW_SECTION "Preview"
#define PREVIEW_CAPTION "PreviewCaption"



class FFPreview : public FFBaseControl
{
protected:
    bool _onlyOnce;
    orxVECTOR _scale;
    int _number;
    orxCHAR _filePreview[MAX_NAME];
public:
    FFPreview(FFBaseUiScene* parent,orxVECTOR& position, orxCHAR* name,const orxCHAR* filepreview, int number);
    virtual ~FFPreview();

public:
    void Update(orxOBJECT* obj);
    void SetScale(orxVECTOR* scale);
    int GetNumber() { return _number;}
};


#endif //__FFPREVIEW_H__