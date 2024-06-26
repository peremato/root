// @(#)root/gl:$Id$
// Author:  Matevz Tadel, Jun 2007

/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TGLClipSetEditor
#define ROOT_TGLClipSetEditor

#include "TGedFrame.h"
#include "TGLUtil.h"

#include "TGLClip.h"

class TGButton;
class TGCheckButton;
class TGNumberEntry;
class TGButtonGroup;


class TGLClipSetSubEditor : public TGVerticalFrame
{
private:
   TGLClipSetSubEditor(const TGLClipSetSubEditor&) = delete;
   TGLClipSetSubEditor& operator=(const TGLClipSetSubEditor&) = delete;

protected:
   TGLClipSet       *fM;

   TGLClip::EType    fCurrentClip;
   TGButtonGroup    *fTypeButtons;

   TGCompositeFrame *fPlanePropFrame;
   TGNumberEntry    *fPlaneProp[4];

   TGCompositeFrame *fBoxPropFrame;
   TGNumberEntry    *fBoxProp[6];
   TGCheckButton    *fClipInside;
   TGCheckButton    *fAutoUpdate;
   TGCheckButton    *fClipEdit;
   TGCheckButton    *fClipShow;
   TGButton         *fApplyButton;
   TGButton         *fResetButton;

public:
   TGLClipSetSubEditor(const TGWindow* p);
   ~TGLClipSetSubEditor() override {}

   void SetModel(TGLClipSet* m);

   void Changed(); //*SIGNAL*

   //Clipping manipulation
   void ClipValueChanged();
   void ClipTypeChanged(Int_t);
   void UpdateViewerClip();
   void ResetViewerClip();

   ClassDefOverride(TGLClipSetSubEditor, 0); // Sub-editor for TGLClipSet.
};


class TGLClipSetEditor : public TGedFrame {

private:
   TGLClipSetEditor(const TGLClipSetEditor&) = delete;
   TGLClipSetEditor& operator=(const TGLClipSetEditor&) = delete;

protected:
   TGLClipSet           *fM;  // fModel dynamic-casted to TGLClipSet
   TGLClipSetSubEditor  *fSE;

public:
   TGLClipSetEditor(const TGWindow *p = nullptr, Int_t width=170, Int_t height=30, UInt_t options=kChildFrame, Pixel_t back=GetDefaultFrameBackground());
   ~TGLClipSetEditor() override {}

   void SetModel(TObject* obj) override;

   ClassDefOverride(TGLClipSetEditor, 0); // GUI editor for TGLClipSet.
};

#endif
