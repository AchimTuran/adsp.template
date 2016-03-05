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



#include "Addon/MessageSystem/Interfaces/IMessageHandler.hpp"
#include "Addon/MessageSystem/Interfaces/IListener.hpp"


class CMessageSender : public IMessageHandler
{
public:
  CMessageSender(std::string Name, std::string ConnectionNodeName = "");
  ~CMessageSender();

  int SetListeners(ListenerVector_t &Listeners);
  int PostEvent(int EventID);

protected:
  IListener **m_Listeners;
  int       *m_ListenerRemapping;
  int       m_ListenerAmount;

private:
  void DestroyListeners();

  RTComSort  m_SortListener;
};
