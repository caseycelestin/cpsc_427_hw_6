#ifndef __RULETYPES_HPP__
#define __RULETYPES_HPP__

#include <string>
#include <memory>
#include <vector>

using std::string;
using std::shared_ptr;
using std::vector;

namespace cs427_527
{
    class Scoresheet;
    class DiceRoll;

    class PointAmount
    {
    public:
	virtual ~PointAmount();
	virtual int points(DiceRoll, Scoresheet) = 0;
    };

    class RuleCheck
    {
    public:
	virtual ~RuleCheck();
	virtual bool applyPoints(DiceRoll) = 0;
    };
    
    class AllSum : public PointAmount
    {
    public:
	virtual int points(DiceRoll, Scoresheet) override;
    };

    class Fixed : public PointAmount
    {
    public:
	Fixed(int v);
	virtual int points(DiceRoll, Scoresheet) override;
    private:
	int value;
    };

    class OneSum : public PointAmount
    {
    public:
	OneSum(int n);
	virtual int points(DiceRoll, Scoresheet) override;
    private:
	int number;
    };

    class Bonus : public PointAmount
    {
    public:
	Bonus(int t, int b);
	virtual int points(DiceRoll, Scoresheet) override;
    private:
	int threshold;
	int bonus;

    };		

    class Total : public PointAmount
    {
    public:
	virtual int points(DiceRoll, Scoresheet) override;
    };

    class NoCheck : public RuleCheck
    {
    public: 
	virtual bool applyPoints(DiceRoll) override;
    };

    class FullHouse : public RuleCheck
    {
    public:
	virtual bool applyPoints(DiceRoll) override;
    };

    class Straights : public RuleCheck
    {
    public:
	Straights(int s);
	virtual bool applyPoints(DiceRoll) override;
    private:
	int size;
    };

    class OfAKind : public RuleCheck
    {
    public:
	OfAKind(int n);
	virtual bool applyPoints(DiceRoll) override;
    private:
	int number;
    };

    // Mystery Rules
    
    class AllSum_Fixed : public PointAmount
    {
    public:
	AllSum_Fixed(int f);
	virtual int points(DiceRoll, Scoresheet) override;
    private:
	int fixed;
    };

    class Tiered : public PointAmount
    {
    public:
	Tiered(vector<int> v, vector<int> t);
	virtual int points(DiceRoll, Scoresheet) override;
    private:
	vector<int> values;
	vector<int> thresh;
    };

    class ZBonus : public PointAmount
    {
    public:
	ZBonus(int a);
	virtual int points(DiceRoll, Scoresheet) override;
    private:
	int adder;
	int count;
	shared_ptr<RuleCheck> applyRule; 
	string str;
	int prevScore;
    };

    class TwoPair : public RuleCheck
    {
    public:
	virtual bool applyPoints(DiceRoll) override;
    };

    class YortStraight : public RuleCheck
    {
    public:
	YortStraight(int s);
	virtual bool applyPoints(DiceRoll) override;
    private:
	int start;
    };

    class Yortzie : public RuleCheck
    {
    public:
	virtual bool applyPoints(DiceRoll) override;
    };
}
#endif
