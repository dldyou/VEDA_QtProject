#include "scheduleeditordialog.h"
#include "ui_scheduleeditordialog.h"
#include "schedule.h"
#include "schedulemanager.h"

#include <QDateTime>

ScheduleEditorDialog::ScheduleEditorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScheduleEditorDialog){
    ui->setupUi(this);

    QDateTime now = QDateTime::currentDateTime();

    // 기본값 현재 날짜
    ui->dateedit1->setDate(now.date());
    ui->dateedit2->setDate(now.date());

    // 기본값 현재 시간
    ui->dateedit1->setTime(now.time());
    ui->dateedit2->setTime(now.time().addSecs(3600));
}

ScheduleEditorDialog::~ScheduleEditorDialog(){
    delete ui;
}

void ScheduleEditorDialog::on_btnSave_clicked()
{
    QString title = ui->lineeditTitle->text();
    QString content = ui->texteditContent->toPlainText();

    QDate startDate = ui->dateedit1->date();
    QDate endDate = ui->dateedit2->date();

    QTime startTime = QTime(9, 0);
    QTime endTime = QTime(10, 0);

    QDateTime startDateTime(startDate, startTime);
    QDateTime endDateTime(endDate, endTime);

    if (title.isEmpty()) {
        QMessageBox::warning(this, "경고", "제목을 입력하세요.");
        return;
    }

    Schedule schedule;
    schedule.setTitle(title);
    schedule.setDescription(content);
    schedule.setStartTime(startDateTime);
    schedule.setEndTime(endDateTime);

    emit scheduleSaved(schedule);

    accept();
}

void ScheduleEditorDialog::setDate(const QDate &date){
    ui->dateedit1->setDate(date);
    ui->dateedit2->setDate(date);
}

void ScheduleEditorDialog::on_btnCancel_clicked(){

    reject();  //창 닫기

}

