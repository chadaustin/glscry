#ifndef SCRY_GEOMETRY_TEST_H
#define SCRY_GEOMETRY_TEST_H


#include "Base.h"
#include "GeometryGenerator.h"
#include "Test.h"


SCRY_BEGIN_NAMESPACE

class GeometryTest : public Test {
public:
    SCRY_BEGIN_RESULT_DESCS()
        SCRY_RESULT_DESC("TriangleRate", "tri/s")
    SCRY_END_RESULT_DESCS()

    GeometryTest(const GeometryGenerator* gen) {
        assert(gen);
        _generator = gen;
    }

    void   setBatchSize(size_t size) { _batchSize = size; }
    size_t getBatchSize() const      { return _batchSize; }

    void setProperty(const std::string& name, size_t value) {
        if (name == "BatchSize") {
            setBatchSize(value);
        } else {
            assert(false && "Invalid Property Name");
        }
    }

protected:
    const std::vector<Triangle>& getTriangleBuffer() {
        if (_batchSize != _triangleBuffer.size()) {
            _generator->generate(_triangleBuffer, _batchSize);
        }
        return _triangleBuffer;
    }

private:
    Inited<size_t, 4096> _batchSize;

    const GeometryGenerator* _generator;
    std::vector<Triangle> _triangleBuffer;
};

SCRY_END_NAMESPACE


#endif
