#include "readcsvfile.h"
#include <QIODevice>
#include <QFile>

readCsvFile::readCsvFile(const QString& fileName, QVector<double>& col1, QVector<double>& col3,  QVector<double>& col4)
{
    // 打开CSV文件
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw std::runtime_error("Failed to open " + fileName.toStdString() + " for reading.");
    }

    QTextStream in(&file);


    // 读取文件并解析每行数据
    int lineCount = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        lineCount++;

        // 略去标题行
        if (lineCount == 1) {
            continue;
        }

        // 使用QStringList将每行数据分割成多个字段
        QStringList fields = line.split(',');

        if (fields.size() == 0)
        {
            continue;
        }

        // 将第一列的值添加到col1中
        col1.push_back(fields[0].toDouble());

        // 将第三列的值添加到col3中
        col3.push_back(fields[2].toDouble());

        // 将第四列的值添加到col4中
        col4.push_back(fields[3].toDouble());

    }

    file.close();
}
