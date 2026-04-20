#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "schedulemanager.h"
#include "scheduleeditordialog.h"

void applyStyleSheet(QWidget* widget, const QString& path) {
    QFile file(path);
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        widget->setStyleSheet(styleSheet);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    applyStyleSheet(this, ":/style/style.qss");

    ui->cwCalender->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    QTextCharFormat saturdayFormat;
    saturdayFormat.setForeground(QColor("#007bff"));
    saturdayFormat.setFontWeight(QFont::Bold);
    ui->cwCalender->setWeekdayTextFormat(Qt::Saturday, saturdayFormat);

    QTextCharFormat sundayFormat;
    sundayFormat.setForeground(QColor("#dc3545"));
    sundayFormat.setFontWeight(QFont::Bold);
    ui->cwCalender->setWeekdayTextFormat(Qt::Sunday, sundayFormat);

    scheduleManager = new ScheduleManager(this);
    connect(scheduleManager, &ScheduleManager::schedulesChanged, this, &MainWindow::updateTable);

    scheduleManager->setStandardSchedules();
    scheduleManager->loadSchedules("schedules.json");

    ui->twScheduleList->verticalHeader()->setVisible(false);
    ui->twScheduleList->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->twScheduleList->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->twScheduleList->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    selectedDate = QDate::currentDate();
    updateTable();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_cwCalender_selectionChanged() {
    selectedDate = ui->cwCalender->selectedDate();
    updateTable();
}

void MainWindow::updateTable() {
    ui->twScheduleList->setRowCount(0);
    const QList<Schedule>& schedules = scheduleManager->getSchedulesForDate(selectedDate);
    QString timeFormat = "yyyy-MM-dd";

    for (int i = 0; i < schedules.size(); i++) {
        const Schedule &schedule = schedules[i];
        ui->twScheduleList->insertRow(i);

        qDebug() << schedule.getTitle() << " " << schedule.getStartTime() << " " << schedule.getEndTime();

        ui->twScheduleList->setItem(i, 0, new QTableWidgetItem(schedule.getTitle()));
        ui->twScheduleList->setItem(i, 1, new QTableWidgetItem(schedule.getStartTime().toString(timeFormat)));
        ui->twScheduleList->setItem(i, 2, new QTableWidgetItem(schedule.getEndTime().toString(timeFormat)));
    }
    qDebug() << selectedDate;
}

// void MainWindow::on_btnAdd_clicked() {
//     ScheduleEditorDialog dlg(this);

//     connect(&dlg, &ScheduleEditorDialog::scheduleSaved,
//             this, [this](const Schedule &s){
//                 scheduleManager.addSchedule(s);
//                 scheduleManager.saveSchedules("schedules.json");
//                 qDebug() << "시작 날짜:" << s.getStartTime().toString(Qt::ISODate);
//                 qDebug() << "끝 날짜:" << s.getEndTime().toString(Qt::ISODate);
//                 qDebug() << "저장 완료";
//             });

//     dlg.exec();
// }