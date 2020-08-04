#include "log.h"

#ifndef _FINALRELEASE

namespace fml
{

  //TODO: This requires that the clog streambuf hasn't been altered already.
  bool log_LogConsoleAndFileBuffer = true;
  std::filebuf* log_TargetFileBuffer = nullptr;
  std::streambuf* _log_OriginalClogBuffer = std::clog.rdbuf();

  char* formatted_time() {

    static time_t rawTime;
    static char buff[70];
    static struct tm myTime;

    rawTime = time( nullptr );
    localtime_s( &myTime, &rawTime );

    strftime( buff, sizeof( buff ), "%c", &myTime );
    return &buff[0];

  }

}

#endif