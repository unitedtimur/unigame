#include "include/Matrix.h"
#include "ui_Matrix.h"
#include "include/Configuration.h"
#include "include/GraphicScene.h"
#include "include/GraphicView.h"
#include "include/levels/ILevel.h"
#include "include/levels/Level_Triangle_1.h"
#include "include/levels/Level_Triangle_2.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QComboBox>
#include <QMessageBox>

Matrix::Matrix(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::Matrix),
	_scene(new GraphicScene),
	_view(new GraphicView),
	_level(nullptr),
	_audio(new QMediaPlayer),
	_playlist(new QMediaPlaylist)
{
	ui->setupUi(this);

	// Инициализация статистики уровней
	this->initLevelsStatistic();

	this->resize(Configuration::WIDTH_MAIN_WINDOW, Configuration::HEIGHT_MAIN_WINDOW);
	this->setFixedSize(Configuration::WIDTH_MAIN_WINDOW, Configuration::HEIGHT_MAIN_WINDOW);

	this->setWindowTitle("UniGame");
	this->setWindowIcon(QIcon(Configuration::UNIGAME));

	int screenHeight = this->height();
	int screenWidth = this->width();
	
	/*
	 * Установим иконки для действий
	 */
	ui->actionHowToPlay->setIcon(QIcon(Configuration::HOWTOPLAY));
	ui->actionAbout->setIcon(QIcon(Configuration::ABOUT));
	ui->actionExit->setIcon(QIcon(Configuration::EXIT));

	/*
	 * Опции
	 *	Как играть
	 *	О создателе
	 *	Выйти
	 *	
	 * Статистика уровней
	 *	Пройденные
	 *	Очистить статистику
	 */
	connect(ui->actionHowToPlay, &QAction::triggered, this, &Matrix::actionHowToPlay_triggered);
	connect(ui->actionAbout, &QAction::triggered, this, &Matrix::actionAbout_triggered);
	connect(ui->actionExit, &QAction::triggered, this, &Matrix::actionExit_triggered);
	connect(ui->actionLevelsStatistics, &QAction::triggered, this, &Matrix::actionLevelsStatistic_triggered);

	_view->setScene(_scene);

	QCoreApplication::instance()->installEventFilter(this);

	// Добавление GraphicView на viewLayout
	ui->viewLayout->addWidget(_view);

	// Фиксация размера окна ( запрет на изменение )
	this->setMinimumSize(QSize(Configuration::WIDTH_MATRIX_WINDOW, Configuration::HEIGHT_MATRIX_WINDOW));
	this->setMaximumSize(QSize(Configuration::WIDTH_MATRIX_WINDOW, Configuration::HEIGHT_MATRIX_WINDOW));

	_view->setMinimumSize(500, 400);
	_view->setMaximumSize(500, 400);

	// Запрет scroll'ов ( вертикального и горизонтального )
	_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_view->setDragMode(QGraphicsView::RubberBandDrag);

	// Фоновая музыка
	this->setMedia();

	// Выбираем уровень
	connect(ui->levelTianglesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Matrix::chooseLevel);
}

Matrix::~Matrix()
{
	delete ui;
	delete _scene;
	delete _view;
	delete _level;
	delete _audio;
	delete _playlist;
}

bool Matrix::eventFilter(QObject* watched, QEvent* event)
{
	if (event->type() == QEvent::KeyPress)
	{
		if (_level != nullptr)
			return _level->checkLevel(watched, event);
	}

	return false;
}

void Matrix::drawMatrix6x6() const
{
	const auto width = _view->width();
	const auto height = _view->height();

	for (qint32 i = 0; i < 6; ++i)
	{
		_scene->addLine(qreal(i / 6.0) * width, 0, qreal(i / 6.0) * width, height);
		_scene->addLine(0, qreal(i / 6.0) * height, width, qreal(i / 6.0) * height);
	}
}

void Matrix::actionHowToPlay_triggered()
{
	QMessageBox::information(this, QString::fromUtf8(u8"Как играть?"), QString::fromUtf8(u8"Если вы выполнили задание уровня, нажмите 'Space' на клавиатуре."));
}

void Matrix::actionExit_triggered()
{
	QCoreApplication::exit();
}

void Matrix::actionAbout_triggered()
{
	QMessageBox::about(this, QString::fromUtf8(u8"О создателе"), "<a href='https://lihomanov.me'>by UnitedTimur (c)</a>");
}

void Matrix::actionLevelsStatistic_triggered()
{
	QString res;

	for (auto it = _levelsStatistic.begin(); it != _levelsStatistic.end(); ++it)
		res += it.key() + ' ' + QString(it.value()).to + '\n';

	QMessageBox::information(this, QString::fromUtf8(u8"Пройденные уровни"), res);
}

void Matrix::actionClearStatistic_triggered()
{
}

void Matrix::initLevelsStatistic()
{
	_levelsStatistic.insert(QString::fromUtf8(u8"Треугольники уровень 1"), false);
	_levelsStatistic.insert(QString::fromUtf8(u8"Треугольники уровень 2"), false);
}

void Matrix::clearGameWindow()
{
	delete _level;
	_level = nullptr;

	// Очищаем сцену
	_scene->clear();

	// Очищаем окно описания уровня
	ui->tooltip->clear();

	// Очищаем окно подсказки уровня
	ui->hintLabel->clear();
}

void Matrix::chooseLevel(qint32 level)
{
	switch (level)
	{
		// Первый уровень
	case 1:
		this->clearGameWindow();
		this->drawMatrix6x6();
		_level = new Level_Triangle_1(this, _view, _scene);
		break;

		// Второй уровень
	case 2:
		this->clearGameWindow();
		this->drawMatrix6x6();
		_level = new Level_Triangle_2(this, _view, _scene);
		break;

		// Если не выбран уровень
	default:
		this->clearGameWindow();
		delete _level;
		_level = nullptr;
		break;
	}
}

void Matrix::paintPointOnGraphicView(QMouseEvent* event)
{
	qDebug() << event->pos();
	
	double rad = 10;
	_scene->addEllipse(QRectF(event->x() - rad, event->y() - rad, rad * 2.0, rad * 2.0), QPen(), QBrush(Qt::yellow));
}

void Matrix::mousePressEvent(QMouseEvent* event)
{

}

void Matrix::setMedia()
{
	_playlist->addMedia(QUrl(Configuration::AUDIO_MATRIX));
	_playlist->setPlaybackMode(QMediaPlaylist::Loop);
	_audio->setPlaylist(_playlist);
	_audio->setVolume(5);
	_audio->setPlaybackRate(1.5);
	_audio->play();
}
