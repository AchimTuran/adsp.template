#pragma once

#define LOG         if(KODI) KODI->Log
#define LOGERROR    ADDON::LOG_ERROR
#define LOGDEBUG    ADDON::LOG_DEBUG
#define LOGINFO     ADDON::LOG_INFO
#define LOGNOTICE   ADDON::LOG_NOTICE
