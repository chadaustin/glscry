#include "Run.h"


namespace scry {

void output(std::ostream& os, TestPtr test, const ResultSet& results,
            const std::string& depVar) {
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

    std::cout << "  " << test->getName() << ": "
              << descs[resultIndex].name << " = "
              << Uint64(results[resultIndex]) << " "
              << descs[resultIndex].units << std::endl;
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
    std::ofstream of(filename.c_str());
    if (!of) {
        throw std::runtime_error("Could not open " + filename);
    }

    for (size_t i = 0; i < testList.size(); ++i) {
        betweenTests();

        TestPtr test = testList[i];
        if (test->isSupported()) {
            ResultSet results = test->run(runFor);
            output(of, test, results, depVar);
        } else {
            // output a zero ?
        }
    }
    of << std::endl;
}


void runTestsRange(const std::string& filename, std::vector<TestPtr> testList,
                   float runFor, const std::string& depVar,
                   const std::string& indVar, RangePtr range
) {
    std::ofstream of(filename.c_str());
    if (!of) {
        throw std::runtime_error("Could not open " + filename);
    }

    size_t indValue;
    while (range->next(indValue)) {
        for (size_t i = 0; i < testList.size(); ++i) {
            betweenTests();

            TestPtr test = testList[i];
            test->setProperty(indVar, indValue);
            if (test->isSupported()) {
                ResultSet results = test->run(runFor);
                output(of, test, results, depVar);
            } else {
                // output a zero
            }
        }
        of << std::endl;
    }
}

}
