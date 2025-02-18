/**
    bespoke synth, a software modular synthesizer
    Copyright (C) 2021 Ryan Challinor (contact: awwbees@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
//
//  TextEntry.h
//  modularSynth
//
//  Created by Ryan Challinor on 12/5/12.
//
//

#ifndef __modularSynth__TextEntry__
#define __modularSynth__TextEntry__

#include <iostream>
#include <climits>
#include "IUIControl.h"
#include "SynthGlobals.h"

class TextEntry;

class ITextEntryListener
{
public:
   virtual ~ITextEntryListener() {}
   virtual void TextEntryComplete(TextEntry* entry) = 0;
   virtual void TextEntryCancelled(TextEntry* entry) {}
   virtual void TextEntryActivated(TextEntry* entry) {}
};

enum TextEntryType
{
   kTextEntry_Text,
   kTextEntry_Int,
   kTextEntry_Float
};

class IKeyboardFocusListener
{
public:
   virtual ~IKeyboardFocusListener() {}
   static void SetActiveKeyboardFocus(IKeyboardFocusListener* focus) { sCurrentKeyboardFocus = focus; }
   static IKeyboardFocusListener* GetActiveKeyboardFocus() { return sCurrentKeyboardFocus; }
   static void ClearActiveKeyboardFocus(bool notifyListeners);
   
   virtual void OnKeyPressed(int key, bool isRepeat) = 0;
private:
   virtual void AcceptEntry(bool pressedEnter) {}
   virtual void CancelEntry() {}
   static IKeyboardFocusListener* sCurrentKeyboardFocus;
};

class TextEntry : public IUIControl, public IKeyboardFocusListener
{
public:
   TextEntry(ITextEntryListener* owner, const char* name, int x, int y, int charWidth, char* var);
   TextEntry(ITextEntryListener* owner, const char* name, int x, int y, int charWidth, string* var);
   TextEntry(ITextEntryListener* owner, const char* name, int x, int y, int charWidth, int* var, int min, int max);
   TextEntry(ITextEntryListener* owner, const char* name, int x, int y, int charWidth, float* var, float min, float max);
   void OnKeyPressed(int key, bool isRepeat) override;
   void Render() override;
   void Delete() override;
   
   void MakeActiveTextEntry(bool setCaretToEnd);
   
   void SetNextTextEntry(TextEntry* entry);
   void UpdateDisplayString();
   void SetInErrorMode(bool error) { mInErrorMode = error; }
   void DrawLabel(bool draw) { mDrawLabel = draw; }
   void SetRequireEnter(bool require) { mRequireEnterToAccept = require; }
   void SetFlexibleWidth(bool flex) { mFlexibleWidth = flex; }
   void ClearInput() { bzero(mString, MAX_TEXTENTRY_LENGTH); mCaretPosition = 0; }
   const char* GetText() const { return mString; }
   
   void GetDimensions(float& width, float& height) override;

   //IUIControl
   void SetFromMidiCC(float slider, bool setViaModulator = false) override {}
   void SetValue(float value) override;
   void Increment(float amount) override;
   void SaveState(FileStreamOut& out) override;
   void LoadState(FileStreamIn& in, bool shouldSetValue = true) override;
   bool IsSliderControl() override { return false; }
   bool IsButtonControl() override { return false; }
   bool IsTextEntry() const override { return true; }
   
protected:
   ~TextEntry();   //protected so that it can't be created on the stack
   
private:
   void Construct(ITextEntryListener* owner, const char* name, int x, int y, int charWidth);  //shared constructor
   
   void AddCharacter(char c);
   bool AllowCharacter(char c);
   void AcceptEntry(bool pressedEnter) override;
   void CancelEntry() override;
   
   void OnClicked(int x, int y, bool right) override;
   bool MouseMoved(float x, float y) override;
   
   int mCharWidth;
   ITextEntryListener* mListener;
   char mString[MAX_TEXTENTRY_LENGTH];
   char* mVarCString;
   string* mVarString;
   int* mVarInt;
   float* mVarFloat;
   int mIntMin;
   int mIntMax;
   float mFloatMin;
   float mFloatMax;
   int mCaretPosition;
   float mCaretBlinkTimer;
   bool mCaretBlink;
   TextEntryType mType;
   TextEntry* mNextTextEntry;
   TextEntry* mPreviousTextEntry;
   bool mInErrorMode;
   bool mDrawLabel;
   float mLabelSize;
   bool mFlexibleWidth;
   bool mHovered;
   bool mRequireEnterToAccept;
};

#endif /* defined(__modularSynth__TextEntry__) */
