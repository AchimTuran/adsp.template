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

// Category:
// AE_DSP_MODE_TYPE_INPUT_RESAMPLE  = 0,        /*!< @brief for input re sample */
// AE_DSP_MODE_TYPE_PRE_PROCESS     = 1,        /*!< @brief for preprocessing */
// AE_DSP_MODE_TYPE_MASTER_PROCESS  = 2,        /*!< @brief for master processing */
// AE_DSP_MODE_TYPE_POST_PROCESS    = 3,        /*!< @brief for post processing */
// AE_DSP_MODE_TYPE_OUTPUT_RESAMPLE = 4,        /*!< @brief for output re sample */
#define REGISTER_ADSP_MODE_CLASS(ADSPMode, ID, Type)  public IADSPMode,                                                     \
                                                      public CFactoryADSPModes::TRegisterADSPMode<ADSPMode, ID, Type>


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
    int               ModeID;
    AE_DSP_MODE_TYPE  ModeType;

    ADSPModeKey_t()
    {
      ModeID = -1;
      ModeType = AE_DSP_MODE_TYPE_UNDEFINED;
    }

    ADSPModeKey_t(int ID, AE_DSP_MODE_TYPE Type)
    {
      ModeID        = ID;
      ModeType      = Type;
    }
  }ADSPModeKey_t;

  class CADSPModeKeyCmp
  {
  public:
    bool operator()(const ADSPModeKey_t &Obj1, const ADSPModeKey_t &Obj2)
    {
      return  Obj1.ModeID < Obj2.ModeID || (Obj1.ModeID == Obj2.ModeID  && Obj1.ModeType < Obj2.ModeType);
    }
  };

  typedef std::map<ADSPModeKey_t, ADSPModeCallbacks_t, CADSPModeKeyCmp> ADSPModeMap_t;
  typedef std::map<std::string, ADSPModeKey_t> ADSPModeNameMap_t;

public:
  template<class TADSPMode, const char* TModeName, AE_DSP_MODE_TYPE TType>
  class TRegisterADSPMode : public TStatisticsADSPModes<TADSPMode>
  {
    friend class CFactoryADSPModes;

  public:
    TRegisterADSPMode() : m_HiddenProductID(ModeID) {} // force registration by assinging ModeID to m_HiddenID

    static const int  ModeID;
    static const AE_DSP_MODE_TYPE ModeType;
    static const char* ModeName;

    static IADSPMode* Create() { return dynamic_cast<IADSPMode*>(new TADSPMode); }

  private:
    const  int                 m_HiddenID; // force initialization for m_HiddenID
    static ADSPModeCallbacks_t m_Callbacks;
  };

  static AE_DSP_ERROR Create(int ModeID, AE_DSP_MODE_TYPE ModeType, IADSPMode *&InterfacePtr);
  static AE_DSP_ERROR Destroy(IADSPMode *&ADSPMode);
  static int RegisterADSPMode(const char* ModeName, AE_DSP_MODE_TYPE ModeType, ADSPModeCallbacks_t Callbacks);
  static int GetActiveADSPMode(std::string &ModeName);
  static int GetCreatedADSPMode(std::string &ModeName);
  static int GetDestroyedADSPMode(std::string &ModeName);

private:
  // Force initialization and creation of product map by using a static method and a std::map
  inline static ADSPModeMap_t& GetADSPModeMap()
  {
    static ADSPModeMap_t s_ADSPModes;

    return s_ADSPModes;
  }

  static ADSPModeNameMap_t m_ModeNameMappingTable;
};


template<class TADSPMode, const char* TModeName, AE_DSP_MODE_TYPE TType>
const int CFactoryADSPModes::TRegisterADSPMode<TADSPMode, TModeName, TType>::ModeID =
CFactoryADSPModes::TRegisterADSPMode(TID, TType, CFactoryADSPModes::TRegisterProduct<TADSPMode, TModeName, TType>::m_Callbacks);

template<class TADSPMode, const char* TModeName, AE_DSP_MODE_TYPE TType>
const int  CFactoryADSPModes::TRegisterADSPMode<TADSPMode, TModeName, TType>::ModeType = TType;

template<class TADSPMode, const char* TModeName, AE_DSP_MODE_TYPE TType>
const int  CFactoryADSPModes::TRegisterADSPMode<TADSPMode, TModeName, TType>::ModeName = TModeName;

template<class TADSPMode, const char* TModeName, AE_DSP_MODE_TYPE TType>
CFactoryADSPModes::ADSPModeCallbacks_t
CFactoryADSPModes::TRegisterADSPMode<TADSPMode, TModeName, TType>::m_Callbacks =
{
  CFactoryADSPModes::TRegisterProduct<TADSPMode, TModeName, TType>::Create,
  CFactoryADSPModes::TRegisterProduct<TADSPMode, TModeName, TType>::GetActiveADSPMode,
  CFactoryADSPModes::TRegisterProduct<TADSPMode, TModeName, TType>::GetCreatedADSPMode,
  CFactoryADSPModes::TRegisterProduct<TADSPMode, TModeName, TType>::GetDestroyedADSPMode
};
