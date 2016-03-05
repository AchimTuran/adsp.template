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
#include "Addon/MessageSystem/Interfaces/IListener.hpp"


template<class T>
class TListener : public IListener
{
public:
  TListener(T *ParamPtr, std::string Name, RTComSignal_t SignalID) : IListener(Name, SignalID)
  {
    if(!ParamPtr)
    {
      throw std::exception("ParamPtr == NULL!");
    }

    m_ParamPtr = ParamPtr;
    memset(&m_LastParamVal, 0, sizeof(T));
  }


  ~TListener()
  {
  }


  virtual bool HasParameterChanged()
  {
    if(*m_ParamPtr != m_LastParamVal)
    {
      // TODO: Logging
      //LOG_DEBUG_NAME(Name) << "listener observed change: \"" << m_LastParamVal << "\" --> \"" << *m_ParamPtr << "\"" << endl;
      memcpy(&m_LastParamVal, m_ParamPtr, sizeof(T));
      return true;
    }

    return false;
  }


  virtual bool PrepareParameter(CMessage &Message)
  {
    // TODO: Logging
    //LOG_DEBUG_NAME(Name) << "listener observed change: \"" << m_LastParamVal << "\" --> \"" << *m_ParamPtr << "\"" << endl;
    memcpy(&m_LastParamVal, m_ParamPtr, sizeof(T));
    return Message.StoreData(m_ParamPtr, sizeof(T));
  }


  virtual size_t GetParamSize()
  {
    return sizeof(T);
  }

protected:
  T *m_ParamPtr;
  T m_LastParamVal;
};
