#include "include/Configuration.h"
#include "include/Matrix.h"
#include "ui_Matrix.h"


#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>
#include <QMouseEvent>

Matrix::Matrix(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::Matrix),
	scene(new QGraphicsScene)
{
	ui->setupUi(this);

	this->setMinimumSize(QSize(Configuration::WIDTH_MATRIX_WINDOW, Configuration::HEIGHT_MATRIX_WINDOW));
	this->setMaximumSize(QSize(Configuration::WIDTH_MATRIX_WINDOW, Configuration::HEIGHT_MATRIX_WINDOW));

	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
}

Matrix::~Matrix()
{
	delete ui;
	delete scene;
}

void Matrix::paintEvent(QPaintEvent* event)
{
	this->drawMatrix6x6(event);


}

void Matrix::drawMatrix6x6(QPaintEvent* event) const
{
	scene->clear();

	qint32 width = ui->graphicsView->width();
	qint32 height = ui->graphicsView->height();
	
	for (qint32 i = 0; i < 6; ++i)
	{
		scene->addLine(qreal(i / 6.0) * width, 0, qreal(i / 6.0) * width, height);
		scene->addLine(0, qreal(i / 6.0) * height, width, qreal(i / 6.0) * height);
	}

	ui->graphicsView->setScene(scene);
}

void Matrix::mousePressEvent(QMouseEvent* event)
{
	qDebug() << event->pos();
}

void Matrix::mouseMoveEvent(QMouseEvent* event)
{
	qDebug() << event->pos();
}
