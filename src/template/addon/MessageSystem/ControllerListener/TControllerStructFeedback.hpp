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



// TODO: Logging
//#include "logger.hpp"
#include "Addon/MessageSystem/ControllerListener/TControllerStruct.hpp"


template<typename TStruct, typename TElement, typename TFlag, unsigned int Flag=0, typename TInternalFmt=TElement>
class TControllerStructFeedback : public TControllerStruct<TStruct, TElement, TInternalFmt>
{
public:
  TControllerStructFeedback(TStruct **StructPtr, 
                            TFlag *ParamFlag,
                            std::string Name, RTComSignal_t Signal,
                            TInternalFmt Scale, unsigned int MaxElements,
                            bool IsPtrElement, unsigned int StructOffset = 0, unsigned int ElementGrpSize = 1, unsigned int ElementOffset = 0) :
    TControllerStruct(StructPtr, Name, Signal, Scale, MaxElements, IsPtrElement, StructOffset,  ElementGrpSize, ElementOffset)
  {
    if (!ParamFlag)
    {
      throw std::exception("ParamFlag == NULL");
    }

    m_Flag = Flag;
    m_ParamFlag = ParamFlag;
  }


  ~TControllerStructFeedback()
  {
  }


  virtual bool ControllParameter(CMessage &Message)
  {
    if (!TControllerStruct<TStruct, TElement, TInternalFmt>::ControllParameter(Message))
    {
      return false;
    }

    *m_ParamFlag |= m_Flag;

    return true;
  }


protected:
  unsigned int m_Flag;
  TFlag *m_ParamFlag;
};
