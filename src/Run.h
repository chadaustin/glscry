#ifndef SCRY_RUN_H
#define SCRY_RUN_H


#include "Range.h"
#include "Test.h"


namespace scry {

    void runTests(const std::string& filename,
                  std::vector<TestPtr> testList,
                  float runFor,
                  const std::string& depVar);

    void runTestsRange(const std::string& filename,
                       std::vector<TestPtr> testList,
                       float runFor,
                       const std::string& depVar,
                       const std::string& indVar,
                       RangePtr range);

}


#endif
