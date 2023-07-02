#ifndef READCSVFILE_H
#define READCSVFILE_H

#include <QWidget>

class readCsvFile
{
public:
    readCsvFile(const QString& fileName, QVector<double>& col1, QVector<double>& col3,  QVector<double>& col4);

    readCsvFile(const QString& fileName, QVector<double>& col1, QVector<double>& col2);
};

#endif // READCSVFILE_H
