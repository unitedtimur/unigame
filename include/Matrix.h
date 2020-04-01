#ifndef MATRIX_H
#define MATRIX_H

#include <QMainWindow>
#include <QMap>

class QGraphicsSceneMouseEvent;
class QMediaPlaylist;
class QMediaPlayer;
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

    void drawMatrix6x6() const;

    Q_SLOT void actionHowToPlay_triggered();
    Q_SLOT void actionExit_triggered();
    Q_SLOT void actionAbout_triggered();
    Q_SLOT void actionLevelsStatistic_triggered();
    Q_SLOT void actionClearStatistic_triggered();

protected:
    void initLevelsStatistic();
    void clearGameWindow();
    void setMedia();
	void mousePressEvent(QMouseEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event) override;
    
	Q_SLOT void chooseLevel(qint32 level);
    Q_SLOT void paintPointOnGraphicView(QMouseEvent* event);

public:
    Ui::Matrix*     ui;
    GraphicScene*   _scene;
    GraphicView*    _view;
    ILevel*         _level;
    QMediaPlayer*   _audio;
    QMediaPlaylist* _playlist;
    QMap<QString, bool> _levelsStatistic;
};

#endif // MATRIX_H
