#include "scoresheet.hpp"

#include "rule.hpp"

#include <iomanip>

using std::make_pair;
using std::setw;
using std::endl;

namespace cs427_527
{
    Scoresheet::Scoresheet()
    {
    }
    
    Scoresheet::Scoresheet(const vector<Rule> ruleList)
    {
	vector<pair<int,string>> s;
	vector<pair<bool, string>> u;

	for (auto it = ruleList.begin(); it != ruleList.end(); it++)
	{
	    Rule add = *it;

	    if(add.isPlayable())
	    {
		s.push_back(make_pair(-1, add.getName()));
		u.push_back(make_pair(true, add.getAbbrev()));
	    }
	    else
	    {
		s.push_back(make_pair(0, add.getName()));
	    }
	}
	score = s;
	unused = u;
    }
    
    vector<string> Scoresheet::unusedCategories()
    {
	vector<string> out;
	for(auto it = unused.begin(); it < unused.end(); it++)
	{
	    pair<bool, string> t = *it;
	    if(t.first)
	    {
		out.push_back(t.second);
	    }
	}
	return out;
    }

    void Scoresheet::update(int value, string name, string abbrev)
    {
	for(auto it = score.begin(); it < score.end(); it++)
	{
	    pair<int, string> line = *it;

	    if(name == line.second)
	    {
		(*it).first = value;
	    }
	    
	    used(abbrev);
	}

    }

    void Scoresheet::used(string abbrev)
    {
	for(auto it = unused.begin(); it < unused.end(); it++)
	{
	    pair<bool, string> t = *it;
	    if(abbrev == t.second)
	    {
		(*it).first = false;
	    }
	}
    }

    void Scoresheet::output(ostream& os) const
    {
	for(auto it = score.begin(); it != score.end(); it++)
	{
	    pair<int, string> line = *it;

	    os << setw(4);

	    if(line.first != -1)
	    {
		os << line.first;
	    }
	    else
	    {
		os << "";
	    }

	    os << " " << line.second << endl;
	}
    }

    vector<int> Scoresheet::getScores() const
    {
	vector<int> out;

	for(auto it = score.begin(); it < score.end(); it++)
	{
	    out.push_back((*it).first);
	}
	return out;
    }

    int Scoresheet::getTotal() const
    {
	int total = 0;

	for(auto it = score.begin(); it < score.end() - 1; it++)
	{
	    int add = (*it).first;
	    if(add == -1)
	    {
		add = 0;
	    }
	    total += add;
	}

	return total;
    }

    bool Scoresheet::isUsed(string s) const
    {
	for(auto it = unused.begin(); it < unused.end(); it++)
	{
	    if((*it).second == s)
	    {
		return !((*it).first);
	    }
	}
	return true;
    }

    ostream& operator<<(ostream& os, const Scoresheet& sheet)
    {
	sheet.output(os);

	return os;
    }
}
