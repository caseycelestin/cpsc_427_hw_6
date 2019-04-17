#ifndef __SCORESHEET_HPP__
#define __SCORESHEET_HPP__

#include <vector>
#include <string>
#include <utility>
#include <iostream>

using std::vector;
using std::string;
using std::pair;
using std::ostream;

namespace cs427_527
{
    class Rule;

    class Scoresheet
    {
    public:
	Scoresheet();

	Scoresheet(const vector<Rule>);

	vector<string> unusedCategories();

	void update(int, string, string);

	void used(string);

	void output(ostream& os) const;

	vector<int> getScores() const;

	int getTotal() const;

	bool isUsed(string) const;

    private:
	vector<pair<int, string>> score;
	
	vector<pair<bool, string>> unused;
    };
    
    ostream& operator<<(ostream& os, const Scoresheet& sheet);
}

#endif
