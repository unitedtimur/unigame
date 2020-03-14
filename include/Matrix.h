#ifndef MATRIX_H
#define MATRIX_H

#include <QMainWindow>

namespace Ui {
	class Matrix;
}

class QGraphicsScene;

class Matrix : public QMainWindow
{
    Q_OBJECT

public:
    explicit Matrix(QWidget *parent = nullptr);
    ~Matrix();


protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void drawMatrix6x6(QPaintEvent* event) const;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    Ui::Matrix *ui;

    QGraphicsScene* scene;

};

#endif // MATRIX_H
