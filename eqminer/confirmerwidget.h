#ifndef CONFIRMERWIDGET_H
#define CONFIRMERWIDGET_H

#include <QWidget>

namespace Ui {
class ConfirmerWidget;
}

class ConfirmerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfirmerWidget(QWidget *parent = nullptr);
    ~ConfirmerWidget();

private:
    Ui::ConfirmerWidget *ui;
};

#endif // CONFIRMERWIDGET_H
