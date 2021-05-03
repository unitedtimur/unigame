#ifndef MATRIX_H
#define MATRIX_H

#include <QMainWindow>
#include <QMap>

class QGraphicsSceneMouseEvent;
class QMediaPlaylist;
class QMediaPlayer;
class QTableWidget;
class GraphicScene;
class QPushButton;
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

    Q_SLOT void startGame();
    Q_SLOT void toMenu();
    Q_SLOT void loadStatistic();
    Q_SLOT void saveStatistic();
    Q_SLOT void changeStatistic(const QStringList& statistic);
    Q_SLOT void showStatistic();
    Q_SLOT void clearStatistic();
    Q_SLOT void actionHowToPlay_triggered();
    Q_SLOT void actionExit_triggered();
    Q_SLOT void actionAbout_triggered();
    Q_SLOT void actionLevelsStatistic_triggered();
    Q_SLOT void actionClearStatistic_triggered();

    Q_SIGNAL void scenePressed(QGraphicsSceneMouseEvent *event);

protected:
    void initLevelsStatistic();
    void clearGameWindow();
    void setMedia();
	void mousePressEvent(QMouseEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event) override;

    void saveSettings();
    void readSettings();
    
	Q_SLOT void chooseTriangleLevel(qint32 level);
    Q_SLOT void chooseLengthAndDistanceLevel(qint32 level);
    Q_SLOT void chooseLabirintLevel(qint32 level);
    Q_SLOT void paintPointOnGraphicView(QMouseEvent* event);

public:
    Ui::Matrix              *ui;
    GraphicScene            *_scene;
    GraphicView             *_view;
    ILevel                  *_level;
    QMediaPlayer            *_audio;
    QMediaPlaylist          *_playlist;
    QMap<QString, bool>     _levelsStatistic;
    QPushButton             *_startButton;
    QPushButton             *_statisticButton;
    QVector<QStringList>    _statisticList;
    QTableWidget            *_statistic;
};

#endif // MATRIX_H
