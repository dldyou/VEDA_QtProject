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
    connect(ui->leSearch, &QLineEdit::textChanged, this, &MainWindow::updateTable);

    scheduleManager->loadSchedules();

    ui->twScheduleList->verticalHeader()->setVisible(false);
    ui->twScheduleList->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->twScheduleList->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->twScheduleList->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    selectedDate = QDate::currentDate();
    ui->lblSelectedDate->setText(selectedDate.toString("yyyy-MM-dd"));
    updateTable();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_cwCalender_selectionChanged() {
    selectedDate = ui->cwCalender->selectedDate();
    ui->lblSelectedDate->setText(selectedDate.toString("yyyy-MM-dd"));
    updateTable();
}

void MainWindow::updateTable() {
    ui->twScheduleList->setRowCount(0);
    QString timeFormat = "yyyy-MM-dd";
    QString searchText = ui->leSearch->text();
    QList<Schedule> schedules;

    if (searchText.isEmpty()) {
        schedules = scheduleManager->getSchedulesForDate(selectedDate);
    }
    else {
        schedules = scheduleManager->getSchedulesByContainText(searchText);
    }


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

void MainWindow::on_btnAdd_clicked() {
    ScheduleEditorDialog dlg(this);
    // 날짜 전달
    dlg.setDate(selectedDate);

    connect(&dlg, &ScheduleEditorDialog::scheduleSaved,
            this, [this](const Schedule &s){
                scheduleManager->addSchedule(s);
                scheduleManager->saveSchedules();

                qDebug() << "시작 날짜:" << s.getStartTime().toString(Qt::ISODate);
                qDebug() << "끝 날짜:" << s.getEndTime().toString(Qt::ISODate);
                qDebug() << "저장 완료";
            });

    dlg.exec();
}

void MainWindow::on_btnEdit_clicked() {
    int row = ui->twScheduleList->currentRow();
    if (row < 0) return;

    QList<Schedule> list = scheduleManager->getSchedulesForDate(selectedDate);
    Schedule selected = list[row];

    ScheduleEditorDialog dlg(this);
    dlg.setSchedule(selected);

    connect(&dlg, &ScheduleEditorDialog::scheduleSaved,
            this, [this, selected](const Schedule &s){

                // 기존 데이터 찾아서 수정
                QList<Schedule> all = scheduleManager->getSchedules();

                for (int i = 0; i < all.size(); i++) {
                    if (all[i].getStartTime() == selected.getStartTime() &&
                        all[i].getTitle() == selected.getTitle()) {

                        scheduleManager->updateSchedule(i, s);
                        break;
                    }
                }

                scheduleManager->saveSchedules();
            });

    dlg.exec();
}

void MainWindow::on_btnRemove_clicked() {
    // 현재 선택된 테이블 행 인덱스 가져오기
    int row = ui->twScheduleList->currentRow();

    // 아무것도 선택되지 않았으면 종료
    if (row < 0) {
        QMessageBox::warning(this, "오류", "삭제할 항목을 선택해주세요.");
        return;
    }

    if (QMessageBox::question(this, "삭제", "정말 삭제하시겠습니까?")
        != QMessageBox::Yes) {
        return;
    }


    // 선택된 날짜 기준으로 일정 리스트 가져오기 (화면에 보이는 데이터)
    QList<Schedule> list = scheduleManager->getSchedulesForDate(selectedDate);

    // 선택된 row에 해당하는 Schedule 객체 추출
    Schedule selected = list[row];

    // 전체 일정 데이터 가져오기 (파일 기준 전체 데이터)
    QList<Schedule> all = scheduleManager->getSchedules();

    // 전체 데이터에서 동일한 일정 찾기
    for (int i = 0; i < all.size(); i++) {

        // startTime + title이 같은 항목을 삭제 대상으로 판단
        // (현재 구조에서는 사실상 "가짜 ID 역할")
        if (all[i].getStartTime() == selected.getStartTime() &&
            all[i].getTitle() == selected.getTitle()) {

            // 해당 일정 삭제
            scheduleManager->removeSchedule(i);

            // 첫 번째로 찾은 항목만 삭제하고 종료
            break;
        }
    }

    // 변경된 일정 데이터를 JSON 파일에 저장
    scheduleManager->saveSchedules();
}
