#include "widget.h"
#include "./ui_widget.h"
#include "flatui.h"
#include "qdatetime.h"
#include <fstream>
#include <iostream>
#include <QFile>
#include <QByteArray>
#include <QString>
#include "readcsvfile.h"
#include "generatemesh.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->initForm();

    // 点击选取文件按钮，弹出文件对话框
    connect(ui->btn_1,&QPushButton::clicked,this,[=](){
        // 打开文件，并将文件信息返回给path
        QString path = QFileDialog::getOpenFileName(this,"打开文件","C:/Users/Zeem/Desktop");
        // 将路径放入到lineEdit中
        ui->txt1->setText(path);

        // 读取内容，并放入textEdit中
        // 实例化file对象，QFile默认支持的格式是utf-8，如果要读取gbk格式，需要加一些其他代码
        QFile file(path); // 参数为要读取文件的路径
        // 设置打开方式
        // https://doc.qt.io/qt-6/qiodevicebase.html#OpenModeFlag-enum
        file.open(QIODeviceBase::ReadOnly);
        // 直接读取所有数据
        // QByteArray array = file.read();
        // 读取一行数据
        QByteArray array = file.readLine();

        QVector<double> contact_normal_lm;
        QVector<double> x;
        QVector<double> y;
//        readCsvFile(path, data1, data2);
        readCsvFile read_csv(path, contact_normal_lm, x, y);

        // 将读取到的数据，放入textEdit中
        ui->txt2->setText(array);

        // 输出数组
        // 输出结果
//        qDebug() << "Col1:";
//        for (const auto& val : contact_normal_lm) {
//            qDebug() << val;
//        }

//        qDebug() << "Col3:";
//        for (const auto& val : x) {
//            qDebug() << val;
//        }
        QVector<double> distance = getDistances(x, y);


        // 绘图
        // create graph and assign data to it:
        ui->customPlot->addGraph();
        ui->customPlot->graph(0)->setData(distance, contact_normal_lm);
        // give the axes some labels:
        ui->customPlot->xAxis->setLabel("Distance along contact surface");
        ui->customPlot->yAxis->setLabel("Contact pressure");
        // set axes ranges, so we see all data:
        ui->customPlot->xAxis->setRange(0, 70);
        ui->customPlot->yAxis->setRange(0, 140000);
        ui->customPlot->replot();


        GenerateMesh mesh(this);
    });

//    plotContactStress();
}

Widget::~Widget()
{
    delete ui;
}

QVector<double> Widget::getDistances(const QVector<double> &x, const QVector<double> &y)
{
    int l = x.size();
    assert(l == y.size());

    QVector<double> dist(l, 0);
    double s = 0;

    for (int i = 1; i < l; i++) {
        s += sqrt(pow(x[i] - x[i-1], 2) + pow(y[i] - y[i-1], 2));
        dist[i] = s;
    }

    return dist;
}

void Widget::plotContactStress()
{


}

void Widget::initForm()
{
    ui->bar1->setRange(0, 100);
    ui->bar2->setRange(0, 100);
    ui->slider1->setRange(0, 100);
    ui->slider2->setRange(0, 100);

    connect(ui->slider1, SIGNAL(valueChanged(int)), ui->bar1, SLOT(setValue(int)));
    connect(ui->slider2, SIGNAL(valueChanged(int)), ui->bar2, SLOT(setValue(int)));
    ui->slider1->setValue(30);
    ui->slider2->setValue(30);

    this->setStyleSheet("*{outline:0px;}QWidget#frmFlatUI{background:#FFFFFF;}");

    FlatUI::setPushButtonQss(ui->btn_1);
    FlatUI::setPushButtonQss(ui->btn_2, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(ui->btn_3, 5, 8, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
    FlatUI::setPushButtonQss(ui->btn_4, 5, 8, "#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996");

    FlatUI::setLineEditQss(ui->txt1);
    FlatUI::setLineEditQss(ui->txt2, 5, 2, "#DCE4EC", "#1ABC9C");
    FlatUI::setLineEditQss(ui->txt3, 3, 1, "#DCE4EC", "#3498DB");
    FlatUI::setLineEditQss(ui->txt4, 3, 1, "#DCE4EC", "#E74C3C");

    FlatUI::setProgressQss(ui->bar1);
    FlatUI::setProgressQss(ui->bar2, 8, 5, 9, "#E8EDF2", "#1ABC9C");

    FlatUI::setSliderQss(ui->slider1);
    FlatUI::setSliderQss(ui->slider2, 10, "#E8EDF2", "#E74C3C", "#E74C3C");

    FlatUI::setRadioButtonQss(ui->rbtn1);
    FlatUI::setRadioButtonQss(ui->rbtn2, 8, "#D7DBDE", "#1ABC9C");
    FlatUI::setRadioButtonQss(ui->rbtn3, 8, "#D7DBDE", "#3498DB");
    FlatUI::setRadioButtonQss(ui->rbtn4, 8, "#D7DBDE", "#E74C3C");

    FlatUI::setScrollBarQss(ui->horizontalScrollBar);
    FlatUI::setScrollBarQss(ui->verticalScrollBar, 8, 120, 20, "#606060", "#34495E", "#1ABC9C", "#E74C3C");

    //设置列数和列宽
    int width = 1920;
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(0, width * 0.06);
    ui->tableWidget->setColumnWidth(1, width * 0.10);
    ui->tableWidget->setColumnWidth(2, width * 0.06);
    ui->tableWidget->setColumnWidth(3, width * 0.10);
    ui->tableWidget->setColumnWidth(4, width * 0.20);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;
    headText << "设备编号" << "设备名称" << "设备地址" << "告警内容" << "告警时间";
    ui->tableWidget->setHorizontalHeaderLabels(headText);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    //设置行高
    ui->tableWidget->setRowCount(300);

    for (int i = 0; i < 300; i++) {
        ui->tableWidget->setRowHeight(i, 24);
        QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString("测试设备%1").arg(i + 1));
        QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *itemContent = new QTableWidgetItem("防区告警");
        QTableWidgetItem *itemTime = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        ui->tableWidget->setItem(i, 0, itemDeviceID);
        ui->tableWidget->setItem(i, 1, itemDeviceName);
        ui->tableWidget->setItem(i, 2, itemDeviceAddr);
        ui->tableWidget->setItem(i, 3, itemContent);
        ui->tableWidget->setItem(i, 4, itemTime);
    }

//    // generate some data:
//    QVector<double> x(101), y(101); // initialize with entries 0..100
//    for (int i=0; i<101; ++i)
//    {
//        x[i] = i/50.0 - 1; // x goes from -1 to 1
//        y[i] = x[i]*x[i]; // let's plot a quadratic function
//    }
//    // create graph and assign data to it:
//    ui->customPlot->addGraph();
//    ui->customPlot->graph(0)->setData(x, y);
//    // give the axes some labels:
//    ui->customPlot->xAxis->setLabel("x");
//    ui->customPlot->yAxis->setLabel("y");
//    // set axes ranges, so we see all data:
//    ui->customPlot->xAxis->setRange(-1, 1);
//    ui->customPlot->yAxis->setRange(0, 1);
//    ui->customPlot->replot();

//    // add two new graphs and set their look:
//    ui->customPlot->addGraph();
//    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
//    ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
//    ui->customPlot->addGraph();
//    ui->customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph

////    ui->customPlot->graph(0)->setChannelFillGraph(ui->customPlot->graph(1)); // 在graph0和graph1之间进行通道填充
//    // generate some points of data (y0 for first, y1 for second graph):
//    QVector<double> x(251), y0(251), y1(251);
//    for (int i=0; i<251; ++i)
//    {
//        x[i] = i;
//        y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
//        y1[i] = qExp(-i/150.0);              // exponential envelope
//    }
//    // configure right and top axis to show ticks but no labels:
//    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
//    ui->customPlot->xAxis2->setVisible(true);
//    ui->customPlot->xAxis2->setTickLabels(false);
//    ui->customPlot->yAxis2->setVisible(true);
//    ui->customPlot->yAxis2->setTickLabels(false);
//    // make left and bottom axes always transfer their ranges to right and top axes:
//    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
//    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
//    // pass data points to graphs:
//    ui->customPlot->graph(0)->setData(x, y0);
//    ui->customPlot->graph(1)->setData(x, y1);
//    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
//    ui->customPlot->graph(0)->rescaleAxes();
//    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
//    ui->customPlot->graph(1)->rescaleAxes(true);
//    // Note: we could have also just called ui->customPlot->rescaleAxes(); instead
//    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
//    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}
