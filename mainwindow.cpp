#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "schedulemanager.h"
#include "scheduleeditordialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ScheduleManager scheduleManager;

    scheduleManager.setStandardSchedules();
    scheduleManager.loadSchedules("schedules.json");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_cwCalender_selectionChanged() {
    selectedDate = ui->cwCalender->selectedDate();
    qDebug() << selectedDate;
}
void MainWindow::on_btnAdd_clicked()
{
    ScheduleEditorDialog dlg(this);

    connect(&dlg, &ScheduleEditorDialog::scheduleSaved,
            this, [this](const Schedule &s){
                scheduleManager.addSchedule(s);
                scheduleManager.saveSchedules("schedules.json");
                qDebug() << "시작 날짜:" << s.getStartTime().toString(Qt::ISODate);
                qDebug() << "끝 날짜:" << s.getEndTime().toString(Qt::ISODate);
                qDebug() << "저장 완료";
            });

    dlg.exec();
}