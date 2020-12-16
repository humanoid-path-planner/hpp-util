// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, CNRS.
//
// This file is part of the hpp-util.
//
// hpp-util is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// hpp-util is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with hpp-util.  If not, see <http://www.gnu.org/licenses/>.

#include "config.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/filesystem.hpp> // Need C++ 17 to remove this.

#include "hpp/util/indent.hh"
#include "hpp/util/debug.hh"

#ifndef HPP_LOGGINGDIR
# error "Please define HPP_LOGGINGDIR to the default logging prefix."
#endif //! HPP_LOGGINGDIR

// Include unistd.h if available, otherwise use the dummy getpid
// function.
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#else
static int getpid ()
{
  return 0;
}
#endif // HAVE_UNISTD_H

namespace hpp
{
  namespace debug
  {

    /// \brief Environment variable used to change the logging
    /// directory.
    static const char* ENV_LOGGINGDIR = "HPP_LOGGINGDIR";

    namespace
    {
      HPP_UTIL_LOCAL void
      makeDirectory (const std::string& filename)
      {
	using namespace boost::filesystem;
	path pathname (filename);

	// FIXME: Boost 1.34.1 does not support the non-obsolete
	// equivalent of branch_path, parent_path, so bear with
	// it for now.
	std::string dirname = pathname.branch_path ().string ();

	boost::filesystem::create_directories (dirname);
      }
    }

    std::string
    getPrefix (const std::string& packageName)
    {
      std::string loggingPrefix;
      const char* env = getenv (ENV_LOGGINGDIR);

      if (env)
	loggingPrefix = env;
      else
	{
	  loggingPrefix = HPP_LOGGINGDIR;
	  if (!packageName.empty ())
	    {
	      loggingPrefix += '/';
	      loggingPrefix += packageName;
	    }
	}

      return loggingPrefix;
    }

    std::string
    getFilename (const std::string& filename,
		 const std::string& packageName)
    {
      std::string res (getPrefix (packageName));
      res += "/";
      res += filename;
      makeDirectory (res);
      return res;
    }

    Output::Output ()
    {}

    Output::~Output ()
    {}

    std::ostream&
    Output::writePrefix (std::ostream& stream,
			 const Channel& channel,
			 char const* file,
			 int line,
			 char const*)
    {
      stream
	<< channel.label () << ':'
	<< file << ':'
	<< line << ": ";
      return stream;
    }


    Channel::Channel (const char* label,
		      const subscribers_t& subscribers)
      : label_ (label),
	subscribers_ (subscribers)
    {}

    Channel::~Channel ()
    {}

    const char*
    Channel::label () const
    {
      return label_;
    }

    void
    Channel::write (char const* file,
		    int line,
		    char const* function,
		    const std::string& data)
    {
      for(Output* o: subscribers_)
	if (o)
	  o->write (*this, file, line, function, data);
    }


    void
    Channel::write (char const* file,
		    int line,
		    char const* function,
		    const std::stringstream& data)
    {
      for(Output* o: subscribers_)
	if (o)
	  o->write (*this, file, line, function, data);
    }


    ConsoleOutput::ConsoleOutput ()
    {}

    ConsoleOutput::~ConsoleOutput ()
    {}

    void
    ConsoleOutput::write (const Channel& channel,
			  char const* file,
			  int line,
			  char const* function,
			  const std::string& data)
    {
      writePrefix (std::cerr, channel, file, line, function);
      std::cerr << incindent << data << decindent << std::flush;
    }

    void
    ConsoleOutput::write (const Channel& channel,
			  char const* file,
			  int line,
			  char const* function,
			  const std::stringstream& data)
    {
      writePrefix (std::cerr, channel, file, line, function);
      std::cerr << incindent << data.rdbuf() << decindent << std::flush;
      data.rdbuf()->pubseekpos(0);
    }

    namespace
    {
      HPP_UTIL_LOCAL std::string
      makeLogFile (const JournalOutput& journalOutput)
      {
	makeDirectory (journalOutput.getFilename ());
	return journalOutput.getFilename ();
      }
    }

    JournalOutput::JournalOutput (std::string filename)
      : filename (filename),
	lastFunction (),
      stream ()
    {}

    JournalOutput::~JournalOutput ()
    {}

    // package name is set to ``hpp'' here so that
    // the journal can be shared between all hpp packages.
    // Splitting log into multiple files would make difficult
    // to track packages interactions.
    std::string
    JournalOutput::getFilename () const
    {
      static const std::string packageName = "hpp";

      std::stringstream name;
      name << filename << '.' << getpid() << ".log";
      return debug::getFilename (name.str (), packageName);
    }

    void
    JournalOutput::write (const Channel& channel,
			  char const* file,
			  int line,
			  char const* function,
			  const std::string& data)
    {
      if (!stream.is_open ()) stream.open (makeLogFile (*this).c_str ());

      if (lastFunction != function)
	{
	  if (!lastFunction.empty ())
	    {
	      writePrefix (stream, channel, file, line, function);
	      stream << "exiting " << lastFunction << iendl;
	    }

	  writePrefix (stream, channel, file, line, function);
	  stream << "entering " << function << iendl;
	  lastFunction = function;
	}

      writePrefix (stream, channel, file, line, function);
      stream << incindent << data << decindent << std::flush;
    }

    void
    JournalOutput::write (const Channel& channel,
			  char const* file,
			  int line,
			  char const* function,
			  const std::stringstream& data)
    {
      if (!stream.is_open ()) stream.open (makeLogFile (*this).c_str ());
      if (lastFunction != function)
	{
	  if (!lastFunction.empty ())
	    {
	      writePrefix (stream, channel, file, line, function);
	      stream << "exiting " << lastFunction << iendl;
	    }

	  writePrefix (stream, channel, file, line, function);
	  stream << "entering " << function << iendl;
	  lastFunction = function;
	}

      writePrefix (stream, channel, file, line, function);
      stream << incindent << data.rdbuf() << decindent << std::flush;
      data.rdbuf()->pubseekpos(0);
    }

    Logging::Logging ()
      : console (),
	journal ("journal"),
	benchmarkJournal ("benchmark"),
	error
	("ERROR", { &journal, &console }),
	warning
	("WARNING", { &journal, &console }),
	notice
	("NOTICE", { &journal, &console }),
	info
	("INFO", { &journal }),
	benchmark
	("BENCHMARK", { &benchmarkJournal })
    {}

    Logging::~Logging ()
    {}

  } // end of namespace debug.

} // end of namespace hpp.


// Global variables definitions.
namespace hpp
{
  namespace debug
  {
    HPP_UTIL_DLLAPI Logging logging;
  } // end of namespace debug
} // end of namespace hpp
