#include <iostream>
#include <fstream>
#include "Context.h"
#include "Run.h"
#include "Types.h"


namespace scry {

    std::string getTitle() {
        std::ostringstream title;
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* version  = glGetString(GL_VERSION);
        title << "(" << vendor << "), (" << renderer << "), ("
              << version << ")";
        return title.str();
    }

    void generateBarGraph(
        const string& datafile,
        const std::vector<TestPtr>& testList,
        const string& resultUnits
    ) {
        string script = datafile + ".sh";
        std::ofstream plot(script.c_str());
        if (!plot) {
            return;
        }

        std::cout << std::endl;
        std::cout << "Generating gnuplot script: " << script << std::endl;

        plot << "#!/bin/sh" << std::endl
             << std::endl
             << "cat <<EOF | gnuplot\n"
             << "set terminal png size 1000\n"
             << "set output \"" << datafile << ".png\"\n"
             << "set title \"" << getTitle() << "\"\n"
             << "set xrange [-0.5:" << testList.size() - 0.5f << "]\n"
             << "set yrange [0:*]\n"
             << "set ylabel \"" << resultUnits << "\"\n" << std::flush;

        plot << "set xtics (";
        for (size_t i = 0; i < testList.size(); ++i) {
            plot << "\"" << testList[i]->getName() << "\" " << i;
            if (i + 1 < testList.size()) {
                plot << ", ";
            }
        }
        plot << ")" << std::endl;

        plot << "plot \"" << datafile << "\" using 0:1 with boxes" << std::endl
             << "EOF" << std::endl;
    }


    void generateLineGraph(
        const string& datafile,
        const std::vector<TestPtr>& testList,
        const string& resultUnits,
        const string& indVar,
        RangePtr range
    ) {
        std::string script = datafile + ".sh";
        std::ofstream plot(script.c_str());
        if (!plot) {
            return;
        }

        std::cout << std::endl;
        std::cout << "Generating gnuplot script: " << script << std::endl;

        plot << "#!/bin/sh" << std::endl
             << std::endl
             << "cat <<EOF | gnuplot\n"
             << "set terminal png size 1000\n"
             << "set output \"" << datafile << ".png\"\n"
             << "set title \"" << getTitle() << "\"\n"
             << "set yrange [0:*]\n"
             << "set xlabel \"" << indVar << "\"\n"
             << "set ylabel \"" << resultUnits << "\"\n" << std::flush;

        plot << "set xtics (";
        size_t count = 0;
        size_t out;
        while (range->next(out)) {
            if (count > 0) {
                plot << ", ";
            }
            plot << "\"" << out << "\" " << count;
            ++count;
        }
        plot << ")" << std::endl;

        plot << "plot \\" << std::endl;
        for (size_t i = 0; i < testList.size(); ++i) {
            plot << "  \"" << datafile << "\" using 0:" << (i + 1) << " title \""
                 << testList[i]->getName() << "\" with lines";
            if (i + 1 < testList.size()) {
                plot << ",\\";
            }
            plot << std::endl;
        }
        plot << "EOF" << std::endl;
    }


    void output(std::ostream& os, TestPtr test, const ResultSet& results,
                const std::string& depVar, const char* indVar = 0,
                const size_t* indValue = 0
    ) {
        std::vector<ResultDesc> descs;
        test->getResultDescs(descs);
        SCRY_ASSERT(descs.size() == results.size());

        int resultIndex = -1;
        for (size_t i = 0; i < descs.size(); ++i) {
            if (descs[i].name == depVar) {
                resultIndex = i;
                break;
            }
        }
        if (resultIndex == -1) {
            throw std::runtime_error("Test has no such result");
        }
    
        os << results[resultIndex] << " ";

        std::cout << "  " << test->getName();
        if (indVar && indValue) {
            std::cout << '(' << indVar << '=' << *indValue << ')';
        }
        std::cout << ": "
                  << descs[resultIndex].name << " = "
                  << Uint64(results[resultIndex]) << " "
                  << descs[resultIndex].units << std::endl;
    }

    void writeID(std::ostream& os) {
        os << "# Vendor = " << glGetString(GL_VENDOR) << "\n"
           << "# Renderer = " << glGetString(GL_RENDERER) << "\n"
           << "# Version = " << glGetString(GL_VERSION) << "\n";
    }

    void flip() {
        SDL_GL_SwapBuffers();
    }

    void betweenTests() {
        glClear(GL_COLOR_BUFFER_BIT);
        pumpMessages();
        flip();
    }

    void runTests(const std::string& filename, std::vector<TestPtr> testList,
                  float runFor, const std::string& depVar
    ) {
        std::cout << std::endl;
        std::cout << "Generating data for " << filename << std::endl;
    
        std::ofstream of(filename.c_str());
        if (!of) {
            throw std::runtime_error("Could not open " + filename);
        }

        writeID(of);

        for (size_t i = 0; i < testList.size(); ++i) {
            betweenTests();

            TestPtr test = testList[i];
            if (test->isSupported()) {
                ResultSet results = test->run(runFor);
                output(of, test, results, depVar);
                of << std::endl;
            } else {
                // output a zero ?
            }
        }

        if (!testList.empty()) {
            TestPtr test = testList[0];
            std::vector<ResultDesc> descs;
            test->getResultDescs(descs);
            const ResultDesc& desc = descs[0];

            generateBarGraph(filename, testList,
                             desc.name + " in " + desc.units);
        }
    }


    void runTestsRange(const string& filename, std::vector<TestPtr> testList,
                       float runFor, const std::string& depVar,
                       const string& indVar, RangePtr range
    ) {
        std::cout << std::endl;
        std::cout << "Generating data for " << filename << std::endl;
    
        std::ofstream of(filename.c_str());
        if (!of) {
            throw std::runtime_error("Could not open " + filename);
        }

        writeID(of);

        size_t indValue;
        while (range->next(indValue)) {
            for (size_t i = 0; i < testList.size(); ++i) {
                betweenTests();

                TestPtr test = testList[i];
                test->setProperty(indVar, indValue);
                if (test->isSupported()) {
                    ResultSet results = test->run(runFor);
                    output(of, test, results, depVar,
                           indVar.c_str(), &indValue);
                } else {
                    // output a zero
                }
            }
            of << std::endl;
        }

        if (!testList.empty()) {
            TestPtr test = testList[0];
            std::vector<ResultDesc> descs;
            test->getResultDescs(descs);
            const ResultDesc& desc = descs[0];

            generateLineGraph(filename, testList,
                              desc.name + " in " + desc.units,
                              indVar, range);
        }
    }

}
