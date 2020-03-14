#ifndef ILEVEL_H
#define ILEVEL_H

class ILevel
{
public:
	virtual void paintLevel() = 0;
	virtual void clearLevel() = 0;
	virtual void showTooltip() = 0;

	ILevel& operator=(const ILevel&) = delete;

protected:
	virtual ~ILevel() = default;
};

#endif // ILEVEL_H
