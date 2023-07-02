#ifndef GENERATEMESH_H
#define GENERATEMESH_H

#include <QWidget>

class GenerateMesh : public QWidget
{
    Q_OBJECT
public:
    explicit GenerateMesh(QWidget *parent = nullptr);
    // 生成网格
    GenerateMesh(QVector<double> &x, QVector<double> &y);

    void generateMesh();
signals:
};

#endif // GENERATEMESH_H
