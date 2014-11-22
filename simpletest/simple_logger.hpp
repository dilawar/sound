/*
 * ==============================================================================
 *
 *       Filename:  simple_logger.hpp
 *
 *    Description:  A simple XML based logger.
 *
 *        Version:  1.0
 *        Created:  Saturday 24 May 2014 06:25:10  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  NCBS Bangalore
 *  
 *  Copyright (C) 2014, Dilawar Singh, NCBS Bangalore
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 * 
 * ==============================================================================
 */

#ifndef  MOOSE_LOGGER_INC
#define  MOOSE_LOGGER_INC

#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sys/stat.h>
#include <fstream>

using namespace std;

#define T_RESET       "\033[0m"
#define T_BLACK       "\033[30m"      /* Black */
#define T_RED         "\033[31m"      /* Red */
#define T_GREEN       "\033[32m"      /* Green */
#define T_YELLOW      "\033[33m"      /* Yellow */
#define T_BLUE        "\033[34m"      /* Blue */
#define T_MAGENTA     "\033[35m"      /* Magenta */
#define T_CYAN        "\033[36m"      /* Cyan */
#define T_WHITE       "\033[37m"      /* White */
#define T_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define T_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define T_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define T_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define T_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define T_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define T_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define T_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

class SimpleLogger {

    public:

        /**
         * @brief Constructor of logger. The wrapper script of moose must make
         * sure that $HOME/.moose is created. The logger will write to
         * $HOME/.moose/log.
         */
        SimpleLogger()
        {
            startTime = timeStamp();
            homeDir = getenv("HOME");

            logSS << "<log simulator=\"moose\">" << endl;
            logSS << "\t<start_time>" << startTime << "</start_time>" << endl;
            logSS << "\t<messages>" << endl;

#ifdef OS_WINDOWS 
            outputFile = homeDir + "\\.moose\\log";
#else
            outputFile = homeDir + "/.moose/log";
#endif
        }

        ~SimpleLogger()
        {

        }

        /**
         * @brief Get current timestamp.
         *
         * @return  A string represeting current timestamp.
         */
        const std::string timeStamp() 
        {
            time_t     now = time(0);
            struct tm  tstruct;
            char       buf[80];
            tstruct = *localtime(&now);
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
            return buf;
        }

        /**
         * @brief When an element is created in moose, log its presense in this
         * map.
         *
         * @param type Type of element.
         * @param path Path of the element.
         */
        void updateGlobalCount(string type)
        {
            if(elementsMap.find(type) == elementsMap.end())
                elementsMap[type] = 1;
            else
                elementsMap[type] = elementsMap[type] + 1;
        }

        template<typename A, typename B>
        string mapToString(const map<A, B>& m, string title = "") const
        {
            unsigned width = 50;
            stringstream ss;

            ss << title;
            for(unsigned i = 0; i < width - title.size(); ++i) 
                ss << "~";
            ss << endl;

            typename map<A, B>::const_iterator it;
            for( it = m.begin(); it != m.end(); it++)
                ss << setw(width/2) << it->first << setw(width/2) << it->second << endl;

            for(unsigned i = 0; i < width; ++i) 
                ss << "=";

            ss << endl;
            return ss.str();
        }

        /**
         * @brief Dump statistics onto console.
         *
         * @param which If which is 0 then print elements inside moose, if it is
         * 1 then print total time taken during simulation.
         *
         * @return
         */
        string dumpStats( int which )
        {
            stringstream ss;
            // unsigned width = 50;
            ss << endl;
            if(which == 0)
                ss << mapToString<string, unsigned long>(elementsMap, "data_structure");

            else if( which == 1)
            {
                timekeeperMap["Simulation"] = accumulate(
                        simulationTime.begin()
                        , simulationTime.end()
                        , 0.0
                        );
                timekeeperMap["Initialization"] = accumulate(
                        initializationTime.begin()
                        , initializationTime.end()
                        , 0.0
                        );
                timekeeperMap["Creation"] = accumulate(
                        creationTime.begin()
                        , creationTime.end()
                        , 0.0
                        );

                ss << mapToString<string, float>( timekeeperMap, "simulation_stats" );
            }
            return ss.str();
        }


        /**
         * @brief Converts a map to XML like staructure.
         *
         * @tparam A
         * @tparam B
         * @param ss Input ostringstream.
         * @param m std::map
         * @param tagName This is current tag name. Useful when recursing.
         * @param indent Usually a tag character.
         */
        template<typename A, typename B>
        void mapToXML(ostringstream& ss, const map<A, B>& m, const char* tagName
                , unsigned indent) const
        {
            string prefix = "";
            for(unsigned int i = 0; i < indent; ++i)
                prefix += "\t";
            ss << prefix << "<" << tagName << ">" << endl;

            typename map<A, B>::const_iterator it;
            for(it = m.begin(); it != m.end(); it++)
            {
                ss << prefix << prefix 
                    << "<" << it->first << ">" 
                    << it->second 
                    << "</" << it->first << ">" << endl;
            }

            ss << prefix << "</" << tagName << ">" << endl;
        }

        /**
         * @brief Convert this logger to XML.
         *
         * @return A XML string.
         */
        string save( const char* outFile = "")
        {
            string logFile = string(outFile);
            if(logFile.size() == 0)
                logFile = outputFile;

            // End of messages.
            logSS << "\t</messages>" << endl;

            mapToXML<string, unsigned long>(logSS, elementsMap, "data_structure", 1);
            mapToXML<string, float>(logSS, timekeeperMap, "times", 1);

            logSS << "\t<end_time>" << timeStamp() << "</end_time>" << endl;

            logSS << "</log>" << endl;

            fstream logF;
            logF.open(logFile.c_str(), std::fstream::out | std::fstream::app);
            logF << logSS.str();
            logF.close();
            return logSS.str();
        }
        
        /**
         * @brief Checks if given directory path exists on system.
         *
         * @param name Directory path as string.
         *
         * @return true, if directory exists, false otherwise.
         */
        bool isDir( const std::string& name )
        {
#ifdef OS_WINDOWS
            struct _stat buf;
            int result = _stat( name.c_str(), &buf );
#else
            struct stat buf;
            int result = stat( name.c_str(), &buf );
#endif
            if(result == 0 && S_ISDIR(buf.st_mode))
                return true;
            else
                return false;
        }

        /**
         * @brief Dumps a message to console.
         *
         * @param type Type of message e.g. WARN, ERROR, FATAL etc.
         * @param msg  Message to dump.
         * @param autoFormat Use ` to demarcate coloring of output.
         */
        void dump(string type, string msg, bool autoFormat = true)
        {

#ifndef ENABLE_LOGGER
            return;
#endif
            stringstream ss;
            ss << "[" << type << "] ";
            bool set = false;
            bool reset = true;
            string color = T_GREEN;
            if(type == "WARNING" || type == "WARN" || type == "FIXME")
                color = T_YELLOW;
            else if(type == "DEBUG")
                color = T_CYAN;
            else if(type == "ERROR" || type == "FAIL" || type == "FATAL" || type == "ASSERT_FAILURE")
                color = T_RED;
            else if(type == "INFO" || type == "EXPECT_FAILURE")
                color = T_MAGENTA;
            else if(type == "LOG")
                color = T_BLUE;

            for(unsigned int i = 0; i < msg.size(); ++i)
            {
                if('`' == msg[i])
                {
                    if(!set and reset) 
                    {
                        set = true;
                        reset = false;
                        ss << color;
                    }
                    else if(set && !reset)
                    {
                        reset = true;
                        set = false;
                        ss << T_RESET;
                    }
                }
                else if('\n' == msg[i])
                    ss << "\n + ";
                else
                    ss << msg[i];
            }

            /*  Be safe than sorry */
            if(!reset)
                ss << T_RESET;

            logSS << ss.str() << endl;
#if QUIET_MODE || VERBOSITY < 0
            return;
#endif
            cerr << ss.str() << endl;
        }

    private:
        map<string, unsigned long> elementsMap;
        map<string, float> timekeeperMap;

    public:

        string mooseDir;
        string homeDir;

        string outputFile;
        string startTime;
        string endTime;

        ostringstream logSS;

        /* Map to keep simulation run-time data. */
        vector<float> simulationTime;
        vector<float> initializationTime;
        vector<float> creationTime;
};

extern SimpleLogger logger;

#endif   /* ----- #ifndef MOOSE_LOGGER_INC  ----- */
