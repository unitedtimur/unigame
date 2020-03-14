#ifndef ILEVELS_H
#define ILEVELS_H

class ILevels
{
public:
	virtual ~ILevels() = default;
	virtual void paintLevel() = 0;
	virtual void clearLevel() = 0;
	virtual void showTooltip() = 0;

};

#endif // ILEVELS_H
