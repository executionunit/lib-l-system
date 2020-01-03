#ifndef EXUNIT_LSYSTEMLIB_DOLSYSTEM_H
#define EXUNIT_LSYSTEMLIB_DOLSYSTEM_H

#include "lsystemlibconfig.h"

#include <stdint.h>

namespace exunit {
namespace lsystem {

/**
** Deterministic Context Free L-System.
*/
class DOLSystem {
public:
    using string = XLSYS_STRING;

    /* rule transform */
    struct Rule {
        string from;
        string to;
    };

    /* a vector of rules */
    using rvector = XLSYS_VECTOR<Rule>;

    /* a vector of strings */
    using svector = XLSYS_VECTOR<XLSYS_STRING>;

    DOLSystem(const char *axiom, const svector &rules);
    ~DOLSystem();

    void Iterate(uint32_t n = 1);

    const char *GetState() const {
        return mState.c_str();
    }
    size_t GetStateSize() const {
        return mState.size();
    }
    uint32_t GetNumRules() const {
        return (uint32_t)mRules.size();
    }
    const rvector &GetRules() const {
        return mRules;
    }
    void BuildRules(const svector &rules);

    uint32_t GetGeneration() const {
        return mGeneration;
    }

private:
    rvector  mRules;
    string   mState;
    uint32_t mGeneration{0};
};

} // namespace lsystem
} // namespace exunit

#endif // header guard