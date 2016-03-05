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



#include <map>
#include <deque>

#include "Addon/MessageSystem/Interfaces/IConnectionPort.hpp"
//#include "ThreadSafeMessages.hpp"

#include "Addon/MessageSystem/Communication/TMonoConnectionPort.hpp"


class CConnectionNode;
struct s_UIConnectionNode {};

typedef TMonoConnectionNode<CConnectionNode> ConnectionManager_t;


class CConnectionNode : public IConnectionNode//, private CThreadSafeMessages
{
public:
  CConnectionNode(std::string Name);
  ~CConnectionNode();

  virtual int Register(IMessageHandler *Member);
  virtual int Deregister(IMessageHandler *Member);

private:
  typedef std::map < std::string, std::deque<IMessageHandler*> > Connections_t;
  Connections_t m_Connections;
};
