#pragma once
/*
 *      Copyright (C) 2005-2016 Team Kodi
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3, or (at your option)
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



#include "template/Addon/MVC/Interfaces/Controller/IController.hpp"

#include "GainMode/GainModeControllerMessages.hpp"

class CPostProcessGainModeControllerMessages;


class CGainModeController : public IController,
                            public CGainModeControllerMessages
{
  friend class CGainModeControllerMessages;

public:
  CGainModeController();
  ~CGainModeController();

  virtual int Create();
  virtual void Destroy();

private:
  int SetMainGain(Message &Msg);

private:
  float m_MainGain;
};