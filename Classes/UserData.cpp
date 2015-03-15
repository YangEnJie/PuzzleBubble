#include "UserData.h"
#include <ctime>
static UserData* s_userData;

int GetTime();

UserData::~UserData()
{
	saveData();
	s_userData = nullptr;
}

UserData* UserData::getInstance()
{
	if (s_userData == nullptr)
	{
		s_userData = new UserData();
		s_userData->init();
	}
	return s_userData;
}

bool UserData::init()
{
	
	if (UserDefault::getInstance()->getBoolForKey("Beginner", true))
	{
		reset();
		_isBeginner = false;
		return true;
	}
	else
	{
		_score = 0;
		_level = 0;
		auto day = UserDefault::getInstance()->getIntegerForKey("Time", 0);
		if (day == GetTime())
		{
			_haveRaffle = UserDefault::getInstance()->getBoolForKey("HaveRaffle");
		}
		else
		{
			_haveRaffle = false;
			UserDefault::getInstance()->setIntegerForKey("Time", GetTime());
		}
		_bomb = UserDefault::getInstance()->getIntegerForKey("Bomb", 0);
		_colorBubble = UserDefault::getInstance()->getIntegerForKey("ColorBubble", 0);
		_hourglass = UserDefault::getInstance()->getIntegerForKey("Hourglass", 0);
		_gold = UserDefault::getInstance()->getIntegerForKey("Gold", 0);
		_bestScore = UserDefault::getInstance()->getIntegerForKey("BestScore", 0);
		_rebirth = UserDefault::getInstance()->getIntegerForKey("Rebirth", 0);
	}
	return true;
}

void UserData::reset()
{
	_bomb = 0;
	_colorBubble = 0;
	_gold = 0;
	_hourglass = 0;
	_isBeginner = true;
	_score = 0;
	_bestScore = 0;
	_raffle = true;
	_haveRaffle = false;
}
void UserData::saveData()
{
	UserDefault::getInstance()->setBoolForKey("Beginner", _isBeginner);
	UserDefault::getInstance()->setIntegerForKey("Bomb", _bomb);
	UserDefault::getInstance()->setIntegerForKey("ColorBubble", _colorBubble);
	UserDefault::getInstance()->setIntegerForKey("Hourglass", _hourglass);
	UserDefault::getInstance()->setIntegerForKey("Gold", _gold);
	UserDefault::getInstance()->setIntegerForKey("BestScore", _bestScore);
	UserDefault::getInstance()->setBoolForKey("HaveRaffle", _haveRaffle);
	UserDefault::getInstance()->setIntegerForKey("Rebirth", _rebirth);
	UserDefault::getInstance()->flush();
}
void UserData::addScore(int var)
{
	setScore(getScore() + var);
	if (getScore() > getBestScore())
	{
		setBestScore(getScore());
	}
	saveData();
}
int GetTime()
{
	time_t timep;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	time(&timep);
#else
	struct timeval now;
	gettimeofday(&now, NULL);
	timep = now.tv_sec;
#endif

	struct tm tm1;
	tm1.tm_year = 2015 - 1900;
	tm1.tm_mon = 3 - 1;
	tm1.tm_mday = 1;
	tm1.tm_hour = 0;
	tm1.tm_min = 0;
	tm1.tm_sec = 0;
	auto time = mktime(&tm1);

	double diff = difftime(timep, time);
	return (int)(diff / (3600 * 24));
}