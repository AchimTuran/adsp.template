/*
 *      Copyright (C) 2005-2016 Team Kodi
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */



#include "PostProcessGain/PostProcessGain.hpp"

#include "ADSPHelpers.h"
#include "include/client.h"

using namespace ADDON;


const std::string CPostProcessGainModeName::ModeName = CADSPModeInfos::Strs[CADSPModeInfos::ADSP_MODE_ID_PORTPROCESS_GAIN];


CPostProcessGain::CPostProcessGain()
{
  m_MainGain = 1.0f;
}


CPostProcessGain::~CPostProcessGain()
{
}


AE_DSP_ERROR CPostProcessGain::ModeCreate(const AE_DSP_SETTINGS &Settings, const AE_DSP_STREAM_PROPERTIES &Properties)
{
  m_InChannels            = Settings.iInChannels;
  m_InChannelPresentFlags = Settings.lInChannelPresentFlags;

  // reset used channel mapping array
  for (int ch = 0; ch < AE_DSP_CH_MAX; ch++)
  {
    m_ChannelMappingIdx[ch] = -1;
    m_ChannelMappingFlags[ch] = 0;
  }

  // add used channels to channel mapping array
  int lastAudioChannel = 0;
  for (int ch = 0; ch < m_InChannels; ch++)
  {
    unsigned long tempChannelFlag = 1 << lastAudioChannel;
    m_ChannelMappingIdx[ch] = CADSPHelpers::GetNextChID(m_InChannelPresentFlags,
                                                        CADSPHelpers::Translate_ChFlag_TO_ChID((AE_DSP_CHANNEL_PRESENT)tempChannelFlag));
    m_ChannelMappingFlags[ch] = CADSPHelpers::Translate_ChID_TO_ChFlag((AE_DSP_CHANNEL)m_ChannelMappingIdx[ch]);
    if (m_ChannelMappingIdx[ch] == AE_DSP_CH_INVALID)
    {
      KODI->Log(LOG_ERROR, "%s, %i, Tried to create invalid channel mappings!", __FUNCTION__, __LINE__);
      return AE_DSP_ERROR_FAILED;
    }
    lastAudioChannel = m_ChannelMappingIdx[ch] + 1;
  }

  if (!CPostProcessGainMessages::Create(this))
  {
    KODI->Log(LOG_ERROR, "%s, %i, Failed to create message dispachter %s", __FUNCTION__, __LINE__, CPostProcessGainMessages::DispatcherName.c_str());
    return AE_DSP_ERROR_FAILED;
  }
  

  return AE_DSP_ERROR_NO_ERROR;
}


void CPostProcessGain::ModeDestroy()
{
}


// Requiered Processing Methods
unsigned int CPostProcessGain::ModeProcess(float **ArrayIn, float **ArrayOut, unsigned int Samples)
{
  CPostProcessGainMessages::ProcessMessage();

  for (int ch = 0; ch < m_InChannels; ch++)
  { 
    float *out = ArrayOut[m_ChannelMappingIdx[ch]];
    const float *in  = ArrayIn[m_ChannelMappingIdx[ch]];
    for (unsigned int ii = 0; ii < Samples; ii++)
    {
      out[ii] = m_MainGain*in[ii];
    }
  }

  return Samples;
}
