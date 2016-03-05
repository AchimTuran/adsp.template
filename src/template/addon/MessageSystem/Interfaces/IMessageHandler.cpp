#include "IMessageHandler.hpp"
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



using namespace std;


IMessageHandler::IMessageHandler(string Name, eHandlerType_t HandlerType, string ConnectionName/*=""*/) :
  IObject(Name),
  HandlerType(HandlerType)
{
  // TODO: LockObject
  //LockSection(MUTEX_LOCK_CONNECTION);
    m_ConnectionPartners.clear();
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_CONNECTION);
  
  m_ConnectionName = ConnectionName;

  m_SignalMappingTable = NULL;
}


IMessageHandler::~IMessageHandler()
{
  TerminateConnection();

  for (CMessageQueue_t::iterator iter = m_InMessages.begin(); iter != m_InMessages.end(); ++iter)
  {
    if (*iter)
    {
      delete *iter;
    }
  }
  m_InMessages.clear();

  for (CMessageQueue_t::iterator iter = m_FreeMessages.begin(); iter != m_FreeMessages.end(); ++iter)
  {
    if (*iter)
    {
      delete *iter;
    }
  }
  m_FreeMessages.clear();

  for (CMessageQueue_t::iterator iter = m_OutMessages.begin(); iter != m_OutMessages.end(); ++iter)
  {
    if (*iter)
    {
      delete *iter;
    }
  }
  m_OutMessages.clear();


  if (m_SignalMappingTable)
  {
    delete [] m_SignalMappingTable;
    m_SignalMappingTable = NULL;
  }
}


bool IMessageHandler::DestroyConnection(IMessageHandler *ConnectionPartner)
{
  // TODO: LockObject
  //LockSection(MUTEX_LOCK_CONNECTION);
    if (m_ConnectionPartners.size() <= 0)
    {// TODO: no connection available!    
      // TODO: LockObject
      //UnlockSection(MUTEX_LOCK_CONNECTION);
      return false;
    }

    for (deque<IMessageHandler*>::iterator iter = m_ConnectionPartners.begin(); iter != m_ConnectionPartners.end(); ++iter)
    {
      if (*iter == ConnectionPartner)
      {
        m_ConnectionPartners.erase(iter);
        break;
      }
    }
    
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_CONNECTION);
  return true;
}


bool IMessageHandler::TerminateConnection()
{
  // TODO: LockObject
  //LockSection(MUTEX_LOCK_CONNECTION);
    if(m_ConnectionPartners.size() <= 0)
    {// TODO: no connection available!
      // TODO: LockObject
      //UnlockSection(MUTEX_LOCK_CONNECTION);
      return false;
    }

    for (deque<IMessageHandler*>::iterator iter = m_ConnectionPartners.begin(); iter != m_ConnectionPartners.end(); ++iter)
    {
      if (*iter)
      {
        if ((*iter)->DestroyConnection(this))
        {// TODO: log warning!
        }
      }
    }

    m_ConnectionPartners.clear();
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_CONNECTION);
  return true;
}


bool IMessageHandler::CreateConnection(IMessageHandler *ConnectionPartner)
{
  if(!ConnectionPartner)
  {// TODO: Invalid Pointer!
    return false;
  }

  // TODO: LockObject
  //LockSection(MUTEX_LOCK_CONNECTION);
    if(!ConnectionPartner->ValidateConnection(this))
    {// TODO: other partner is already connected!
      // TODO: LockObject
      //UnlockSection(MUTEX_LOCK_CONNECTION);
      return false;
    }

    m_ConnectionPartners.push_back(ConnectionPartner);
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_CONNECTION);
  
  return true;
}


bool IMessageHandler::ValidateConnection(IMessageHandler *ValidationPartner)
{
  if(!ValidationPartner)
  {// TODO: Invalid Pointer!
    return false;
  }

  // TODO: LockObject
  //LockSection(MUTEX_LOCK_CONNECTION);
    m_ConnectionPartners.push_back(ValidationPartner);
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_CONNECTION);
  return true;
}


bool IMessageHandler::ReceiveMessage(CMessage *Message)
{
  if (!Message)
  {
    return false;
  }
  // TODO: LockObject
  //LockSection(MUTEX_LOCK_IN_MESSAGES);
    m_InMessages.push_back(Message);
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_IN_MESSAGES);
  return true;
}


int IMessageHandler::GetFreeMessages(CMessageQueue_t &FreeMessage)
{
  // TODO: LockObject
  //LockSection(MUTEX_LOCK_CONNECTION);
  int messageAmount = m_FreeMessages.size();
  if (messageAmount > 0)
  {
    FreeMessage.swap(m_FreeMessages);
  }
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_CONNECTION);

  return messageAmount;
}


int IMessageHandler::GetOutMessages(CMessageQueue_t &OutMessage)
{
  // TODO: LockObject
  //LockSection(MUTEX_LOCK_CONNECTION);
  int messageAmount = m_OutMessages.size();
  if (messageAmount > 0)
  {
    OutMessage.swap(m_OutMessages);
  }
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_CONNECTION);

  return messageAmount;
}


bool IMessageHandler::TransmitMessage(CMessage *Message, RTComSignal_t Signal)
{
  if (m_ConnectionPartners.size() <= 0 || m_ConnectionPartners.size() > 1)
  {
    return false;
  }

  Message->SetSignal(Signal);
  
  // TODO: LockObject
  //LockSection(MUTEX_LOCK_CONNECTION);
    bool retBool = m_ConnectionPartners.at(0)->ReceiveMessage(Message);
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_CONNECTION);

  return retBool;
}

int IMessageHandler::GetFreePartnerMessages(CMessageQueue_t &FreeMessage)
{
  int messageAmount = 0;
  // TODO: LockObject
  //LockSection(MUTEX_LOCK_CONNECTION);
  if (m_ConnectionPartners.size() > 0)
  {
    for (std::deque<IMessageHandler*>::iterator iter = m_ConnectionPartners.begin(); iter != m_ConnectionPartners.end() && messageAmount <= 0; ++iter)
    {
      messageAmount = (*iter)->GetFreeMessages(FreeMessage);
    }
  }
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_CONNECTION);

  return messageAmount;
}

void IMessageHandler::GetOutPartnerMessages()
{
  // TODO: LockObject
  //LockSection(MUTEX_LOCK_CONNECTION);
    if (m_ConnectionPartners.size() > 0)
    {
      for (std::deque<IMessageHandler*>::iterator iter = m_ConnectionPartners.begin(); iter != m_ConnectionPartners.end(); ++iter)
      {
        CMessageQueue_t outMessages;
        if ((*iter)->GetOutMessages(outMessages) > 0)
        {
          for (CMessageQueue_t::iterator msgIter = outMessages.begin(); msgIter != outMessages.end(); ++msgIter)
          {
            m_InMessages.push_back((*msgIter));
          }
        }
      }
    }
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_CONNECTION);
}


string IMessageHandler::GetConnectionName()
{
  return m_ConnectionName;
}
