#ifndef TRIAGARA_GEOMETRY_TEST_H
#define TRIAGARA_GEOMETRY_TEST_H


#include "Base.h"
#include "GeometryGenerator.h"
#include "Test.h"


TRIAGARA_BEGIN_NAMESPACE

class GeometryTest : public Test {
public:
    TRIAGARA_BEGIN_RESULT_DESCS()
        TRIAGARA_RESULT_DESC("TriangleRate", "tri/s")
    TRIAGARA_END_RESULT_DESCS()

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

TRIAGARA_END_NAMESPACE


#endif
