#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__


namespace cs427_527
{
   
    class YahtzeeGame;

    class YahtzeeFactory
    {
    public:
	virtual ~YahtzeeFactory() = default;
	virtual YahtzeeGame makeGame() const = 0;
    };

    class BasicYahtzeeFactory : public YahtzeeFactory
    {
    public:
	virtual YahtzeeGame makeGame() const;
    };

    class MysteryYahtzeeFactory : public YahtzeeFactory
    {
    public:
	virtual YahtzeeGame makeGame() const;
    };
}
#endif

