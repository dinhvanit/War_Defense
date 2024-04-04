#ifndef TIME_H
#define TIME_H


class time
{
public:
	time(float setTimeSMax, float setTimeSCurrent = 0);

	void countUp(float dT);
	void countDown(float dT);
	void resetToZero();
	void resetToMax();
	bool timeSIsZero();
	bool timeSIsGreaterThanOrEqualTo(float timeSCheck);


private:
	float timeSMax;
	float timeSCurrent;
};

#endif // TIME_H
