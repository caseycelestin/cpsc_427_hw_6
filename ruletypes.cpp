#include "ruletypes.hpp"

#include "diceroll.hpp"
#include "scoresheet.hpp"

#include <vector>

using std::vector;
using std::make_shared;

namespace cs427_527
{
    PointAmount::~PointAmount()
    {
    }

    RuleCheck::~RuleCheck()
    {
    }
    
    int AllSum::points(DiceRoll roll, Scoresheet sheet)
    {
	return roll.total();
    }

    Fixed::Fixed(int v)
    {
	value = v;
    }

    int Fixed::points(DiceRoll roll, Scoresheet sheet)
    {
	return value;
    }

    OneSum::OneSum(int n)
    {
	number = n;
    }

    int OneSum::points(DiceRoll roll, Scoresheet sheet)
    {
	return number * roll.count(number);
    }

    Bonus::Bonus(int t, int b)
    {
	threshold = t;
	bonus = b;
    }

    int Bonus::points(DiceRoll roll, Scoresheet sheet)
    {
	int total = 0;
	vector<int> scores = sheet.getScores();
	for(int i = 0; i < roll.NUM_SIDES; i++)
	{
	    int add = scores[i];
	    if(add == -1)
	    {
		add = 0;
	    }

	    total += add;
	}
	if(total >= threshold)
	{
	    return bonus;
	}
	return 0;
    }

    int Total::points(DiceRoll, Scoresheet sheet)
    {
	vector<int> scores = sheet.getScores();
	int total = 0;

	for(auto it = scores.begin(); it < scores.end() - 1; it++)
	{
	    int add = *it;
	    if(add == -1)
	    {
		add = 0;
	    }
	    total += add;
	}

	return total;
    }

    bool NoCheck::applyPoints(DiceRoll roll)
    {
	return true;
    }

    bool FullHouse::applyPoints(DiceRoll roll)
    {
	bool three = false;
	bool two = false;

	for(int i = 1; i <= roll.NUM_SIDES; i++)
	{
	    if(roll.count(i) == 2)
	    {
		two = true;
	    }
	    if(roll.count(i) == 3)
	    {
		three = true;
	    }
	}

	return two && three;
    }

    Straights::Straights(int s)
    {
	size = s;
    }

    bool Straights::applyPoints(DiceRoll roll)
    {
	int i = 1;
	int ref = 1;
	int count = 0;

	while(count < size)
	{
	    if(ref == (roll.NUM_SIDES - size + 2))
	    {
		return false;
	    }


	    if(roll.count(i) != 0)
	    {
		count++;
		i++;
	    }
	    else
	    {
		count = 0;
		ref++;
		i = ref;
	    }
	}

	return true;
    }

    OfAKind::OfAKind(int n)
    {
	number = n;
    }

    bool OfAKind::applyPoints(DiceRoll roll)
    {
	for(int i = 1; i <= roll.NUM_SIDES; i++)
	{
	    if(roll.count(i) >= number)
	    {
		return true;
	    }
	}

	return false;
    }

    // Mystery Rules	

    AllSum_Fixed::AllSum_Fixed(int f)
    {
	fixed = f;
    }

    int AllSum_Fixed::points(DiceRoll roll, Scoresheet sheet)
    {
	return roll.total() + fixed;
    }

    Tiered::Tiered(vector<int> v, vector<int> t)
    {
	values = v;
	thresh = t;
    }

    int Tiered::points(DiceRoll roll, Scoresheet sheet)
    {
	int total = 0;
	vector<int> scores = sheet.getScores();
	for(int i = 0; i < roll.NUM_SIDES; i++)
	{
	    int add = scores[i];
	    if(add == -1)
	    {
		add = 0;
	    }

	    total += add;
	}
	if(total < thresh[0])
	{
	    return 0;
	}

	int i = 1;
	for(auto it = values.begin(); it < values.end() - 1; it++)
	{
	    if(total < thresh[i])
	    {
		return *it;
	    }
	    i++;
	}
	return values[i-1];
    }

 

    bool TwoPair::applyPoints(DiceRoll roll)
    {
	bool check = false;
	for(int i = 1; i <= roll.NUM_SIDES; i++)
	{
	    if(roll.count(i) > 3)
	    {
		return true;
	    }

	    if(roll.count(i) > 1)
	    {
		if(check)
		{
		    return true;
		}
		
		check = true;
	    }
	}

	return false;
    }

    YortStraight::YortStraight(int s)
    {
	start = s;
    }

    bool YortStraight::applyPoints(DiceRoll roll)
    {
	int l = 5;

	for(int i = start; i <= l; i++)
	{
	    if(roll.count(i) == 0)
	    {
		return false;
	    }
	}

	return true;
    }

    bool Yortzie::applyPoints(DiceRoll roll)
    {
	for(int i = 0; i <= roll.NUM_SIDES; i++)
	{
	    if(roll.count(i) > 1)
	    {
		return false;
	    }
	}

	return true;
    }
}
