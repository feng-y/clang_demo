#pragma once

#include <string>

class DynamicWorker {
public:
    DynamicWorker() = default;
    DynamicWorker(bool verbose) : verbose_(verbose) {}

private:
    bool verbose_ = true;
};
