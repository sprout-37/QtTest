#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置字体
    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(13);
    a.setFont(font);


    Widget w;

    w.show();
    return a.exec();
}
