#include "include/Matrix.h"
#include "include/Configuration.h"
#include "include/GraphicScene.h"
#include "include/GraphicView.h"
#include "ui_Matrix.h"


#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include "include/levels/ILevel.h"
#include "include/levels/Level_Triangle_1.h"

Matrix::Matrix(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::Matrix),
	scene(new GraphicScene),
	view(new GraphicView),
	level(nullptr)
{
	ui->setupUi(this);

	QCoreApplication::instance()->installEventFilter(this);

	// Добавление GraphicView на viewLayout
	ui->viewLayout->addWidget(view);

	// Фиксация размера окна ( запрет на изменение )
	this->setMinimumSize(QSize(Configuration::WIDTH_MATRIX_WINDOW, Configuration::HEIGHT_MATRIX_WINDOW));
	this->setMaximumSize(QSize(Configuration::WIDTH_MATRIX_WINDOW, Configuration::HEIGHT_MATRIX_WINDOW));

	view->setMinimumSize(500, 400);
	view->setMaximumSize(500, 400);

	// Запрет scroll'ов ( вертикального и горизонтального )
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setDragMode(QGraphicsView::RubberBandDrag);

	// Сигнал нажатия мыши на GraphicView и слот отрисовки точки
	//connect(view, &GraphicView::mouseClicked, this, &Matrix::paintPointOnGraphicView);

	startLevelTriangles();

}

Matrix::~Matrix()
{
	delete ui;
	delete scene;
	delete view;
	delete level;
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
		if (level != nullptr)
			return level->checkLevel(watched, event);
	}

	return false;
}

void Matrix::drawMatrix6x6(QPaintEvent* event) const
{
	const auto width = view->width();
	const auto height = view->height();

	for (qint32 i = 0; i < 6; ++i)
	{
		scene->addLine(qreal(i / 6.0) * width, 0, qreal(i / 6.0) * width, height);
		scene->addLine(0, qreal(i / 6.0) * height, width, qreal(i / 6.0) * height);
	}

	view->setScene(scene);
}

void Matrix::startLevelTriangles()
{
	this->drawMatrix6x6(nullptr);

	level = new Level_Triangle_1(this, view, scene);
}

void Matrix::paintPointOnGraphicView(QMouseEvent* event)		
{
	qDebug() << event->pos();
	
	double rad = 10;
	scene->addEllipse(QRectF(event->x() - rad, event->y() - rad, rad * 2.0, rad * 2.0), QPen(), QBrush(Qt::yellow));
}

void Matrix::mousePressEvent(QMouseEvent* event)
{

}
