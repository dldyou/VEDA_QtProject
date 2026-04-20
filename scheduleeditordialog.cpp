#include "scheduleeditordialog.h"
#include "ui_scheduleeditordialog.h"
#include "schedule.h"

#include <QDateTime>

ScheduleEditorDialog::ScheduleEditorDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ScheduleEditorDialog) {
    ui->setupUi(this);

    QDateTime now = QDateTime::currentDateTime();

    // 기본값 현재 날짜
    ui->deStart->setDate(now.date());
    ui->deEnd->setDate(now.date());

    // 기본값 현재 시간
    ui->deStart->setTime(now.time());
    ui->deEnd->setTime(now.time().addSecs(3600));
}

ScheduleEditorDialog::~ScheduleEditorDialog() {
    delete ui;
}

void ScheduleEditorDialog::on_btnSave_clicked() {
    QString title = ui->leTitle->text();
    QString content = ui->teContent->toPlainText();

    // date, time 가져옴
    QDateTime startDateTime = ui->deStart->dateTime();
    QDateTime endDateTime   = ui->deEnd->dateTime();

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

void ScheduleEditorDialog::setDate(const QDate &date) {
    ui->deStart->setDate(date);
    ui->deEnd->setDate(date);
}

void ScheduleEditorDialog::setSchedule(const Schedule &schedule) {
    ui->leTitle->setText(schedule.getTitle());
    ui->teContent->setText(schedule.getDescription());

    ui->deStart->setDateTime(schedule.getStartTime());
    ui->deEnd->setDateTime(schedule.getEndTime());
}

void ScheduleEditorDialog::on_btnCancel_clicked() {
    reject();  // 그냥 창 닫기
}

