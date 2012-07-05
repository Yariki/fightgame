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
public:
    FFPreview(FFBaseUiScene* parent,orxVECTOR& position, orxCHAR* name);
    virtual ~FFPreview();

public:
    void Update(orxOBJECT* obj);
    void SetScale(orxVECTOR* scale);
};


#endif //__FFPREVIEW_H__