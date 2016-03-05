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

#include "MessageSystemReceiver.hpp"

using namespace std;


CMessageReceiver::CMessageReceiver(string Name, string ConnectionNodeName/* = ""*/) :
  IMessageHandler(Name, MESSAGE_RECEIVER, ConnectionNodeName)
{
  m_Controllers = NULL;
  m_ControllerRemapping = NULL;
  m_ControllerAmount = 0;
}


CMessageReceiver::~CMessageReceiver()
{
  if (m_Controllers)
  {
    for (int ii = 0; ii < m_ControllerAmount; ii++)
    {
      if (m_Controllers[ii])
      {
        delete m_Controllers[ii];
        m_Controllers[ii] = NULL;
      }
    }

    delete[] m_Controllers;
    m_Controllers = NULL;
  }

  if (m_ControllerRemapping)
  {
    delete[] m_ControllerRemapping;
    m_ControllerRemapping = NULL;
  }

  m_ControllerAmount = 0;
}

int CMessageReceiver::SetControllers(ControllerVector_t &Controllers)
{
  if (Controllers.size() <= 0)
  {
    return 0;
  }

  if (m_ControllerAmount > 0)
  {// delete old controllers and disconnect this receiver
    TerminateConnection();

    DestroyControllers();
  }

  m_ControllerAmount = Controllers.size();

  if (m_Controllers)
  {
    delete [] m_Controllers;
    m_Controllers = NULL;
  }
  
  sort(Controllers.begin(), Controllers.end(), m_SortControllers);

  int signalIDDistance = 1;
  for (unsigned int ii = 1; ii < Controllers.size() && signalIDDistance == 1; ii++)
  {
    signalIDDistance = Controllers[ii]->Signal - Controllers[ii - 1]->Signal;
    if (signalIDDistance <= 0)
    {//TODO: error! SignalID is already available!
      return -1;
    }
  }

  if (Controllers.size() == 1 || Controllers[0]->Signal > 0)
  {
    signalIDDistance = Controllers[0]->Signal;
  }

  if (signalIDDistance != 1)
  {
    m_SignalMappingTable = new unsigned int[Controllers.size()];

    for (unsigned int ii = 0; ii < Controllers.size(); ii++)
    {
      m_SignalMappingTable[ii] = Controllers[ii]->Signal;
    }
  }

  //LOG_DEBUG_NAME(this->Name) << "receiver has controller:" << endl;

  m_Controllers = new IController*[m_ControllerAmount];
  for (unsigned int ii = 0; ii < Controllers.size(); ii++)
  {
    //LOG_DEBUG << "  [" << ii << "] \"" << Controllers[ii]->Name << "\"" << endl;
    m_Controllers[ii] = Controllers[ii];
  }
  //LOG_DEBUG << endl;

  return m_ControllerAmount;
}


// TODO: find a better solution for assigning paramters
void CMessageReceiver::Process()
{
  if (m_InMessages.size() > 0)
  {
    CMessageQueue_t messages;
    // TODO: LockObject
    //LockSection(MUTEX_LOCK_IN_MESSAGES);
      messages.swap(m_InMessages);
    // TODO: LockObject
    //UnlockSection(MUTEX_LOCK_IN_MESSAGES);

    for (CMessageQueue_t::iterator iter = messages.begin(); iter != messages.end(); ++iter)
    {
      RTComSignal_t signal = (*iter)->GetSignal();

      if (m_SignalMappingTable)
      {
        int originalEventID = signal;
        for (int ii = 0; ii < m_ControllerAmount; ii++)
        {
          if (originalEventID == m_SignalMappingTable[ii])
          {
            signal = ii;
            break;
          }
          else
          {
            signal = m_ControllerAmount;
          }
        }
      }

      if (0 <= signal && signal < m_ControllerAmount)
      {
        if (!m_Controllers[signal]->ControllParameter(*(*iter)))
        {
          // TODO: report error! Control parameter failed!
        }
      }
      else
      {
        // TODO: report error! Invalid signal ID!
      }
    }

    // TODO: LockObject
    //LockSection(MUTEX_LOCK_IN_MESSAGES);
      while (messages.size() > 0)
      {
        m_FreeMessages.push_back(messages.front());
        messages.pop_front();
      }
    // TODO: LockObject
    //UnlockSection(MUTEX_LOCK_IN_MESSAGES);
  }
}


void CMessageReceiver::DestroyControllers()
{
  if (m_Controllers)
  {
    for (int ii = 0; ii < m_ControllerAmount; ii++)
    {
      if (m_Controllers[ii])
      {
        delete m_Controllers[ii];
        m_Controllers[ii] = NULL;
      }
    }

    delete[] m_Controllers;
    m_Controllers = NULL;
  }

  if (m_ControllerRemapping)
  {
    delete[] m_ControllerRemapping;
    m_ControllerRemapping = NULL;
  }

  m_ControllerAmount = 0;
}
