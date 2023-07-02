#ifndef COMPUTECONTACTSTRESS_H
#define COMPUTECONTACTSTRESS_H

#include <QWidget>

class ComputeContactStress : public QWidget
{
    Q_OBJECT
public:
    explicit ComputeContactStress(QWidget *parent = nullptr);
    void computeContactStress();

signals:
};

#endif // COMPUTECONTACTSTRESS_H
