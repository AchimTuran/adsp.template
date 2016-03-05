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



#include "ConnectionPort.hpp"

using namespace std;


CConnectionNode::CConnectionNode(std::string Name) :
  IConnectionNode(Name)
{
}


CConnectionNode::~CConnectionNode()
{
}


int CConnectionNode::Register(IMessageHandler *Member)
{
  if (!Member)
  {
    return false;
  }

  // TODO: LockObject
  //LockSection(MUTEX_LOCK_CONNECTION);
    Connections_t::iterator iter = m_Connections.find(Member->GetConnectionName());
    if (iter == m_Connections.end())
    {// Add a new connection member to this node
      m_Connections[Member->GetConnectionName()].push_back(Member);
    }
    else
    {
      if (iter->second.size() <= 0)
      {
        // TODO: return error!
        // TODO: LockObject
        //UnlockSection(MUTEX_LOCK_CONNECTION);
        return -1;
      }

      IMessageHandler::eHandlerType_t connectionPartnerType = IMessageHandler::MESSAGE_INVALID_TYPE;
      if (Member->HandlerType == IMessageHandler::MESSAGE_RECEIVER)
      {
        connectionPartnerType = IMessageHandler::MESSAGE_SENDER;
      }
      else if (Member->HandlerType == IMessageHandler::MESSAGE_SENDER)
      {
        connectionPartnerType = IMessageHandler::MESSAGE_RECEIVER;
      }
      else
      {// TODO: error message invalid handler type!
        // TODO: LockObject
        //UnlockSection(MUTEX_LOCK_CONNECTION);
        return -1;
      }

      for (std::deque<IMessageHandler*>::iterator partnerIter = iter->second.begin(); partnerIter != iter->second.end(); ++partnerIter)
      {
        if ((*partnerIter)->HandlerType == connectionPartnerType)
        {
          if (!(Member->CreateConnection(*partnerIter)))
          {// TODO: error create connection failed
            // TODO: LockObject
            //UnlockSection(MUTEX_LOCK_CONNECTION);
            return -1;
          }
        }
      }

      if (Member->HandlerType == IMessageHandler::MESSAGE_RECEIVER)
      { // check all senders out messages for this receiver
        Member->GetOutPartnerMessages();
      }

      iter->second.push_back(Member);
    }
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_CONNECTION);

  return 0;
}


int CConnectionNode::Deregister(IMessageHandler *Member)
{
  if (!Member)
  {
    return -1;
  }

  // TODO: LockObject
  //LockSection(MUTEX_LOCK_CONNECTION);
    Connections_t::iterator iter = m_Connections.find(Member->GetConnectionName());
    if (iter == m_Connections.end())
    {// Add a new connection member to this node
      // TODO: error couldn't find connection
      return -1;
    }
    else
    {
      if (iter->second.size() <= 0)
      {
        // TODO: return error!
        return -1;
      }


      deque<IMessageHandler*>::iterator memberIter = iter->second.begin();
      while (memberIter != iter->second.end() && (*memberIter)->HandlerType != Member->HandlerType)
      {
        ++memberIter;
      }
      
      if (memberIter == iter->second.end())
      {
        // TODO: error couldn't find connected member!
        Member->TerminateConnection();
        return -1;
      }

      iter->second.erase(memberIter);
      Member->TerminateConnection();
    }
  // TODO: LockObject
  //UnlockSection(MUTEX_LOCK_CONNECTION);

  return 0;
}
