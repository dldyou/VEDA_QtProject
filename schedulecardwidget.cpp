#include "schedulecardwidget.h"
#include "ui_schedulecardwidget.h"
#include <QGraphicsDropShadowEffect>

ScheduleCardWidget::ScheduleCardWidget(const Schedule &schedule, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScheduleCardWidget)
{
    ui->setupUi(this);

    // 데이터 세팅
    ui->lblTitle->setText(schedule.getTitle());
    ui->lblTime->setText(schedule.getStartTime().toString("MM.dd") + "-" + schedule.getEndTime().toString("MM.dd"));
    ui->lblDesc->setText(schedule.getDescription());

    // 긴 내용에 '...' 처리 (elidedText 활용)
    QFontMetrics metrics(ui->lblDesc->font());
    QString elidedText = metrics.elidedText(schedule.getDescription(), Qt::ElideRight, 300); // 300px 기준
    ui->lblDesc->setText(elidedText);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(0, 0, 0, 15));
    shadow->setOffset(0, 4);

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setProperty("selected", false);
}

ScheduleCardWidget::~ScheduleCardWidget()
{
    delete ui;
}

void ScheduleCardWidget::setCardSelected(bool isSelected) {
    // 1. 위젯의 "selected" 속성값을 변경
    this->setProperty("selected", isSelected);

    // 2. 변경된 속성을 바탕으로 QSS 스타일을 강제로 다시 계산하여 적용
    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
}