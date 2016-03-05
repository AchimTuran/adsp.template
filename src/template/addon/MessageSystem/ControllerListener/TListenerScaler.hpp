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
#include "Addon/MessageSystem/ControllerListener/TListener.hpp"


template<typename T>
class TListenerScaler : public TListener<T>
{
public:
  TListenerScaler(T *ParamPtr, T Scale, std::string Name, RTComSignal_t Signal) :
    TListener<T>(ParamPtr, Name, Signal)
  {
    m_Scale = Scale;
  }


  ~TListenerScaler()
  {
  }


  virtual bool PrepareParameter(CMessage &Message)
  {   
    // TODO: Logging
    //LOG_DEBUG_NAME(Name) << "listener observed change: \"" << m_LastParamVal << "\" --> \"" << *m_ParamPtr << "\"" << endl;

    m_Param = *m_ParamPtr;
    m_Param *= m_Scale;

    // TODO: Logging
    //LOG_DEBUG_NAME(Name) << "listener scaled parameter to: \"" << m_Param << "\"" << std::endl;

    memcpy(&m_LastParamVal, m_ParamPtr, sizeof(T));
    return Message.StoreData(&m_Param, sizeof(T));
  }


protected:
  T m_Scale;
  T m_Param;
};
