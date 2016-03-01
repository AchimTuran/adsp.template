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


#include "FactoryADSPModes.hpp"

AE_DSP_ERROR CFactoryADSPModes::Create(int ModeID, int ModeCategory, IADSPMode *&InterfacePtr)
{
  ADSPModeKey_t ADSPModeKey(ModeID, ModeCategory);
  ADSPModeMap_t::iterator iter = GetADSPModeMap().find(ADSPModeKey);
  if (iter == GetADSPModeMap().end())
  {
    InterfacePtr = NULL;
    return AE_DSP_ERROR_INVALID_PARAMETERS;
  }

  InterfacePtr = (*iter).second.CreateADSPMode();
  return AE_DSP_ERROR_NO_ERROR;
}


AE_DSP_ERROR CFactoryADSPModes::Destroy(IADSPMode *&ADSPMode)
{
  if (ADSPMode)
  {
    delete ADSPMode;
    ADSPMode = NULL;
  }

  return AE_DSP_ERROR_NO_ERROR;
}


int CFactoryADSPModes::RegisterADSPMode(int ModeID, int ModeCategory, ADSPModeCallbacks_t Callbacks)
{
  ADSPModeKey_t ADSPModeKey(ModeID, ModeCategory);
  ADSPModeMap_t::iterator iter = GetADSPModeMap().find(ADSPModeKey);
  if (iter == GetADSPModeMap().end())
  {// only register not yet known products
    GetADSPModeMap()[ADSPModeKey] = Callbacks;
  }

  return ModeID;
}


int CFactoryADSPModes::GetActiveADSPMode(int ModeID, int ModeCategory)
{
  ADSPModeKey_t ADSPModeKey(ModeID, ModeCategory);
  ADSPModeMap_t::iterator iter = GetADSPModeMap().find(ADSPModeKey);
  if (iter == GetADSPModeMap().end())
  {
    return -1;
  }

  return (*iter).second.GetActiveADSPMode();
}


int CFactoryADSPModes::GetCreatedADSPMode(int ModeID, int ModeCategory)
{
  ADSPModeKey_t ADSPModeKey(ModeID, ModeCategory);
  ADSPModeMap_t::iterator iter = GetADSPModeMap().find(ADSPModeKey);
  if (iter == GetADSPModeMap().end())
  {
    return -1;
  }

  return (*iter).second.GetCreatedADSPMode();
}

int CFactoryADSPModes::GetDestroyedADSPMode(int ModeID, int ModeCategory)
{
  ADSPModeKey_t ADSPModeKey(ModeID, ModeCategory);
  ADSPModeMap_t::iterator iter = GetADSPModeMap().find(ADSPModeKey);
  if (iter == GetADSPModeMap().end())
  {
    return -1;
  }

  return (*iter).second.GetDestroyedADSPMode();
}
