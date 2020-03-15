#include "include/Configuration.h"
#include "include/Matrix.h"
#include "include/LevelTriangles.h"
#include "include/GraphicScene.h"
#include "ui_Matrix.h"


#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

Matrix::Matrix(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::Matrix),
	scene(new GraphicScene),
	view(new GraphicView)
{
	ui->setupUi(this);

	this->setMinimumSize(QSize(Configuration::WIDTH_MATRIX_WINDOW, Configuration::HEIGHT_MATRIX_WINDOW));
	this->setMaximumSize(QSize(Configuration::WIDTH_MATRIX_WINDOW, Configuration::HEIGHT_MATRIX_WINDOW));

	ui->verticalLayout->addWidget(view);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setDragMode(QGraphicsView::RubberBandDrag);
	//ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

	connect(view, &GraphicView::mouseClicked, this, &Matrix::paintPointOnGraphicView);
}

Matrix::~Matrix()
{
	delete ui;
	delete scene;
	delete view;
}

void Matrix::paintEvent(QPaintEvent* event)
{
	this->drawMatrix6x6(event);
	startLevelTriangles();
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
	//LevelTriangles levelTriangles(new QPolygon({ QPoint(0, -40), QPoint(25, 40), QPoint(-25, 40) }), scene);

	
}

void Matrix::paintPointOnGraphicView(QMouseEvent* event)
{
	LevelTriangles levelTriangles(scene);
	levelTriangles.paintPoints(QPoint(event->pos().x(), event->pos().y()));
}

void Matrix::mousePressEvent(QMouseEvent* event)
{

}
