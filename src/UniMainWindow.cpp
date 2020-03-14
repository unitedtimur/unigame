#include <QMessageBox>

#include "include/UniMainWindow.h"
#include "include/Configuration.h"
#include "include/StartMenu.h"

#include "ui_UniMainWindow.h"
#include <QVBoxLayout>

UniMainWindow::UniMainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::UniMainWindow),
	_startMenu(new StartMenu(this))
{
	ui->setupUi(this);
	this->resize(Configuration::WIDTH_MAIN_WINDOW, Configuration::HEIGHT_MAIN_WINDOW);
	this->setFixedSize(Configuration::WIDTH_MAIN_WINDOW, Configuration::HEIGHT_MAIN_WINDOW);

	this->setWindowTitle("UniGame");
	this->setWindowIcon(QIcon(Configuration::UNIGAME));

	int screenHeight = this->height();
	int screenWidth = this->width();

	ui->startButton->setGeometry(screenHeight / 2,
								 screenWidth / 2,
								 Configuration::WIDTH_MAIN_WINDOW / 10, 
								 Configuration::HEIGHT_MAIN_WINDOW / 10);

	/*
	 * Settings for StartMenu
	 */
	_startMenu->hideEverything();
	connect(ui->startButton, &QPushButton::clicked, _startMenu, &StartMenu::showEverything);

	/*
	 * Set Icons for Menu
	 */
	ui->actionHowToPlay->setIcon(QIcon(Configuration::HOWTOPLAY));
	ui->actionAbout->setIcon(QIcon(Configuration::ABOUT));
	ui->actionExit->setIcon(QIcon(Configuration::EXIT));

	/*
	 * Options 
	 *	How to play
	 *	About
	 *	Exit
	 */
	connect(ui->actionHowToPlay, &QAction::triggered, this, &UniMainWindow::actionHowToPlay_triggered);
	connect(ui->actionAbout, &QAction::triggered, this, &UniMainWindow::actionAbout_triggered);
	connect(ui->actionExit, &QAction::triggered, this, &UniMainWindow::actionExit_triggered);

	//connect(ui->startButton, &QPushButton::clicked, this, &UniMainWindow::hide);
	//connect(ui->startButton, &QPushButton::clicked, _startMenu, &QWidget::show);
	connect(ui->startButton, &QPushButton::clicked, [&]()
	{
			ui->startButton->hide();
			this->setCentralWidget(_startMenu);
			
	});
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
