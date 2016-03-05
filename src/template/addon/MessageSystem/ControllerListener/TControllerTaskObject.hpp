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
#include "Addon/MessageSystem/Interfaces/IController.hpp"


template<class TTaskObject, class TParam>
class TControllerTaskObject : public IController
{
public:
  TControllerTaskObject(TParam *ParamPtr, std::string Name, RTComSignal_t Signal) : IController(Name, Signal)
  {
    if (!ParamPtr)
    {
      throw std::exception("TaskObject == NULL");
    }

    m_ParamPtr    = ParamPtr;
  }


  ~TControllerTaskObject()
  {
  }


  virtual bool ControllParameter(CMessage &Message)
  {
    if (Message.GetSignal() != this->Signal)
    {
      // TODO: Logging
      //LOG_ERROR_FUNCTION << "Message.GetSignalID() != this->GetSignalID()" << std::endl;
      return false;
    }

    // TODO: Logging
    //LOG_DEBUG_NAME(Name) << "controller processed task" << std::endl;

    return m_TaskObject.Process(m_ParamPtr, Message);
  }


protected:
  TTaskObject m_TaskObject;
  TParam      *m_ParamPtr;
};
