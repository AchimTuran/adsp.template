#pragma once
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



#include "AudioDSP/FactoryADSPModes/FactoryADSPModes.hpp"
#include "AudioDSP/Helpers/TADSPModeSettings.hpp"
#include "PreProcessCpyModeSettings.hpp"

#include "ADSPModeInfos.h"

class CPreProcessModeName
{
public:
  static const std::string ModeName;
};

const std::string CPreProcessModeName::ModeName = CADSPModeInfos::Strs[CADSPModeInfos::ADSP_MODE_ID_PREPROCESS_CPY];


class CPreProcessingCpy : REGISTER_ADSP_MODE_CLASS(CPreProcessingCpy, CPreProcessModeName, AE_DSP_MODE_TYPE_PRE_PROCESS)
{
public:
  CPreProcessingCpy();
  ~CPreProcessingCpy();

  virtual AE_DSP_ERROR Create(const AE_DSP_SETTINGS *settings, const AE_DSP_STREAM_PROPERTIES *pProperties);
  virtual AE_DSP_ERROR Destroy();

  // Requiered Processing Methods
  virtual unsigned int Process(float **Array_in, float **Array_out, unsigned int Samples);
};
