#include "AudioDeviceOutputCV.h"

#include <Tools/Range.h>
AudioDevice::OutputCV::OutputCV()
   : OutputRaw()
   , value(0.0)
{
}

AudioDevice::OutputCV::OutputCV(Driver* driver, const Channel& channel)
   : OutputCV()
{
   activate(driver, channel);
}

void AudioDevice::OutputCV::setVoltage(const float& newVoltage)
{
   value = Range::clamp(0.1 * newVoltage, -1.0, 1.0);
}

void AudioDevice::OutputCV::process(OutputBuffer& outputBuffer)
{
   const Frame& noOfFrames = outputBuffer.getNoOfFrames();
   for (Frame frame = 0; frame < noOfFrames; frame++)
      outputBuffer[frame] = value;
}
