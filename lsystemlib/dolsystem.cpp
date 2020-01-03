
#include "dolsystem.h"

namespace exunit {
namespace lsystem {

DOLSystem::DOLSystem(const char *axiom, const svector &rules) : mState(axiom) {
    BuildRules(rules);
}

DOLSystem::~DOLSystem() {
}

void DOLSystem::Iterate(uint32_t n) {

    while (n--) {
        string state = mState;
        mState.clear();

        const char *s = state.c_str();
        while (*s != '\0') {
            bool ruleapplied = false;
            for (const auto &r : mRules) {
                if (r.from[0] == *s) {
                    mState = mState + r.to;
                    ruleapplied = true;
                    break;
                }
            }
            if (!ruleapplied) {
                mState = mState + *s;
            }
            ++s;
        }

        ++mGeneration;
    }
}

void DOLSystem::BuildRules(const svector &rules) {
    for (const auto &r : rules) {

        auto pos = r.find("=>");
        if (pos == string::npos) {
            XLSYS_REPORT_ERROR("failed to find => in rule, skipping");
            continue;
        }
        mRules.push_back({r.substr(0, pos), r.substr(pos + 2)});
    }
}

} // namespace lsystem
} // namespace exunit