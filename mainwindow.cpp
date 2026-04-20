#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "schedulemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ScheduleManager scheduleManager;

    scheduleManager.loadSchedules("schedules.json");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_cwCalender_selectionChanged() {
    selectedDate = ui->cwCalender->selectedDate();
    qDebug() << selectedDate;
}