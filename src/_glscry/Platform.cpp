/* [Begin Copyright Header]
 *
 * GLScry - OpenGL Performance Analysis Tool
 * Copyright (C) 2004-2005  Iowa State University
 * 
 * This software is licensed under the terms of the GNU Lesser Public
 * License, version 2.1, as published by the Free Software Foundation.  
 * See the file COPYRIGHT.txt for details.
 * 
 * Authors:
 *   Chad Austin <aegisk@iastate.edu>
 *   Dirk Reiners <dreiners@iastate.edu>
 *
 * [End Copyright Header] */
#include <vector>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "Platform.h"
#include "Types.h"
using namespace boost;
using namespace boost::python;


#ifdef WIN32

#include <windows.h>

namespace scry {

    void breakIfDebugging() {
        if (IsDebuggerPresent()) {
            DebugBreak();
        }
    }

}

#else

namespace scry {

    void breakIfDebugging() {
    }

}

#endif




namespace scry {

    struct Processor {
        Processor() {
        }

        Processor(const string& type, const string& speed) {
            this->type = type;
            this->speed = speed;
        }

        bool operator==(const Processor& rhs) const {
            return type == rhs.type && speed == rhs.speed;
        }

        string type;
        string speed;
    };
    typedef std::vector<Processor> ProcessorList;

    ProcessorList getProcessors();
    string getMemorySize();

    void bindPlatform() {
        class_<Processor>("Processor", no_init)
            .def(init<>())
            .def(init<string, string>())
            .def_readonly("type",  &Processor::type)
            .def_readonly("speed", &Processor::speed)
            ;

        class_<ProcessorList>("ProcessorList")
            .def(vector_indexing_suite<ProcessorList>())
            ;

        def("getProcessors", getProcessors);
        def("getMemorySize", getMemorySize);
    }

}

#if defined(__CYGWIN__) || defined(__linux)  // SUPPORTS /proc FILESYSTEM

#include <fstream>

namespace scry {

    string ltrim(const string& s) {
        for (size_t i = 0; i < s.size(); ++i) {
            if (!isspace(s[i])) {
                return s.substr(i);
            }
        }

        return "";
    }

    string rtrim(const string& s) {
        for (int i = s.size() - 1; i >= 0; --i) {
            if (!isspace(s[i])) {
                return s.substr(0, i + 1);
            }
        }

        return "";
    }

    string trim(const string& s) {
        return ltrim(rtrim(s));
    }

    ProcessorList getProcessors() {
        std::ifstream file("/proc/cpuinfo");
        if (!file) {
            return ProcessorList(1, Processor("/proc/cpuinfo can't be read.",
                                              "/proc/cpuinfo can't be read."));
        }

        ProcessorList rv;
        int current = -1;

        std::string line;
        while (getline(file, line)) {
            size_t i = line.find(':');
            if (i == string::npos) {
                continue;
            }

            string left = trim(line.substr(0, i));
            string right = trim(line.substr(i + 1));
            if (left == "processor") {
                current = atoi(right.c_str());
                if (current < 0) {
                    continue;
                }

                if (unsigned(current + 1) > rv.size()) {
                    rv.resize(current + 1);
                }
            } else if (left == "model name") {
                if (current >= 0) {
                    rv[current].type = right;
                }
            } else if (left == "cpu MHz") {
                if (current >= 0) {
                    rv[current].speed = right;
                }
            }
        }

        return rv;
    }

    string getMemorySize() {
        std::ifstream file("/proc/meminfo");
        if (!file) {
            return "/proc/meminfo can't be read.";
        }

        std::string line;
        while (getline(file, line)) {
            if (line.substr(0, 9) == "MemTotal:") {
                return trim(line.substr(9));
            }
        }

        return "Unknown";
    }

}

#elif defined(WIN32) || defined(_WIN32)  // ******* WINDOWS

#include <windows.h>
#include "CPUInfo.h"

namespace scry {

    ProcessorList getProcessors() {
        std::vector<CPUInfo> info(getCPUCount());
        int actual = getMultipleCPUInfo(&info[0]);

        ProcessorList rv;
        for (int i = 0; i < actual; ++i) {
            char speed[100];
            sprintf(speed, "%d MHz", info[i].frequency);
            rv.push_back(Processor(
                info[i].getProcessorName(),
                speed));
        }
        return rv;
    }

    string getMemorySize() {
        MEMORYSTATUS mem;
        GlobalMemoryStatus(&mem);

        char buffer[100];
        sprintf(buffer, "%d MB", int(mem.dwTotalPhys / 1000000));
        return buffer;
    }

}

#elif defined (__sgi)  // *********************** SGI IRIX

namespace scry {

    ProcessorList getProcessors() {
        return "Unimplemented check.";
    }

    string getMemorySize() {
        return "Unimplemented check.";
    }

}

#else  // *************************************** UNKNOWN PLATFORM

namespace scry {

    ProcessorList getProcessors() {
        ProcessorList rv;
        rv.push_back(Processor("Unknown Platform", "Unknown Platform"));
        return rv;
    }

    string getMemorySize() {
        return "Unknown Platform";
    }

}

#endif
