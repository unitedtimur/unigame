#ifndef UNIMAINWINDOW_H
#define UNIMAINWINDOW_H

#include <QMainWindow>

class StartMenu;

namespace Ui
{
	class UniMainWindow;
}

class UniMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit UniMainWindow(QWidget* parent = nullptr);
	~UniMainWindow();

public slots:
	void actionHowToPlay_triggered();
	void actionExit_triggered();
	void actionAbout_triggered();

private:
	Ui::UniMainWindow* ui;
	StartMenu* _startMenu;
};

#endif UNIMAINWINDOW_H