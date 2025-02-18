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
//  PitchDive.h
//  Bespoke
//
//  Created by Ryan Challinor on 12/27/15.
//
//

#ifndef __Bespoke__PitchDive__
#define __Bespoke__PitchDive__

#include "NoteEffectBase.h"
#include "IDrawableModule.h"
#include "Slider.h"
#include "Checkbox.h"
#include "ModulationChain.h"
#include "Transport.h"

class PitchDive : public NoteEffectBase, public IDrawableModule, public IFloatSliderListener
{
public:
   PitchDive();
   virtual ~PitchDive();
   static IDrawableModule* Create() { return new PitchDive(); }
   
   string GetTitleLabel() override { return "pitchdive"; }
   void CreateUIControls() override;
   void SetEnabled(bool enabled) override { mEnabled = enabled; }
   
   //INoteReceiver
   void PlayNote(double time, int pitch, int velocity, int voiceIdx = -1, ModulationParameters modulation = ModulationParameters()) override;
   
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override;
   void CheckboxUpdated(Checkbox* checkbox) override;
   
   void LoadLayout(const ofxJSONElement& moduleInfo) override;
   void SetUpFromSaveData() override;
private:
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& width, float& height) override { width = 120; height = 40; }
   bool Enabled() const override { return mEnabled; }
   
   float mStart;
   FloatSlider* mStartSlider;
   float mTime;
   FloatSlider* mTimeSlider;

   Modulations mModulation;
};

#endif /* defined(__Bespoke__PitchDive__) */
