#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>

namespace Ui
{
	class StartMenu;
}

class StartMenu : public QWidget
{
	Q_OBJECT

public:
	explicit StartMenu(QWidget* parent = nullptr);
	~StartMenu();

private slots:
	void hideEverything();
	void showEverything();

private:
	Ui::StartMenu* ui;

	friend class UniMainWindow;
};

#endif STARTMENU_H