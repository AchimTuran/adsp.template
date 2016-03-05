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
#include <memory>

// This class implements aconnection manager for IMessageHandler 
// and is based on the Monostate Pattern: http://accu.org/index.php/journals/2085


template<class T, class TAG=void>
class TMonoConnectionNode
{
public:
  TMonoConnectionNode(std::shared_ptr<T> Monostate)
  {
    if (!Monostate)
    {
      // TODO: throw exception
    }

    m_Monostate = Monostate;
  }

  TMonoConnectionNode()
  {
    if (!m_Monostate)
    {
      // TODO: throw exception
    }
  }

  inline int Register(IMessageHandler *Member)
  {
    return m_Monostate->Register(Member);
  }

  inline int Deregister(IMessageHandler *Member)
  {
    if (!m_Monostate)
    {
      return -1;
    }

    return m_Monostate->Deregister(Member);
  }

private:
  static std::shared_ptr<T> m_Monostate;
};

template<class T, class TAG>
std::shared_ptr<T> TMonoConnectionNode<T, TAG>::m_Monostate;
