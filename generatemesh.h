#ifndef GENERATEMESH_H
#define GENERATEMESH_H

#include <QWidget>

class GenerateMesh : public QWidget
{
    Q_OBJECT
public:
    explicit GenerateMesh(QWidget *parent = nullptr);
    void generateMesh();
signals:

};

#endif // GENERATEMESH_H
