#include "include/Matrix.h"
#include "ui_Matrix.h"
#include "include/Configuration.h"
#include "include/GraphicScene.h"
#include "include/GraphicView.h"
#include "include/levels/ILevel.h"
#include "include/levels/Level_Triangle_1.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>

Matrix::Matrix(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::Matrix),
	_scene(new GraphicScene),
	_view(new GraphicView),
	_level(nullptr),
	_audio(new QMediaPlayer)
{
	ui->setupUi(this);

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

	// Сигнал нажатия мыши на GraphicView и слот отрисовки точки
	//connect(view, &GraphicView::mouseClicked, this, &Matrix::paintPointOnGraphicView);

	//startLevelTriangles();

	// Музыка для уровней
	_audio->setMedia(QUrl(Configuration::AUDIO_MATRIX));
	//_audio->play();
}

Matrix::~Matrix()
{
	delete ui;
	delete _scene;
	delete _view;
	delete _level;
	delete _audio;
}

Matrix* Matrix::instance()
{
	static Matrix obj(nullptr);
	return &obj;
}

void Matrix::paintEvent(QPaintEvent* event)
{
	
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

void Matrix::drawMatrix6x6(QPaintEvent* event) const
{
	const auto width = _view->width();
	const auto height = _view->height();

	for (qint32 i = 0; i < 6; ++i)
	{
		_scene->addLine(qreal(i / 6.0) * width, 0, qreal(i / 6.0) * width, height);
		_scene->addLine(0, qreal(i / 6.0) * height, width, qreal(i / 6.0) * height);
	}

	_view->setScene(_scene);
}

void Matrix::chooseLevel()
{

}

void Matrix::startLevelTriangles()
{
	this->drawMatrix6x6(nullptr);

	_level = new Level_Triangle_1(this, _view, _scene);
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
	QMediaPlaylist playlist;

	playlist.addMedia(QUrl(Configuration::AUDIO_MATRIX));
	playlist.setCurrentIndex(1);

	_audio->setPlaylist(&playlist);
}
