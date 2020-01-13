
#include "lsystem.h"
#include <regex>
#include <chrono>
#include <iostream>

namespace exunit {
namespace lsystem {

LSystem::LSystem(const char *axiom, const svector &rules, const char *contextignore) : mState(axiom) {

	if (contextignore) {
        mContextIgnore = contextignore;
    }

	// initialize the random number generator with time-dependent seed
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	mRNG.seed(ss);

    BuildRules(rules);
}

LSystem::~LSystem() {
}

bool LSystem::ApplyRuleSet(const rvector &rules) {
	size_t numrules = rules.size();

	//if there were no rules then we can't apply anything!
	if (numrules == 0) {
		return false;
	}

	//if there is only one rule then just apply it.
	if (numrules == 1) {
		mState = mState + rules[0].to;
		return true;
	}

	//get a random number from 0-1
	//int ruleidx = 0;
	float p = mNumGen(mRNG);
	for (const auto &r : rules) {
		if (p <= r.prob) {
			mState = mState + r.to;
			//std::cout << ruleidx << '\n';
			return true;
		}
		p -= r.prob;
		//++ruleidx;
	}

	//we fell through, probably because the rules
	//probabilites didn't add up to one!
	mState = mState + rules.back().to;
	XLSYS_REPORT_ERROR("Stocastic rule overrun");
	
	return true;
}

void LSystem::Iterate(uint32_t n) {

    while (n--) {
        string state = mState;
        mState.clear();

        const char *s = state.c_str();
        while (*s != '\0') {
            bool ruleapplied = false;

			const auto &i = mRules.find(*s);
			if (i != mRules.end()) {
				const auto &rules = i->second;
				ruleapplied = ApplyRuleSet(rules);
			}

            if (!ruleapplied) {
                mState = mState + *s;
            }
            ++s;
        }

        ++mGeneration;
    }
}

void LSystem::BuildRules(const svector &rules) {

	//looking for CHAR=DD>TOSTRING
	//for example: "a=10>ab" or "a=>ab"
	//where CHAR is 'a' and is the from part of the rule
	//      DD is the optional percentage chance of rule firing.
	//      TOSTRING is the to part of the rule.
	// match[0] is the original string.
	// match[1] is CHAR
	// match[2] is =DD> or =>
	// match[3] is DD if it's length is > 0
	// match[4] is TOSTRING

	std::regex rulerex(R"((.*)(=(\d{1,2})*>)(.*))");
	std::smatch match;

	for (const auto &r : rules) {

		if (std::regex_match(r, match, rulerex)) {
			std::string from, to;
			float percent = 1.0f;

			from = match[1];
			to = match[4];

			if (match[3].length()) {
				//we got one with a percent!
				percent = strtol(match[3].str().c_str(), nullptr, 10) / 100.0f;
			}
			mRules[from[0]].push_back({ percent, to });
		}
	}
}

} // namespace lsystem
} // namespace exunit