#ifndef ILEVEL_H
#define ILEVEL_H

class ILevel
{
public:
	virtual ~ILevel() = default;
	virtual void paintLevel() = 0;
	virtual void clearLevel() = 0;
	virtual void showTooltip() = 0;
};

#endif // ILEVEL_H
