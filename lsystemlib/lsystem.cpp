
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

/*
* @rules the rules to apply to the state
* @spos the current position in the old state we are processing
* @start the start of the old state.
*/
bool LSystem::ApplyRuleSet(const rvector &rules, const char *spos, const char *sstart) {
	size_t numrules = rules.size();

	//if there were no rules then we can't apply anything!
	if (numrules == 0) {
		return false;
	}

	//process context sensitive rules first if there are any
	//should probably optimize this?
	for (const auto &r : rules) {
		if (r.is_context_sensitive()) {
			
		}
	}

	//get a random number from 0-1
	float p = mNumGen(mRNG);
	for (const auto &r : rules) {
		if (p <= r.prob) {
			mState.append(r.to);
			return true;
		}
		p -= r.prob;
	}

	//we fell through, probably because the rules
	//probabilites didn't add up to one!
	mState.append(rules.back().to);
	XLSYS_REPORT_ERROR("Stocastic rule overrun");
	
	return true;
}

void LSystem::Iterate(uint32_t n) {

    while (n--) {
		//swap the old state in to state so we can
		//update mState
		//TODO just allocate a big ass buffer and split
		// it in to two here rather than allocate memory
		// for a string.
		string state;
		std::swap(mState, state);

		// at least this big, it's going to be a lot bigger probably
		// but what hueristic to use?
		mState.reserve(state.size()); 
        

        const char *s = state.c_str();
        while (*s != '\0') {
            bool ruleapplied = false;

			const auto &i = mRules.find(*s);
			if (i != mRules.end()) {
				const auto &rules = i->second;
				ruleapplied = ApplyRuleSet(rules, s, state.c_str());
			}

            if (!ruleapplied) {
                mState.push_back(*s);
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
			mRules[from[0]].push_back(Rule{to, percent });
		}
	}
}

bool LSystem::Rule::precond_match(const char *spos, const char *sstart)const noexcept {
	return false;
}

bool LSystem::Rule::postcond_match(const char *spos, const char *sstart)const noexcept {
	return false;
}


} // namespace lsystem
} // namespace exunit