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



#include "PreProcessCpyModeSettings.hpp"

#include "ADSPModeInfos.h"


CPreProcessCpyModeSettings::CPreProcessCpyModeSettings()
{
  this->iUniqueDBModeId = -1;
  this->iModeType       = AE_DSP_MODE_TYPE_INPUT_RESAMPLE;
  strcpy(this->strModeName, CADSPModeInfos::Strs[CADSPModeInfos::ADSP_MODE_ID_PREPROCESS_CPY]);

  this->iModeNumber           = CADSPModeInfos::ADSP_MODE_ID_PREPROCESS_CPY;
  this->iModeSupportTypeFlags = AE_DSP_PRSNT_ASTREAM_BASIC | AE_DSP_PRSNT_ASTREAM_MUSIC | AE_DSP_PRSNT_ASTREAM_MOVIE | AE_DSP_PRSNT_ASTREAM_GAME | AE_DSP_PRSNT_ASTREAM_APP | AE_DSP_PRSNT_ASTREAM_MESSAGE | AE_DSP_PRSNT_ASTREAM_PHONE;
  this->bHasSettingsDialog    = true;
  this->bIsDisabled           = true;

  this->iModeName         = 30004;
  this->iModeSetupName    = 30005;
  this->iModeDescription  = 30006;
  this->iModeHelp         = 30007;

  strcpy(this->strOwnModeImage,       "img1.jpg");
  strcpy(this->strOverrideModeImage,  "img1.jpg");
}


CPreProcessCpyModeSettings::~CPreProcessCpyModeSettings()
{
}
