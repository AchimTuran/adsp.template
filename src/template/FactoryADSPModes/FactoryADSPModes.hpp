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



#include <map>

#include "IADSPMode.hpp"
#include "TStatisticsADSPModes.hpp"
#include <kodi/kodi_adsp_types.h>


class CFactoryADSPModes
{
private:
  typedef IADSPMode* (*ADSPModeCreateCallback)();
  typedef int(*ADSPModeStatisticCallback)();
  typedef struct ADSPModeCallbacks_t
  {
    ADSPModeCreateCallback     CreateADSPMode;
    ADSPModeStatisticCallback  GetActiveADSPMode;
    ADSPModeStatisticCallback  GetCreatedADSPMode;
    ADSPModeStatisticCallback  GetDestroyedADSPMode;
  }ADSPModeCallbacks_t;

  typedef struct ADSPModeKey_t
  {
    int  ModeID;
    int  ModeCategory;

    ADSPModeKey_t(int ID, int Category)
    {
      ModeID        = ID;
      ModeCategory  = Category;
    }
  }ADSPModeKey_t;

  class CADSPModeKeyCmp
  {
  public:
    bool operator()(const ADSPModeKey_t &Obj1, const ADSPModeKey_t &Obj2)
    {
      return  Obj1.ModeID < Obj2.ModeID || (Obj1.ModeID == Obj2.ModeID  && Obj1.ModeCategory < Obj2.ModeCategory);
    }
  };

  typedef std::map<ADSPModeKey_t, ADSPModeCallbacks_t, CADSPModeKeyCmp> ADSPModeMap_t;

public:
  template<class TADSPMode, int TID, int TCategory>
  class TRegisterADSPMode : public TStatisticsADSPModes<TADSPMode>
  {
    friend class CFactoryADSPModes;

  public:
    TRegisterADSPMode() : m_HiddenProductID(ModeID) {} // force registration by assinging ModeID to m_HiddenID

    static const int  ModeID;
    static const int  ModeCategory;

    static IADSPMode* Create() { return dynamic_cast<IADSPMode*>(new TADSPMode); }

  private:
    const  int                 m_HiddenID; // force initialization for m_HiddenID
    static ADSPModeCallbacks_t m_Callbacks;
  };

  static AE_DSP_ERROR Create(int ModeID, int ModeCategory, IADSPMode *&InterfacePtr);
  static AE_DSP_ERROR Destroy(IADSPMode *&ADSPMode);
  static int RegisterADSPMode(int ModeID, int ModeCategory, ADSPModeCallbacks_t Callbacks);
  static int GetActiveADSPMode(int ModeID, int ModeCategory);
  static int GetCreatedADSPMode(int ModeID, int ModeCategory);
  static int GetDestroyedADSPMode(int ModeID, int ModeCategory);

private:
  // Force initialization and creation of product map by using a static method and a std::map
  inline static ADSPModeMap_t& GetADSPModeMap()
  {
    static ADSPModeMap_t s_ADSPModes;

    return s_ADSPModes;
  }
};

template<class TADSPMode, int TID, int TCategory>
const int CFactoryADSPModes::TRegisterADSPMode<TADSPMode, TID, TCategory>::ModeID =
CFactoryADSPModes::TRegisterADSPMode(TID, TCategory, CFactoryADSPModes::TRegisterProduct<class TADSPMode, int TID, int TCategory>::m_Callbacks);

template<class TADSPMode, int TID, int TCategory>
const int  CFactoryADSPModes::TRegisterADSPMode<TADSPMode, TID, TCategory>::ModeCategory = TCategory;

template<class TADSPMode, int TID, int TCategory>
CFactoryADSPModes::ADSPModeCallbacks_t
CFactoryADSPModes::TRegisterADSPMode<TADSPMode, TID, TCategory>::m_Callbacks =
{
  CFactoryADSPModes::TRegisterProduct<TADSPMode, TID, TCategory>::Create,
  CFactoryADSPModes::TRegisterProduct<TADSPMode, TID, TCategory>::GetActiveADSPMode,
  CFactoryADSPModes::TRegisterProduct<TADSPMode, TID, TCategory>::GetCreatedADSPMode,
  CFactoryADSPModes::TRegisterProduct<TADSPMode, TID, TCategory>::GetDestroyedADSPMode
};
