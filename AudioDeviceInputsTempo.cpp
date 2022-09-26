#include "AudioDeviceInputsTempo.h"

AudioDevice::InputsTempo::InputsTempo(Driver* driver, const Channel& channelClock, const Channel& channelReset)
   : TempoControl()
   , clockInput(driver, channelClock)
   , resetInput(driver, channelReset)
   , tickActive(false)
   , tickFunctionList()
   , resetFunctionList()
{
}

void AudioDevice::InputsTempo::advance(const float callackRate, const float allowedTickPercentage)
{
   if (resetInput.isOn())
   {
      clockReset();
      for (ClockFunction& clockFunction : resetFunctionList)
         clockFunction();

      tickActive = false;
   }
   else if (clockInput.isOn())
   {
      if (!tickActive)
      {
         clockTick();
         for (ClockFunction& clockFunction : tickFunctionList)
            clockFunction();
      }
      tickActive = true;
   }
   else
   {
      TempoControl::advance(callackRate, allowedTickPercentage);
      tickActive = false;
   }
}
