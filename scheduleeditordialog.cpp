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

    // date, time 가져옴
    QDateTime startDateTime = ui->dateedit1->dateTime();
    QDateTime endDateTime   = ui->dateedit2->dateTime();

    if (title.isEmpty()) {
        QMessageBox::warning(this, "경고", "제목을 입력하세요.");
        return;
    }

    // 시간 역전 방지
    if (startDateTime > endDateTime) {
        QMessageBox::warning(this, "경고", "종료 시간이 시작 시간보다 빠릅니다.");
        return;
    }

    Schedule schedule(title, content, startDateTime, endDateTime);

    emit scheduleSaved(schedule);
    accept();
}

void ScheduleEditorDialog::setDate(const QDate &date){
    ui->dateedit1->setDate(date);
    ui->dateedit2->setDate(date);
}

void ScheduleEditorDialog::setSchedule(const Schedule &schedule)
{
    ui->lineeditTitle->setText(schedule.getTitle());
    ui->texteditContent->setText(schedule.getDescription());

    ui->dateedit1->setDateTime(schedule.getStartTime());
    ui->dateedit2->setDateTime(schedule.getEndTime());
}

void ScheduleEditorDialog::on_btnCancel_clicked(){

    reject();  // 그냥 창 닫기

}

