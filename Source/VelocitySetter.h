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
//  VelocitySetter.h
//  modularSynth
//
//  Created by Ryan Challinor on 5/16/13.
//
//

#ifndef __modularSynth__VelocitySetter__
#define __modularSynth__VelocitySetter__

#include <iostream>
#include "NoteEffectBase.h"
#include "IDrawableModule.h"
#include "Checkbox.h"
#include "Slider.h"

class VelocitySetter : public NoteEffectBase, public IDrawableModule, public IFloatSliderListener
{
public:
   VelocitySetter();
   static IDrawableModule* Create() { return new VelocitySetter(); }
   
   string GetTitleLabel() override { return "velocity"; }
   void CreateUIControls() override;

   void SetEnabled(bool enabled) override { mEnabled = enabled; }

   //INoteReceiver
   void PlayNote(double time, int pitch, int velocity, int voiceIdx = -1, ModulationParameters modulation = ModulationParameters()) override;

   void CheckboxUpdated(Checkbox* checkbox) override;
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override {}
   
   virtual void LoadLayout(const ofxJSONElement& moduleInfo) override;
   virtual void SetUpFromSaveData() override;
   
   
private:
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& width, float& height) override { width = 90; height = 38; }
   bool Enabled() const override { return mEnabled; }
   
   float mVelocity;
   FloatSlider* mVelocitySlider;
   float mRandomness;
   FloatSlider* mRandomnessSlider;
};


#endif /* defined(__modularSynth__VelocitySetter__) */

