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



#include <algorithm>

#include "MessageSystemSender.hpp"

using namespace std;


CMessageSender::CMessageSender(std::string Name, string ConnectionNodeName/* = ""*/) :
  IMessageHandler(Name, MESSAGE_SENDER, ConnectionNodeName)
{
  m_Listeners         = NULL; 
  m_ListenerAmount    = 0;
  m_ListenerRemapping = NULL;
}


CMessageSender::~CMessageSender()
{
  DestroyListeners();
}


int CMessageSender::SetListeners(ListenerVector_t &Listeners)
{
  if(Listeners.size() <= 0)
  {
    return 0;
  }

  if (m_ListenerAmount > 0)
  {
    TerminateConnection();

    DestroyListeners();
  }

  m_ListenerAmount = Listeners.size();

  if(m_Listeners)
  {
    delete [] m_Listeners;
    m_Listeners = NULL;
  }

  sort(Listeners.begin(), Listeners.end(), m_SortListener);

  int signalIDDistance = 1;
  for (unsigned int ii = 1; ii < Listeners.size() && signalIDDistance == 1; ii++)
  {
    signalIDDistance = Listeners[ii]->Signal - Listeners[ii -1]->Signal;
    if (signalIDDistance <= 0)
    {//TODO: error! SignalID is already available!
      return -1;
    }
  }

  if (Listeners.size() == 1 || Listeners[0]->Signal > 0)
  {
    signalIDDistance = Listeners[0]->Signal;
  }

  if (signalIDDistance != 1)
  {
    m_SignalMappingTable = new unsigned int[Listeners.size()];

    for (unsigned int ii = 0; ii < Listeners.size(); ii++)
    {
      m_SignalMappingTable[ii] = Listeners[ii]->Signal;
    }
  }

  //LOG_DEBUG_NAME(this->Name) << " sender has listener:" << endl;

  m_Listeners = new IListener*[m_ListenerAmount];
  for (unsigned int ii = 0; ii < Listeners.size(); ii++)
  {
    //LOG_DEBUG << "  [" << ii << "] \"" << Listeners[ii]->Name << "\"" << endl;
    m_Listeners[ii] = Listeners[ii];
  }
  //LOG_DEBUG << endl;

  return m_ListenerAmount;
}


int CMessageSender::PostEvent(int EventID)
{
  if (m_ListenerAmount <= 0)
  {
    return -1;
  }

  if (m_SignalMappingTable)
  {
    int originalEventID = EventID;
    for (int ii = 0; ii < m_ListenerAmount; ii++)
    {
      if (originalEventID == m_SignalMappingTable[ii])
      {
        EventID = ii;
        break;
      }
      else
      {
        EventID = m_ListenerAmount;
      }
    }
  }

  if (EventID < 0 || EventID >= m_ListenerAmount)
  {
    return -1;
  }
   
  CMessage *message = NULL;    
  // TODO: LockObject
  //LockSection(MUTEX_LOCK_FREE_MESSAGES);
    int availableMessages = m_FreeMessages.size();

    if (availableMessages <= 0)
    {// try to get free messages vom connection partner
      availableMessages = GetFreePartnerMessages(m_FreeMessages);
    }
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_FREE_MESSAGES);

  if (availableMessages > 0)
  {
    // TODO: LockObject
    //LockSection(MUTEX_LOCK_FREE_MESSAGES);
      message = m_FreeMessages.front();
      m_FreeMessages.pop_front();
    // TODO: LockObject
    //UnlockSection(MUTEX_LOCK_FREE_MESSAGES);
  }
  else
  {
    message = new CMessage(Name, m_Listeners[EventID]->Name);
  }

  // TODO: LockObject
  //LockSection(MUTEX_LOCK_VALUE);
    m_Listeners[EventID]->PrepareParameter(*message); // TODO: check return value!
    message->SetSignal(EventID);
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_VALUE);

  if (!this->TransmitMessage(message, m_Listeners[EventID]->Signal))
  {// TODO: couldn't send message!
    // TODO: LockObject
    //LockSection(MUTEX_LOCK_OUT_MESSAGES);
      m_OutMessages.push_back(message);
    // TODO: LockObject
    //UnlockSection(MUTEX_LOCK_OUT_MESSAGES);

    return -2;
  }

  return 0;
}


void CMessageSender::DestroyListeners()
{
  if (m_Listeners)
  {
    for (int ii = 0; ii < m_ListenerAmount; ii++)
    {
      if (m_Listeners[ii])
      {
        delete m_Listeners[ii];
        m_Listeners[ii] = NULL;
      }
    }

    delete[] m_Listeners;
    m_Listeners = NULL;
  }

  if (m_ListenerRemapping)
  {
    delete[] m_ListenerRemapping;
    m_ListenerRemapping = NULL;
  }

  m_ListenerAmount = 0;
}
