#ifndef MATRIX_H
#define MATRIX_H

#include <QMainWindow>

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

protected:
    void drawMatrix6x6() const;
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
};

#endif // MATRIX_H
