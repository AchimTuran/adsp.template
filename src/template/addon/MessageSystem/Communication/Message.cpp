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



#include <iostream>

#include "Message.hpp"

using namespace std;


CMessage::CMessage(string SrcName, string DstName) :
  IObject("RTCMessage")
{
  m_Data = NULL;
  m_SrcName = SrcName;
  m_SrcName = DstName;
  m_MessageSize = 0;
}

CMessage::~CMessage()
{
  if(m_Data)
  {
    delete [] m_Data;
  }
}


RTComSignal_t CMessage::GetSignal()
{
  return m_Signal;
}


void CMessage::SetSrcName(std::string SrcName)
{
  m_SrcName = SrcName;
}

string CMessage::GetSrcName()
{
  return m_SrcName;
}


void CMessage::SetDstName(std::string DstName)
{
  m_DstName = DstName;
}


string CMessage::GetDstName()
{
  return m_DstName;
}


bool CMessage::StoreData(void *DataPtr, size_t Size)
{
  if(!DataPtr)
  {
    //LOG_ERROR_FUNCTION << "!DataPtr" << endl;
    return false;
  }

  if(Size > m_MessageSize)
  {
    //LOG_DEBUG_FUNCTION << "reallocating message memory" << endl;
    if(m_Data)
    {
      delete[] m_Data;
      m_Data = NULL;
    }

    m_Data = new unsigned char[Size];
    m_CurrentMessageSize = Size;
    m_MessageSize = Size;
  }
  else
  {
    m_CurrentMessageSize = Size;
  }

  memcpy(m_Data, DataPtr, m_CurrentMessageSize);
  return true;
}


bool CMessage::GetData(void *DataPtr, size_t Size/* = 0*/)
{
  if (!DataPtr || Size > m_MessageSize)
  {
    //LOG_ERROR_FUNCTION << "!DataPtr" << endl;
    return false;
  }

  if (Size <= 0)
  {
    memcpy(DataPtr, m_Data, m_MessageSize);
  }
  else
  {
    memcpy(DataPtr, m_Data, Size);
  }
    
  return true;
}


bool CMessage::GetDataPtr(void *&DataPtr)
{
  if(!m_Data)
  {
    //LOG_ERROR_FUNCTION << "!DataPtr" << endl;
    DataPtr = NULL;
    return false;
  }

  DataPtr = (void*)m_Data;

  return true;
}


size_t CMessage::GetMessageSize()
{
  return m_MessageSize;
}


void CMessage::SetSignal(RTComSignal_t Signal)
{
  m_Signal = Signal;
}
