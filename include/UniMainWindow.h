#ifndef UNIMAINWINDOW_H
#define UNIMAINWINDOW_H

#include <QMainWindow>

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
};

#endif UNIMAINWINDOW_H