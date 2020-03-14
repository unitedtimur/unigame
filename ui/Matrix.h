#ifndef MATRIX_H
#define MATRIX_H

#include <QMainWindow>

namespace Ui {
class Matrix;
}

class Matrix : public QMainWindow
{
    Q_OBJECT

public:
    explicit Matrix(QWidget *parent = nullptr);
    ~Matrix();

private:
    Ui::Matrix *ui;
};

#endif // MATRIX_H
