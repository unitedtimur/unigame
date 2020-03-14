#include "include/StartMenu.h"
#include "ui_StartMenu.h"

StartMenu::StartMenu(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::StartMenu)
{
	ui->setupUi(this);
	ui->backButton->setVisible(false);

	connect(ui->backButton, &QPushButton::clicked, [&]()
	{
			this->showEverything();
			ui->backButton->setVisible(false);
	});

	/*
	 * Connects all level with buttons
	 */
	connect(ui->lengthAndDistanceLevelButton, &QPushButton::clicked, this, &StartMenu::hideEverything);
	connect(ui->parallelLevelButton, &QPushButton::clicked, this, &StartMenu::hideEverything);
}


StartMenu::~StartMenu()
{
	delete ui;
}

void StartMenu::hideEverything()
{
	ui->buttonsGroupBox->hide();
	ui->backButton->setVisible(true);
}

void StartMenu::showEverything()
{
	ui->buttonsGroupBox->show();
}
