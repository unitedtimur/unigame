#include "Matrix.h"
#include "ui_Matrix.h"

Matrix::Matrix(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Matrix)
{
    ui->setupUi(this);
}

Matrix::~Matrix()
{
    delete ui;
}
