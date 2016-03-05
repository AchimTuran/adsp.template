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
#include <deque>

#include "Addon/MessageSystem/Interfaces/IObject.hpp"
#include "Addon/MessageSystem/Communication/Message.hpp"
//#include "RTCom/Messages/ThreadSafeMessages.hpp"


class IMessageHandler : public IObject//, protected CThreadSafeMessages
{
public:
  typedef enum
  {
    MESSAGE_INVALID_TYPE = -1,

    MESSAGE_RECEIVER,
    MESSAGE_SENDER,

    MESSAGE_MAX_TYPE
  }eHandlerType_t;

  IMessageHandler(std::string Name, eHandlerType_t HandlerType, std::string ConnectionNodeName = "");
  virtual ~IMessageHandler();

  // destoy an active connection
  virtual bool DestroyConnection(IMessageHandler *ConnectionPartner);

  // terminate a connection
  virtual bool TerminateConnection();

  // creates a connection between partners
  virtual bool CreateConnection(IMessageHandler *ConnectionPartner);

  // validates a connection and sets the partner
  virtual bool ValidateConnection(IMessageHandler *ValidationPartner);

  // receive a message and store it to input message box
  virtual bool ReceiveMessage(CMessage *Message);

  // get available free messages
  virtual int  GetFreeMessages(CMessageQueue_t &FreeMessage);

  // get available out messages
  virtual int  GetOutMessages(CMessageQueue_t &OutMessage);

  // get all saved messages from connection partners
  virtual void GetOutPartnerMessages();

  std::string GetConnectionName();

  const eHandlerType_t HandlerType;

protected:
  virtual bool TransmitMessage(CMessage *Message, RTComSignal_t Signal);
  virtual int  GetFreePartnerMessages(CMessageQueue_t &FreeMessage);

  CMessageQueue_t     m_InMessages;
  CMessageQueue_t     m_FreeMessages;
  CMessageQueue_t     m_OutMessages;

  unsigned int        *m_SignalMappingTable;

private:
  
  std::deque<IMessageHandler*>  m_ConnectionPartners;
  std::string                   m_ConnectionName;  
};
