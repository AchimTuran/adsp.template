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
#include <string>

using namespace std;


// static member variables
CFactoryADSPModes::ADSPModeNameMap_t CFactoryADSPModes::m_ModeNameMappingTable;

AE_DSP_ERROR CFactoryADSPModes::Create(int ModeID, AE_DSP_MODE_TYPE ModeType, IADSPMode *&InterfacePtr)
{
  ADSPModeKey_t ADSPModeKey(ModeID, ModeType);
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


int CFactoryADSPModes::RegisterADSPMode(const std::string ModeName, AE_DSP_MODE_TYPE ModeType, ADSPModeCallbacks_t Callbacks)
{
  static int modeID=0;
  ADSPModeKey_t ADSPModeKey(modeID, ModeType);
  ADSPModeMap_t::iterator iter = GetADSPModeMap().find(ADSPModeKey);
  if (iter == GetADSPModeMap().end())
  {// only register not yet known products
    GetADSPModeMap()[ADSPModeKey] = Callbacks;
  }

  m_ModeNameMappingTable[ModeName] = ADSPModeKey;

  return modeID++;
}


int CFactoryADSPModes::GetActiveADSPMode(std::string &ModeName)
{
  ADSPModeNameMap_t::iterator iterModeKey = m_ModeNameMappingTable.find(ModeName);
  if (iterModeKey == m_ModeNameMappingTable.end())
  {
    return -1;
  }

  ADSPModeMap_t::iterator iterCB = GetADSPModeMap().find((*iterModeKey).second);
  if (iterCB == GetADSPModeMap().end())
  {
    return -1;
  }

  return (*iterCB).second.GetActiveADSPMode();
}


int CFactoryADSPModes::GetCreatedADSPMode(std::string &ModeName)
{
  ADSPModeNameMap_t::iterator iterModeKey = m_ModeNameMappingTable.find(ModeName);
  if (iterModeKey == m_ModeNameMappingTable.end())
  {
    return -1;
  }

  ADSPModeMap_t::iterator iterCB = GetADSPModeMap().find((*iterModeKey).second);
  if (iterCB == GetADSPModeMap().end())
  {
    return -1;
  }

  return (*iterCB).second.GetCreatedADSPMode();
}

int CFactoryADSPModes::GetDestroyedADSPMode(std::string &ModeName)
{
  ADSPModeNameMap_t::iterator iterModeKey = m_ModeNameMappingTable.find(ModeName);
  if (iterModeKey == m_ModeNameMappingTable.end())
  {
    return -1;
  }

  ADSPModeMap_t::iterator iterCB = GetADSPModeMap().find((*iterModeKey).second);
  if (iterCB == GetADSPModeMap().end())
  {
    return -1;
  }

  return (*iterCB).second.GetDestroyedADSPMode();
}
