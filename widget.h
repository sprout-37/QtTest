#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>
#include "generatemesh.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QVector<double> getDistances(const QVector<double> &x, const QVector<double> &y);
    void plotContactStress(const QVector<double> &contact_normal_lm, const QVector<double> x, const QVector<double> &y);
    GenerateMesh * mesh;


private slots:
    // 初始化样式函数
    void initForm();
};
#endif // WIDGET_H
