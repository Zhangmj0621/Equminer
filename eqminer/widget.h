#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE



class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    QTextEdit* textEdit;


    //static QTextEdit* textEdit;

    static Widget* getwidget();
    static void logOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
