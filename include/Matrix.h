#ifndef MATRIX_H
#define MATRIX_H

#include <QMainWindow>

class QGraphicsSceneMouseEvent;
class GraphicScene;
class GraphicView;
class ILevel;

namespace Ui {
    class Matrix;
}

class Matrix : public QMainWindow
{
    Q_OBJECT

public:
    explicit Matrix(QWidget* parent = nullptr);
    ~Matrix();

    static Matrix* instance();

protected:
    void paintEvent(QPaintEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event) override;

public:
    void drawMatrix6x6(QPaintEvent* event) const;

    Q_SLOT void startLevelTriangles();
    Q_SLOT void paintPointOnGraphicView(QMouseEvent* event);

protected:
    void mousePressEvent(QMouseEvent* event) override;

public:
    Ui::Matrix*     ui;

    GraphicScene*   scene;
    GraphicView*    view;

    ILevel*         level;
};

#endif // MATRIX_H
