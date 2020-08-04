#pragma once

#ifdef _FINALRELEASE
#define Log(X)
#else

#include <time.h>
#include <iostream>
#include <fstream>

namespace fml
{

  //! Decide to write to console and/or target file buffer.
  extern bool log_LogConsoleAndFileBuffer;

  //! The buffer the log will send messages via clog to.
  extern std::filebuf* log_TargetFileBuffer;

  //! The original clog buffer.
  extern std::streambuf* _log_OriginalClogBuffer;

  char* formatted_time();


  //! Part 3/3 - Writes a message to clog and endlines.
  template<typename First>
  void _LogIterator( const First& msg )
  {
    std::clog << msg << '\n';
  }

  //! Part 2/3 - Writes a message to clog and endlines.
  template<typename First, typename ...Rest>
  void _LogIterator( const First& msg, const Rest& ...params )
  {
    std::clog << msg;
    _LogIterator( params... );
  }

  //! Part 1/3 - Writes a message to clog and endlines.
  template<typename ...Rest>
  void Log( Rest... params )
  {
    if ( log_TargetFileBuffer != nullptr && log_TargetFileBuffer->is_open() )
    {
      std::clog.rdbuf( log_TargetFileBuffer );
    }

    char* myTime = formatted_time();
    std::clog << myTime << '\t';
    _LogIterator( params... );
    std::clog.rdbuf( _log_OriginalClogBuffer );

    if ( log_LogConsoleAndFileBuffer ) {
      std::clog << myTime << '\t';
      _LogIterator( params... );
    }

  }


}

#endif