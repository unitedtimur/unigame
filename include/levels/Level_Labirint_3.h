#ifndef LEVEL_LABIRINT_3_H
#define LEVEL_LABIRINT_3_H

#include "ILevel.h"
#include "../graphicscell.h"

class Matrix;
class GraphicView;
class GraphicScene;
class QMouseEvent;

class Level_Labirint_3 final : public ILevel
{
    Q_OBJECT

public:
    explicit Level_Labirint_3(Matrix* matrix, GraphicView* view, GraphicScene* scene);
    ~Level_Labirint_3() = default;

protected:
    void algorithm();
    Q_SLOT void check(QMouseEvent *event);

public:
    void paintLevel();
    void paintPoint(const QPoint &point);
    void clearLevel();
    void showTooltip();
    void showHint();
    void startLevel();
    bool checkLevel(QObject *watched, QEvent *event);
    void finishLevel();

private:
    Matrix *_matrix;
    GraphicView *_view;
    GraphicScene *_scene;

    QVector<QVector<GraphicsCell *>> _cells;
    QVector<QVector<qint32>> _rightPath;
    QVector<QVector<qint32>> _userTry;
};

#endif // LEVEL_LABIRINT_3_H
