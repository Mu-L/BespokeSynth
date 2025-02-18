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
//  FreqDelay.h
//  modularSynth
//
//  Created by Ryan Challinor on 5/10/13.
//
//

#ifndef __modularSynth__FreqDelay__
#define __modularSynth__FreqDelay__

#include <iostream>
#include "IAudioProcessor.h"
#include "IDrawableModule.h"
#include "INoteReceiver.h"
#include "DelayEffect.h"
#include "Slider.h"

class FreqDelay : public IAudioProcessor, public IDrawableModule, public INoteReceiver, public IFloatSliderListener
{
public:
   FreqDelay();
   virtual ~FreqDelay();
   static IDrawableModule* Create() { return new FreqDelay(); }
   
   string GetTitleLabel() override { return "freq delay"; }
   void CreateUIControls() override;

   //IAudioSource
   void Process(double time) override;

   //INoteReceiver
   void PlayNote(double time, int pitch, int velocity, int voiceIdx = -1, ModulationParameters modulation = ModulationParameters()) override;
   void SendCC(int control, int value, int voiceIdx = -1) override {}
   
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override;
   
   virtual void LoadLayout(const ofxJSONElement& moduleInfo) override;
   virtual void SetUpFromSaveData() override;
   
private:
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& width, float& height) override { width = 130; height = 120; }
   bool Enabled() const override { return true; }

   ChannelBuffer mDryBuffer;
   float mDryWet;
   FloatSlider* mDryWetSlider;

   DelayEffect mDelayEffect;
};

#endif /* defined(__modularSynth__FreqDelay__) */

