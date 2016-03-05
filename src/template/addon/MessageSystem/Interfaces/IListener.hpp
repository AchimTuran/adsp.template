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



#include <vector>

#include "Addon/MessageSystem/Interfaces/IObject.hpp"
#include "Addon/MessageSystem/Communication/Message.hpp"

class IListener;

// typedef for parameter listener registration
typedef std::vector <IListener*> ListenerVector_t;

class IListener : public IObject
{
public:
  IListener(std::string Name, RTComSignal_t Signal) : IObject(Name, Signal) {}
  virtual ~IListener() {}

  virtual bool HasParameterChanged() = 0;
  virtual bool PrepareParameter(CMessage &Message) = 0;
  virtual size_t GetParamSize() = 0;
};
