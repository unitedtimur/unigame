#include "include/Matrix.h"
#include "ui_Matrix.h"

#include "include/Functions.h"
#include "include/GraphicScene.h"
#include "include/GraphicView.h"
#include "include/Configuration.h"

#include "include/levels/ILevel.h"
#include "include/levels/Level_Triangle_1.h"
#include "include/levels/Level_Triangle_2.h"
#include "include/levels/Level_Triangle_3.h"

#include "include/levels/Level_LengthAndDistance_1.h"
#include "include/levels/Level_LengthAndDistance_2.h"
#include "include/levels/Level_LengthAndDistance_3.h"

#include "include/graphicscell.h"
#include "include/levels/Level_Labirint_1.h"
#include "include/levels/Level_Labirint_2.h"
#include "include/levels/Level_Labirint_3.h"

#include "include/levels/Level_Parallelogram_1.h"
#include "include/levels/Level_Parallelogram_2.h"
#include "include/levels/Level_Parallelogram_3.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QComboBox>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QTableView>
#include <QTableWidget>
#include <QHeaderView>
#include <QTemporaryFile>
#include <QDir>
#include <QSettings>
#include <QSound>
#include <QVideoWidget>

Matrix::Matrix(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::Matrix),
    _scene(new GraphicScene),
    _view(new GraphicView),
    _level(nullptr),
    _audio(new QMediaPlayer),
    _playlist(new QMediaPlaylist),
    _startButton(new QPushButton(QObject::tr("Начать"), this)),
    _statisticButton(new QPushButton(QObject::tr("Статистика"), this)),
    _statistic(new QTableWidget)
{
    ui->setupUi(this);

    readSettings();

    setMouseTracking(true);

    // Устанавливаем стили
    _statistic->setStyleSheet("QTableWidget { "
                                            "color: #202225; "
                                            "background: #36393f; "
                                        "} "
                                        "QHeaderView { "
                                            "color: #8e9297; "
                                            "background-color: #36393f; "
                                            "font: 25px PerfoC; "
                                        "}");
    _startButton->setStyleSheet(Configuration::START_BUTTON_STYLE_SHEET);
    _statisticButton->setStyleSheet(_startButton->styleSheet());
    ui->hintLabel->setStyleSheet(this->ui->tooltip->styleSheet());
    ui->menuButton->setStyleSheet(_startButton->styleSheet());
    ui->levelLengthAndDistanceComboBox->setStyleSheet(ui->levelTianglesComboBox->styleSheet());
    ui->levelButton->setStyleSheet(_startButton->styleSheet());

    // Скрываем окно игры
    ui->centralwidget->hide();
    {
        this->_startButton->setGeometry(Configuration::WIDTH_MATRIX_WINDOW / 2 - 130,
                                        Configuration::HEIGHT_MATRIX_WINDOW / 2, 200, 50);
        this->_statisticButton->setGeometry(Configuration::WIDTH_MATRIX_WINDOW / 2 - 130,
                                            Configuration::HEIGHT_MATRIX_WINDOW / 2 + 80, 200, 50);

        connect(this->_startButton, &QPushButton::clicked, this, &Matrix::startGame);
        connect(this->_statisticButton, &QPushButton::clicked, this, &Matrix::showStatistic);
        connect(this->ui->menuButton, &QPushButton::clicked, this, &Matrix::toMenu);
    }

    // Инициализация статистики уровней
    loadStatistic();
    // Изменяем размер окна
    resize(Configuration::WIDTH_MAIN_WINDOW, Configuration::HEIGHT_MAIN_WINDOW);
    // Фиксируем размер окон
    setFixedSize(Configuration::WIDTH_MAIN_WINDOW, Configuration::HEIGHT_MAIN_WINDOW);
    _statistic->setFixedSize(Configuration::WIDTH_MAIN_WINDOW, Configuration::HEIGHT_MAIN_WINDOW / 2);
    // Устанавливаем имя окнам
    setWindowTitle(Configuration::PROJECT_NAME);
    _statistic->setWindowTitle(Configuration::PROJECT_NAME);
    // Устанавливаем иконку окнам
    setWindowIcon(QIcon(Configuration::UNIGAME));
    _statistic->setWindowIcon(QIcon(Configuration::UNIGAME));
    /*
         * Установим иконки для действий
         */
    ui->actionHowToPlay->setIcon(QIcon(Configuration::HOWTOPLAY));
    ui->actionAbout->setIcon(QIcon(Configuration::ABOUT));
    ui->actionExit->setIcon(QIcon(Configuration::EXIT));

    /*
         * Опции
         *	Как играть
         *	О создателе
         *	Выйти
         *
         * Статистика уровней
         *	Пройденные
         *	Очистить статистику
         */
    connect(this->ui->actionHowToPlay, &QAction::triggered, this, &Matrix::actionHowToPlay_triggered);
    connect(this->ui->actionAbout, &QAction::triggered, this, &Matrix::actionAbout_triggered);
    connect(this->ui->actionExit, &QAction::triggered, this, &Matrix::actionExit_triggered);
    connect(this->ui->actionLevelsStatistics, &QAction::triggered, this, &Matrix::showStatistic);
    connect(this->ui->actionClearStatistics, &QAction::triggered, this, &Matrix::clearStatistic);
    connect(this->ui->actionClearStatistics, &QAction::triggered, this, &Matrix::saveStatistic);

    // Устанавливаем сцену
    this->_view->setScene(this->_scene);

    QCoreApplication::instance()->installEventFilter(this);

    // Добавление GraphicView на viewLayout
    this->ui->viewLayout->addWidget(this->_view);

    // Фиксация размера окна ( запрет на изменение )
    this->setMinimumSize(QSize(Configuration::WIDTH_MATRIX_WINDOW,
                               Configuration::HEIGHT_MATRIX_WINDOW));
    this->setMaximumSize(QSize(Configuration::WIDTH_MATRIX_WINDOW,
                               Configuration::HEIGHT_MATRIX_WINDOW));

    this->_view->setMinimumSize(500, 400);
    this->_view->setMaximumSize(500, 400);

    // Запрет scroll'ов ( вертикального и горизонтального )
    this->_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->_view->setDragMode(QGraphicsView::RubberBandDrag);

    // Убираем нумерацию в _statistic
    this->_statistic->verticalHeader()->hide();

    // Фоновая музыка
    this->setMedia();

    // Скрытие вспомогательной кнопки для уровней
    this->ui->levelButton->hide();

    // Сигналы и слоты для выбора уровней
    connect(ui->levelTianglesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Matrix::chooseTriangleLevel);
    connect(ui->levelLengthAndDistanceComboBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Matrix::chooseLengthAndDistanceLevel);
    connect(ui->levelLabirintsComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Matrix::chooseLabirintLevel);
    connect(ui->levelParallelogramComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Matrix::chooseParallelogramLevel);
}

Matrix::~Matrix()
{
    saveSettings();
    this->saveStatistic();

    delete ui;
    delete _scene;
    delete _view;
    delete _level;
    delete _audio;
    delete _playlist;
    delete _statistic;
}

bool Matrix::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
        if (_level != nullptr)
            if (_level->checkLevel(watched, event)) {
                QSound::play(Configuration::LEVEL_WON);
                return true;
            }
    }

    return false;
}

void Matrix::saveSettings()
{
    QSettings settings(Configuration::ORGANIZATION);

    settings.beginGroup("Matrix");
    {
        settings.setValue("geometry", geometry());
    }
    settings.endGroup();
}

void Matrix::readSettings()
{
    QSettings settings(Configuration::ORGANIZATION);

    settings.beginGroup("Matrix");
    {
        const auto geometry = settings.value("geometry").toRect();
        setGeometry(geometry);
    }
    settings.endGroup();
}

void Matrix::drawMatrix6x6() const
{
    const auto width = _view->width();
    const auto height = _view->height();

    // Draw the matrix 6x6
    for (qint32 i = 0; i < 6; ++i)
    {
        _scene->addLine(qreal(i / 6.0) * width, 0, qreal(i / 6.0) * width, height);
        _scene->addLine(0, qreal(i / 6.0) * height, width, qreal(i / 6.0) * height);
    }
}

void Matrix::startGame()
{
    // Показываем окно игры
    this->ui->centralwidget->show();
    // Скрываем кнопки меню
    this->_startButton->hide();
    this->_statisticButton->hide();
    // Обновляем окно игры
    this->ui->levelTianglesComboBox->setCurrentIndex(0);
    this->ui->levelLengthAndDistanceComboBox->setCurrentIndex(0);
    this->ui->levelLabirintsComboBox->setCurrentIndex(0);
    this->ui->levelParallelogramComboBox->setCurrentIndex(0);
    this->clearGameWindow();
}

void Matrix::toMenu()
{
    // Скрываем окно игры
    this->ui->centralwidget->hide();
    // Показываем кнопки меню
    this->_startButton->show();
    this->_statisticButton->show();
}

void Matrix::loadStatistic()
{
    try
    {
        if (!QFile(QApplication::applicationDirPath() + Configuration::STATISTIC_PATH).exists())
        {
            QFile file(Configuration::STATISTIC_RESOURCE);
            {
                if (file.open(QIODevice::ReadOnly | QIODevice::Text))
                {
                    QFile fileTo(QApplication::applicationDirPath() + Configuration::STATISTIC_PATH);

                    if (fileTo.open(QIODevice::WriteOnly | QIODevice::Truncate))
                    {
                        fileTo.write(file.readAll());
                        fileTo.close();
                    }
                    else throw std::exception();

                    file.close();
                }
                else throw std::exception();
            }
        }

        QFile file(QApplication::applicationDirPath() + Configuration::STATISTIC_PATH);

        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            // Создаём поток для извлечения данных из файла
            QTextStream in(&file);
            in.setCodec("UTF-8");

            // Считываем данные до конца файла
            while (!in.atEnd()) {
                _statisticList.push_back(QString(in.readLine().toUtf8()).split(';'));
            }

            file.close();
        }
        else throw std::exception();
    }
    catch (const std::exception& /*ex*/)
    {
        QApplication::beep();
        QMessageBox::critical(this, Configuration::PROJECT_NAME, QString(Errors::LOAD_ERROR));
    }
}

void Matrix::saveStatistic()
{
    try
    {
        if (!QFile(QApplication::applicationDirPath() + Configuration::STATISTIC_PATH).exists())
            throw std::exception();

        QFile file(QApplication::applicationDirPath() + Configuration::STATISTIC_PATH);

        if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            QTextStream in(&file);
            in.setCodec("UTF-8");

            for (const auto& statistic : _statisticList)
                in << statistic.join(';') + '\n';

            file.close();
        }
        else throw std::exception();
    }
    catch (const std::exception& /*ex*/)
    {
        QApplication::beep();
        QMessageBox::critical(this, Configuration::PROJECT_NAME, QString(Errors::SAVE_ERROR));
    }
}

void Matrix::changeStatistic(const QStringList& statistic)
{
    for (qint32 i = 0; i < _statisticList.size(); ++i)
    {
        if (_statisticList[i][0] == statistic[0] && _statisticList[i][1] == statistic[1])
        {
            _statisticList[i][2] = statistic[2];
        }
    }
}

void Matrix::showStatistic()
{
    _statistic->setRowCount(_statisticList.size());
    _statistic->setColumnCount(3);
    _statistic->setHorizontalHeaderLabels(QStringList() << QObject::tr("Раздел") << QObject::tr("Уровень") << QObject::tr("Статус"));

    for (qint32 i = 0; i < _statisticList.size(); ++i)
    {
        _statistic->setItem(i, 0, new QTableWidgetItem(_statisticList[i][0]));
        _statistic->setItem(i, 1, new QTableWidgetItem(_statisticList[i][1]));
        _statistic->setItem(i, 2, new QTableWidgetItem(_statisticList[i][2]));

        _statistic->item(i, 0)->setBackground(Qt::yellow);
        _statistic->item(i, 1)->setBackground(Qt::yellow);
        _statistic->item(i, 2) && _statistic->item(i, 2)->text().size() > 0x07 ?
                    _statistic->item(i, 2)->setBackground(Qt::red) :
                    _statistic->item(i, 2)->setBackground(Qt::green);
    }

    _statistic->setGeometry(Configuration::WIDTH_MATRIX_WINDOW / 2 - 300, Configuration::HEIGHT_MATRIX_WINDOW / 2 - 300, 600, 200);
    _statistic->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _statistic->show();
}

void Matrix::clearStatistic()
{
    for (qint32 i = 0; i < _statisticList.size(); ++i)
    {
        _statisticList[i][2] = QObject::tr("Не пройден");
    }
}

void Matrix::actionHowToPlay_triggered()
{
    QMessageBox::information(this, QObject::tr("Как играть?"), QObject::tr("Если вы выполнили задание уровня, нажмите 'Space' на клавиатуре."));
}

void Matrix::actionExit_triggered()
{
    QCoreApplication::exit();
}

void Matrix::actionAbout_triggered()
{
    QMessageBox::about(this, QObject::tr("О создателе"), "<a href='https://unitedtimur.github.io'>by UnitedTimur (c)</a>");
}

void Matrix::actionLevelsStatistic_triggered()
{
    _statistic->setRowCount(_statisticList.size());
    _statistic->setColumnCount(3);
    _statistic->setHorizontalHeaderLabels(QStringList() << QObject::tr("Раздел") << QObject::tr("Уровень") << QObject::tr("Статус"));

    for (qint32 i = 0; i < _statisticList.size(); ++i)
    {
        _statistic->setItem(i, 0, new QTableWidgetItem(_statisticList[i][0]));
        _statistic->setItem(i, 1, new QTableWidgetItem(_statisticList[i][1]));
        _statistic->setItem(i, 2, new QTableWidgetItem(_statisticList[i][2]));
    }

    // TODO сделать статистику правильной ( не отображается статистка пройденных уровней )

    qint32 emptyCounter = 0;

    for (qint32 i = 0; i < _statistic->rowCount(); ++i)
    {
        for (qint32 j = 0; j < _statistic->columnCount(); ++j)
        {
            _statistic->item(i, j) == nullptr ? ++emptyCounter : --emptyCounter;
        }
    }

    _statistic->setGeometry(Configuration::WIDTH_MATRIX_WINDOW / 2 - 300, Configuration::HEIGHT_MATRIX_WINDOW / 2 - 300, 600, 200);
    _statistic->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _statistic->show();
}

void Matrix::actionClearStatistic_triggered()
{
}

void Matrix::initLevelsStatistic()
{

}

void Matrix::clearGameWindow()
{
    delete _level;
    _level = nullptr;

    // Очищаем сцену
    _scene->clear();
    _scene->clearFocus();

    // Очищаем окно описания уровня
    ui->tooltip->clear();

    // Очищаем окно подсказки уровня
    ui->hintLabel->clear();
}

void Matrix::chooseTriangleLevel(qint32 level)
{
    if (level < 0)
        return;

    switch (level)
    {
    // Первый уровень
    case 1:
        this->clearGameWindow();
        this->drawMatrix6x6();
        _level = new Level_Triangle_1(this, _view, _scene);
        ui->levelButton->hide();
        break;

        // Второй уровень
    case 2:
        this->clearGameWindow();
        this->drawMatrix6x6();
        _level = new Level_Triangle_2(this, _view, _scene);
        ui->levelButton->show();
        break;

        // Третий уровень
    case 3:
        this->clearGameWindow();
        this->drawMatrix6x6();
        _level = new Level_Triangle_3(this, _view, _scene);
        ui->levelButton->show();
        break;

        // Если не выбран уровень
    default:
        this->clearGameWindow();
        delete _level;
        _level = nullptr;
        ui->levelButton->hide();
        break;
    }

    _scene->setSceneRect(QRect(0, 0, _view->width(), _view->height()));
    _view->fitInView(_scene->sceneRect(), Qt::KeepAspectRatio);
}

void Matrix::chooseLengthAndDistanceLevel(qint32 level)
{
    if (level < 0)
        return;

    switch (level)
    {
    // Первый уровень
    case 1:
        this->clearGameWindow();
        this->drawMatrix6x6();
        _level = new Level_LengthAndDistance_1(this, _view, _scene);
        ui->levelButton->show();
        break;

        // Второй уровень
    case 2:
        this->clearGameWindow();
        this->drawMatrix6x6();
        _level = new Level_LengthAndDistance_2(this, _view, _scene);
        ui->levelButton->hide();
        break;

        // Третий уровень
    case 3:
        this->clearGameWindow();
        this->drawMatrix6x6();
        _level = new Level_LengthAndDistance_3(this, _view, _scene);
        ui->levelButton->hide();
        break;

        // Если не выбран уровень
    default:
        this->clearGameWindow();
        delete _level;
        _level = nullptr;
        ui->levelButton->hide();
        break;
    }

    _scene->setSceneRect(QRect(0, 0, _view->width(), _view->height()));
    _view->fitInView(_scene->sceneRect(), Qt::KeepAspectRatio);
}

void Matrix::chooseLabirintLevel(qint32 level)
{
    if (level < 0)
        return;

    switch (level) {
    case 1:
        this->clearGameWindow();
        _level = new Level_Labirint_1(this, _view, _scene);
        break;
    case 2:
        this->clearGameWindow();
        _level = new Level_Labirint_2(this, _view, _scene);
        break;
    case 3:
        this->clearGameWindow();
        _level = new Level_Labirint_3(this, _view, _scene);
        break;
    default:
        this->clearGameWindow();
        ui->levelButton->hide();
        break;
    }

    if (level >= 1 && level <= 2) {
        _scene->setSceneRect(QRect(0, 0, 6 * 30, 6 * 30));
    } else if (level == 3) {
        _scene->setSceneRect(QRect(0, 0, 20 * 30, 20 * 30));
    }

    _view->fitInView(_scene->sceneRect(), Qt::KeepAspectRatio);
}

void Matrix::chooseParallelogramLevel(qint32 level)
{
    if (level < 0)
        return;

    switch (level) {
    case 1:
        this->clearGameWindow();
        this->drawMatrix6x6();
        _level = new Level_Parallelogram_1(this, _view, _scene);
        ui->levelButton->show();
        break;
    case 2:
        this->clearGameWindow();
        this->drawMatrix6x6();
        _level = new Level_Parallelogram_2(this, _view, _scene);
        ui->levelButton->show();
        break;
    case 3:
        this->clearGameWindow();
        this->drawMatrix6x6();
        _level = new Level_Parallelogram_3(this, _view, _scene);
        ui->levelButton->show();
        break;
    default:
        this->clearGameWindow();
        ui->levelButton->hide();
        break;
    }

    _scene->setSceneRect(QRect(0, 0, _view->width(), _view->height()));
    _view->fitInView(_scene->sceneRect(), Qt::KeepAspectRatio);
}

void Matrix::paintPointOnGraphicView(QMouseEvent* event)
{
    double rad = 10;
    _scene->addEllipse(QRectF(event->x() - rad, event->y() - rad, rad * 2.0, rad * 2.0), QPen(),
                       QBrush(Qt::yellow));
}

void Matrix::mousePressEvent(QMouseEvent* event)
{
    QMainWindow::mousePressEvent(event);
}

void Matrix::setMedia()
{
    _playlist->addMedia(QUrl(Configuration::AUDIO_MATRIX));
    _playlist->setPlaybackMode(QMediaPlaylist::Loop);
    _audio->setPlaylist(_playlist);
    _audio->setVolume(5);
    _audio->setPlaybackRate(1.5);
    _audio->play();
}
