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
#include "Addon/MessageSystem/Interfaces/IController.hpp"


typedef std::vector<int> SignalIDsVector_t;

class CMessageReceiver : public IMessageHandler
{
public:
  CMessageReceiver(std::string Name, std::string ConnectionNodeName = "");
  ~CMessageReceiver();
  
  int SetControllers(ControllerVector_t &Controllers);
  void Process();

protected:
  IController   **m_Controllers;
  int           *m_ControllerRemapping;
  int           m_ControllerAmount;

private:
  void DestroyControllers();

  RTComSort     m_SortControllers;
};
