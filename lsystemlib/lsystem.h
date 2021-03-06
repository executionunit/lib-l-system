#ifndef EXUNIT_LSYSTEMLIB_DOLSYSTEM_H
#define EXUNIT_LSYSTEMLIB_DOLSYSTEM_H

#include "lsystemlibconfig.h"

#include <stdint.h>
#include <random>

namespace exunit {
namespace lsystem {

/**
** Deterministic Context Free L-System.
*/
class LSystem {
public:
    using string = XLSYS_STRING;

    /* a vector of strings */
    using svector = XLSYS_VECTOR<string>;

    /* rule transform */
    struct Rule {

        float prob;      /*< probability of this rule firing 0-1 (default 1.0f)*/
        string  pre, post; /*< pre and post condition or \0 if there is no condition (default \0)*/

        string to;

        Rule(const string &t, float probability) : to(t), prob(probability), pre(), post() {
        }
        Rule(const string &t, const string &precond, const string &postcond) : to(t), prob(1.0f), pre(precond), post(postcond) {
        }

		bool is_context_sensitive()const noexcept {
			return pre.length() > 0 || post.length() > 0;
		}

		bool precond_match(const char *spos, const char *sstart)const noexcept;
		bool postcond_match(const char *spos, const char *sstart)const noexcept;
    };

    using rvector = XLSYS_VECTOR<Rule>;

    /* a vector of rules */
    using rmap = XLSYS_UMAP<char, rvector>;

    /**
    ** @param axiom the starting condition of the system eg: "F"
    ** @param rules a vector of rules of the form X=>X' eg: {"F=>FS", "S=>F"}
    ** @param contextignore string of tokens(characters) to be ignored when scoping context. eg: "+-"
    */
    LSystem(const char *axiom, const svector &rules, const char *contextignore = nullptr);
    ~LSystem();

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
    const rmap &GetRules() const {
        return mRules;
    }
    void BuildRules(const svector &rules);

    uint32_t GetGeneration() const {
        return mGeneration;
    }

private:
    rmap     mRules;
    string   mState;
    string   mContextIgnore; /*< tokens to ignore when context matching.*/
    uint32_t mGeneration{0};

    std::mt19937_64                       mRNG;
    std::uniform_real_distribution<float> mNumGen{0, 1};

    bool ApplyRuleSet(const rvector &rules, const char *spos, const char *sstart);
};

} // namespace lsystem
} // namespace exunit

#endif // header guard