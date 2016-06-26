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


template<class TADSPMode>
class TStatisticsADSPModes
{
public:
  TStatisticsADSPModes()
  {
    m_CreatedADSPModes++;
    m_ActiveADSPModes++;
  }

  ~TStatisticsADSPModes()
  {
    m_DestroyedADSPModes++;
    m_ActiveADSPModes--;
  }

  static int GetCreatedADSPMode()
  {
    return m_CreatedADSPModes;
  }

  static int GetDestroyedADSPMode()
  {
    return m_DestroyedADSPModes;
  }

  static int GetActiveADSPMode()
  {
    return m_ActiveADSPModes;
  }

private:
  static int m_CreatedADSPModes;
  static int m_DestroyedADSPModes;
  static int m_ActiveADSPModes;
};

template<class TADSPMode>
int TStatisticsADSPModes<TADSPMode>::m_CreatedADSPModes;

template<class TADSPMode>
int TStatisticsADSPModes<TADSPMode>::m_DestroyedADSPModes;

template<class TADSPMode>
int TStatisticsADSPModes<TADSPMode>::m_ActiveADSPModes;
