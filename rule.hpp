#ifndef __RULE_HPP__
#define __RULE_HPP__

#include <string>
#include <memory>

using std::string;
using std::shared_ptr;

namespace cs427_527
{
    class DiceRoll;
    class Scoresheet;

    class PointAmount;
    class RuleCheck;

    class Rule
    {
    public:
	// Empty Initializer
	Rule();

	// Full Initializer
	Rule(string, string, shared_ptr<PointAmount>, shared_ptr<RuleCheck>, bool);

	// Returns points awarded for rule
	int points(DiceRoll&, Scoresheet&);

	// Returns if points are applied
	bool applyPoints(DiceRoll&);

	// Returns name
	string getName();

	// Returns abbreviation
	string getAbbrev();

	// Returns rule type
	bool isPlayable();
    private:
	string name;
	string abbrev;
	shared_ptr<PointAmount> pointRule;
	shared_ptr<RuleCheck> applyRule;
	bool playable;
    };
}

#endif

