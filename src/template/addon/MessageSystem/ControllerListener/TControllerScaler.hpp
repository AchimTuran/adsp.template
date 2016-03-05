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
#include "Addon/MessageSystem/ControllerListener/TControllerMemcpy.hpp"


template<typename T>
class TControllerScaler : public TControllerMemcpy<T>
{
public:
  TControllerScaler(T *ParamPtr, T Scale, std::string Name, RTComSignal_t Signal) :
    TControllerMemcpy<T>(ParamPtr, Name, Signal)
  {
    m_Scale = Scale;
  }


  ~TControllerScaler()
  {
  }


  virtual bool ControllParameter(CMessage &Message)
  {
    if (!TControllerMemcpy<T>::ControllParameter(Message))
    {
      return false;
    }

    *m_ParamPtr *= m_Scale;

    // TODO: Logging
    //LOG_DEBUG_NAME(Name) << "controller scaled parameter to: \"" << *m_ParamPtr << "\"" << std::endl;

    return true;
  }


protected:
  T m_Scale;
};
