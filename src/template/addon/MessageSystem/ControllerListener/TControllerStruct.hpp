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



// TODO: Logging
//#include "logger.hpp"
#include "Addon/MessageSystem/ControllerListener/TControllerMemcpy.hpp"


template<typename TStruct, typename TElement, typename TInternalFmt=TElement>
class TControllerStruct : public IController
{
protected:
  template<typename TStruct, typename TElement>
  class TElementPtr
  {
  public:
    TElementPtr(TStruct **StructPtr, bool IsPtrElement, unsigned int StructOffset = 0, unsigned int ElementGrpSize = 1, unsigned int ElementOffset = 0)
    {
      if (ElementGrpSize < 1)
      {
        ElementGrpSize = 1;
      }

      m_StructPtr = (char**)StructPtr;
      m_StructOffset = StructOffset;
      m_ElementGrpSize = ElementGrpSize;
      m_ElementOffset = ElementOffset;
      m_IsPtrElement = IsPtrElement;
    }

    inline TElement& operator [] (unsigned int ElementIdx)
    {
      char *elementPtr = NULL;
      if (m_IsPtrElement)
      {
        elementPtr = *((char**)(*m_StructPtr + m_StructOffset));
      }
      else
      {
        elementPtr = *m_StructPtr + m_StructOffset;
      }
      elementPtr += m_ElementOffset;
      elementPtr += m_ElementGrpSize*ElementIdx;

      return *(TElement*)elementPtr;
    }

  private:
    unsigned int  m_StructOffset;
    unsigned int  m_ElementGrpSize;
    unsigned int  m_ElementOffset;
    bool          m_IsPtrElement;
    char          **m_StructPtr;
  };


public:
  TControllerStruct(TStruct **StructPtr, 
                    std::string Name, RTComSignal_t Signal,
                    TInternalFmt Scale, unsigned int MaxElements,
                    bool IsPtrElement, unsigned int StructOffset = 0, unsigned int ElementGrpSize = 1, unsigned int ElementOffset = 0) :
    IController(Name, Signal),
    m_Element(StructPtr, IsPtrElement, StructOffset, ElementGrpSize, ElementOffset)
  {
    if (MaxElements < 1)
    {
      MaxElements = 1;
    }

    m_Scale       = Scale;
    m_MaxElements = MaxElements;
  }


  ~TControllerStruct()
  {
  }


  virtual bool ControllParameter(CMessage &Message)
  {
    if (Message.GetSignal() != this->Signal)
    {
      // TODO: Logging
      //LOG_ERROR_FUNCTION << "Message.GetSignalID() != this->GetSignalID()" << std::endl;
      return false;
    }

    TInternalFmt m_Value;
    if (!Message.GetData(&m_Value, sizeof(TInternalFmt)))
    {
      LOG_ERROR_FUNCTION << "!Message.GetDataPtr(p)" << std::endl;
      return false;
    }

    // TODO: Logging
    //LOG_DEBUG_NAME(Name) << "controller changed parameter to: \"" << m_Value << "\"" << std::endl;
    m_Value *= m_Scale;
    // TODO: Logging
    //LOG_DEBUG_NAME(Name) << "controller scaled parameter to: \"" << m_Value << "\"" << std::endl;

    for (unsigned int ii = 0; ii < m_MaxElements; ii++)
    {
      m_Element[ii] = (TElement)m_Value;
    }

    return true;
  }


protected:
  unsigned int  m_MaxElements;
  TInternalFmt  m_Scale;
  TElementPtr<TStruct, TElement> m_Element;
};
