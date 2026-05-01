#include "view/RobotGridWidget.h"

#include <QCoreApplication>
#include <QDir>
#include <QGridLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QSizePolicy>

RobotGridWidget::RobotGridWidget(QWidget* parent)
    : QWidget(parent) {

    QString appDir = QCoreApplication::applicationDirPath();
    QString iconPath = QDir(appDir).filePath("../assets/robot-icon.png");

    robotIcon.load(iconPath);

    setFixedSize(250, 250);

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    for (int row = 0; row < gridSize; row++) {
        gridLayout->setRowStretch(row, 1);

        for (int column = 0; column < gridSize; column++) {
            gridLayout->setColumnStretch(column, 1);

            QLabel* cell = new QLabel(this);
            cell->setMinimumSize(50, 50);
            cell->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            cell->setAlignment(Qt::AlignCenter);
            cell->setScaledContents(false);
            cell->setStyleSheet("border: 1px solid gray;");

            cells[row][column] = cell;
            gridLayout->addWidget(cell, row, column);
        }
    }

    updateRobotIcon();
}

void RobotGridWidget::setRobotPosition(int newX, int newY) {
    x = newX;
    y = newY;
    updateRobotIcon();
}

void RobotGridWidget::updateRobotIcon() {
    for (int row = 0; row < gridSize; row++) {
        for (int column = 0; column < gridSize; column++) {
            cells[row][column]->clear();
        }
    }

    QLabel* robotCell = cells[y][x];

    if (!robotIcon.isNull()) {
        robotCell->setPixmap(robotIcon.scaled(
            robotCell->contentsRect().size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation));
    }
}

void RobotGridWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    updateRobotIcon();
}
