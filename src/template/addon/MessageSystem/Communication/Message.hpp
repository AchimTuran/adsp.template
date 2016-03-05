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



#include <deque>

#include "Addon/MessageSystem/Interfaces/IObject.hpp"


class CMessage;

typedef std::deque<CMessage*> CMessageQueue_t;

class CMessage : private IObject
{
public:
  CMessage(std::string SrcName, std::string DstName);
  ~CMessage();

  void SetSignal(RTComSignal_t Signal);
  RTComSignal_t GetSignal();
  void SetSrcName(std::string SrcName);
  std::string GetSrcName();
  void SetDstName(std::string DstName);
  std::string GetDstName();

  bool GetData(void *DataPtr, size_t Size = 0);
  bool GetDataPtr(void *&DataPtr);
  size_t GetMessageSize();

  bool StoreData(void *DataPtr, size_t Size);

private:
  std::string   m_SrcName;
  std::string   m_DstName;
  RTComSignal_t m_Signal;

  size_t        m_MessageSize;
  size_t        m_CurrentMessageSize;
  unsigned char *m_Data;
};
