#include <QMessageBox>

#include "include/UniMainWindow.h"
#include "include/Configuration.h"
#include "ui_UniMainWindow.h"

UniMainWindow::UniMainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::UniMainWindow)
{
	ui->setupUi(this);
	this->resize(Configuration::WIDTH_MAIN_WINDOW, Configuration::HEIGHT_MAIN_WINDOW);
	this->setFixedSize(Configuration::WIDTH_MAIN_WINDOW, Configuration::HEIGHT_MAIN_WINDOW);

	this->setWindowTitle("UniGame");
	this->setWindowIcon(QIcon(Configuration::UNIGAME));

	ui->actionHowToPlay->setIcon(QIcon(Configuration::HOWTOPLAY));
	ui->actionAbout->setIcon(QIcon(Configuration::ABOUT));
	ui->actionExit->setIcon(QIcon(Configuration::EXIT));

	connect(ui->actionHowToPlay, &QAction::triggered, this, &UniMainWindow::actionHowToPlay_triggered);
	connect(ui->actionAbout, &QAction::triggered, this, &UniMainWindow::actionAbout_triggered);
	connect(ui->actionExit, &QAction::triggered, this, &UniMainWindow::actionExit_triggered);
}

UniMainWindow::~UniMainWindow()
{
	delete ui;
}

void UniMainWindow::actionHowToPlay_triggered()
{
	QMessageBox::information(this, "How to play", "Press F to respect");
}

void UniMainWindow::actionExit_triggered()
{
	QCoreApplication::exit();
}

void UniMainWindow::actionAbout_triggered()
{
	QMessageBox::about(this, "About", "<a href='https://vk.com/unitedtimur'>by UnitedTimur (c)</a>");
}
