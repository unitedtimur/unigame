#ifndef MATRIX_H
#define MATRIX_H

#include <QMainWindow>
#include "GraphicView.h"
#include "ILevel.h"

class QGraphicsSceneMouseEvent;

namespace Ui {
	class Matrix;
}

class GraphicScene;

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

    Q_SLOT void startLevelTriangles();
    Q_SLOT void paintPointOnGraphicView(QMouseEvent* event);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    Ui::Matrix*     ui;

    GraphicScene*   scene;
    GraphicView*    view;

    ILevel*         level;

    friend class LevelTriangles;
};

#endif // MATRIX_H
