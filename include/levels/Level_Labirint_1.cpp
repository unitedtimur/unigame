#include "Level_Labirint_1.h"
#include "include/Matrix.h"
#include "ui_Matrix.h"

#include "Point.h"
#include "include/GraphicView.h"
#include "include/GraphicScene.h"

#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <queue>
#include <QDebug>

Level_Labirint_1::Level_Labirint_1(Matrix *matrix, GraphicView *view, GraphicScene *scene) :
    _matrix(matrix),
    _view(view),
    _scene(scene)
{
    startLevel();

    _matrix->ui->levelButton->setText(QObject::tr("Сбросить попытку"));
    _matrix->ui->levelButton->show();

    algorithm();

    connect(_matrix->ui->levelButton, &QPushButton::clicked, this, &Level_Labirint_1::clearLevel);
    connect(_view, &GraphicView::mouseClicked, this, &Level_Labirint_1::check);
}

void Level_Labirint_1::paintLevel()
{
    _cells.resize(6);
    _rightPath.resize(6);
    _userTry.resize(6);

    for (qint32 y = 0; y < 6; ++y) {
        _cells[y].resize(6);
        _rightPath[y].resize(6);
        _userTry[y].resize(6);

        for (qint32 x = 0; x < 6; ++x) {
            _cells[y][x] = new GraphicsCell(GraphicsCell::Status::JustCell);
            _cells[y][x]->setRect(QRectF(x * 30,
                                         y * 30,
                                         30,
                                         30));
            _cells[y][x]->setX(x);
            _cells[y][x]->setY(y);

            _rightPath[y][x] = 0;
            _userTry[y][x] = 0;

            _scene->addItem(_cells[y][x]);
        }
    }

    _cells[0][0]->setStatus(GraphicsCell::Status::StartCell);
    _cells[5][5]->setStatus(GraphicsCell::Status::FinishCell);
}

void Level_Labirint_1::paintPoint(const QPoint &point)
{
    Q_UNUSED(point)
}

void Level_Labirint_1::clearLevel()
{
    startLevel();
    algorithm();
}

void Level_Labirint_1::showTooltip()
{
    _matrix->ui->tooltip->setText(QObject::tr("Постройте кратчайший путь в лабиринте"));
}

void Level_Labirint_1::showHint()
{

}

void Level_Labirint_1::startLevel()
{
    // Показываем задание
    showTooltip();

    // Отрисовываем уровень
    paintLevel();
}

bool Level_Labirint_1::checkLevel(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched)

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = dynamic_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_Space)
        {
            for (qint32 i = 0; i < _rightPath.size(); ++i) {
                for (qint32 j = 0; j < _rightPath[i].size(); ++j) {
                    if (_userTry[j][i] != _rightPath[j][i]) {
                        return false;
                    }
                }
            }

            // Пользователь прошёл уровень
            this->finishLevel();

            return true;
        }
    }

    return false;
}

void Level_Labirint_1::finishLevel()
{
}

void Level_Labirint_1::algorithm()
{
    const QVector<QVector<GraphicsCell*>> parse = _cells;

    std::queue<GraphicsCell *> cells;
    std::vector<std::vector<Point>> matrixPath(6, std::vector<Point>(6));

    qint32 cellY;
    qint32 cellX;

    // MatrixPath is store the coordinates by parent and his code number
    for (const auto& row : parse)
    {
        for (const auto& column : row)
        {
            if (column->getStatus() == GraphicsCell::Status::StartCell)
            {
                // The start cell
                cells.push(column);
            }
            else if (column->getStatus() == GraphicsCell::Status::BarrierCell)
            {
                // Set -1 in matrixPath where is barrier
                cellY = column->getY();
                cellX = column->getX();

                matrixPath[cellY][cellX] = Point(cellY, cellX, -1);
            }
        }
    }

    // Get the start cell coordinates
    cellY = cells.front()->getY();
    cellX = cells.front()->getX();

    // Set for start cell code number like 1
    matrixPath[cellY][cellX] = Point(cellY, cellX, 1);

    // Work while cells not is empty
    while (!cells.empty())
    {
        // Get the first elemnt in queue
        GraphicsCell* cell = cells.front();

        cellY = cell->getY();
        cellX = cell->getX();

        // Look at top
        if (cellY != 0 && matrixPath[cellY - 1][cellX].code == 0)
        {
            if (parse[cellY - 1][cellX]->getStatus() & GraphicsCell::Status::FinishCell)
            {
                break;
            }

            matrixPath[cellY - 1][cellX] = Point(cellY, cellX, matrixPath[cellY][cellX].code + 1);
            cells.push(parse[cellY - 1][cellX]);
        }

        // Look at bottom
        if (cellY != parse.size() - 1 && matrixPath[cellY + 1][cellX].code == 0)
        {
            if (parse[cellY + 1][cellX]->getStatus() & GraphicsCell::Status::FinishCell)
            {
                break;
            }

            matrixPath[cellY + 1][cellX] = Point(cellY, cellX, matrixPath[cellY][cellX].code + 1);
            cells.push(parse[cellY + 1][cellX]);
        }

        // Look at left
        if (cellX != 0 && matrixPath[cellY][cellX - 1].code == 0)
        {
            if (parse[cellY][cellX - 1]->getStatus() & GraphicsCell::Status::FinishCell)
            {
                break;
            }

            matrixPath[cellY][cellX - 1] = Point(cellY, cellX, matrixPath[cellY][cellX].code + 1);
            cells.push(parse[cellY][cellX - 1]);
        }

        // Look at right
        if (cellX != parse[0].size() - 1 && matrixPath[cellY][cellX + 1].code == 0)
        {
            if (parse[cellY][cellX + 1]->getStatus() & GraphicsCell::Status::FinishCell)
            {
                break;
            }

            matrixPath[cellY][cellX + 1] = Point(cellY, cellX, matrixPath[cellY][cellX].code + 1);
            cells.push(parse[cellY][cellX + 1]);
        }

        cells.pop();
    }

    // If not path from start cell to finish cell
    if (cells.empty())
    {
        qDebug() << "NO PATH";
        return;
    }

    cellX = cells.front()->getX();
    cellY = cells.front()->getY();

    // Get the code number finish cell
    qint32 currentNumber = matrixPath[cellY][cellX].code - 1;

    // Make the back path to start cell
    for (qint32 i = 0; i < currentNumber; ++i)
    {
        parse[cellY][cellX]->setStatus(GraphicsCell::Status::HPathCell);

        _rightPath[cellX][cellY] = 1;

        qint32 tempX = cellX;
        qint32 tempY = cellY;

        cellY = matrixPath[tempY][tempX].y;
        cellX = matrixPath[tempY][tempX].x;
    }
}

void Level_Labirint_1::check(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton)
    {
        GraphicsCell* rect = dynamic_cast<GraphicsCell*>(_view->itemAt(event->pos()));

        if (!rect)
            return;

        if (!(rect->getStatus() & GraphicsCell::BarrierCell)
                && !(rect->getStatus() & GraphicsCell::StartCell)
                && !(rect->getStatus() & GraphicsCell::FinishCell)) {
            rect->setStatus(GraphicsCell::PathCell);
            _userTry[rect->getX()][rect->getY()] = 1;
        }
    }
}
