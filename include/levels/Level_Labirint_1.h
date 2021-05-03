#ifndef LEVEL_LABIRINT1_H
#define LEVEL_LABIRINT1_H

#include "ILevel.h"

class Matrix;
class GraphicView;
class GraphicScene;
class GraphicsCell;

struct Node
{
    qint32 g {0};
    qint32 h {0};
    qint32 f {0};
    qint32 posiition {0};

    bool operator==(qint32 position)
    {
        return this->posiition == position;
    }
};

class Level_Labirint_1 final : public ILevel
{
    Q_OBJECT

public:
    explicit Level_Labirint_1(Matrix* matrix, GraphicView* view, GraphicScene* scene);
    ~Level_Labirint_1() = default;

protected:
    void paintLevel() override;
    void paintPoint(const QPoint& point) override;
    void clearLevel() override;
    void showTooltip() override;
    void showHint() override;
    void startLevel() override;
    bool checkLevel(QObject* watched, QEvent* event) override;
    void finishLevel() override;
    void algorithm();

private:
    Matrix *_matrix;
    GraphicView *_view;
    GraphicScene *_scene;

    QVector<QVector<GraphicsCell *>> _cells;
    QVector<QVector<qint32>> _rightPath;
    QVector<QVector<qint32>> _userTry;
};

#endif // LEVEL_LABIRINT1_H
