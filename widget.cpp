#include "widget.h"
#include "./ui_widget.h"
#include "flatui.h"
#include <iostream>
#include <QFile>
#include <QByteArray>
#include <QString>
#include <QProcess>
#include "readcsvfile.h"
#include "generatemesh.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 设置窗口标题
    setWindowTitle("活塞销接触计算");

    // 初始qss样式
    this->initForm();

    // 点击选取网格控制点按钮，弹出文件对话框，并进行网格生成
    connect(ui->btn1, &QPushButton::clicked, this, [=]()
            {
                // 打开文件，并将文件信息返回给path
                QString path = QFileDialog::getOpenFileName(this, "导入型线控制点", "C:/Users/Zeem/Desktop");

                if (path.isEmpty())
                {
                    return;
                }

                //                // 将路径放入到lineEdit中
                //                ui->txt1->setText(path);

                //                // 读取内容，并放入textEdit中
                //                QFile file(path); // 参数为要读取文件的路径
                //                // 设置打开方式
                //                // https://doc.qt.io/qt-6/qiodevicebase.html#OpenModeFlag-enum
                //                file.open(QIODeviceBase::ReadOnly);
                //                // 直接读取所有数据
                //                // QByteArray array = file.read();
                //                // 读取一行数据
                //                QByteArray array = file.readLine();
                //                // 将读取到的数据，放入textEdit中
                //                ui->txt2->setText(array);

                // 定义两个vector数组，用于存放控制点坐标
                QVector<double> x;
                QVector<double> y;

                // 读取csv文件，获取控制点的x坐标和y坐标
                readCsvFile read_csv(path, x, y);

                // 生成网格
                GenerateMesh generateMesh(x, y);

                // 绘制压力分布
                //                plotContactStress(contact_normal_lm, x, y);

                //                for (int i = 0; i < x.size(); ++i) {
                //                    qDebug() << x[i];
                //                }

                //                file.close();
            });

    // 实例化网格对象
    this->mesh = new GenerateMesh(this);
    // 将按钮与产生网格相连接
    connect(ui->btn2, &QPushButton::clicked, this->mesh, &GenerateMesh::generateMesh);

    // 将程序与计算程序相连接
    QProcess *process = new QProcess(this);
    // connect the button with exe
    connect(ui->btn3, &QPushButton::clicked, this, [=]()
            {
                // Set program name and parameters
                QString program = "/home/meng/moose_install_test/contact0526/contact0526-opt";
                QStringList arguments;
                arguments << "-i"
                          << "/home/meng/projects/contact0306/problems/contact_test/2023_05_10_test/zhixian_no_fric.i";

                process->setProgram(program);
                process->setArguments(arguments);
                //            process->setReadChannel(QProcess::StandardOutput);

                QObject::connect(process, &QProcess::readyReadStandardOutput, [process]()
                                 {
                                     QByteArray data = process->readAllStandardOutput();
                                     QString output(data);
                                     qDebug().noquote() << output; // 令换行符等转义字符生效
                                 });

                process->start();

                //            process->waitForFinished();
            });

    // 点击选取文件按钮，弹出文件对话框，并进行图像绘制
    connect(ui->btn4, &QPushButton::clicked, this, [=]()
            {

                // 打开文件，并将文件信息返回给path
                QString path = QFileDialog::getOpenFileName(this,"选取结果文件","/home/meng/projects/contact0306/problems/contact_test/2023_05_10_test/");

                if (path.isEmpty()){
                    return;
                }

                // 将路径放入到lineEdit中
                ui->txt1->setText(path);

                // 读取内容，并放入textEdit中
                QFile file(path); // 参数为要读取文件的路径
                // 设置打开方式
                // https://doc.qt.io/qt-6/qiodevicebase.html#OpenModeFlag-enum
                file.open(QIODeviceBase::ReadOnly);
                // 直接读取所有数据
                // QByteArray array = file.read();
                // 读取一行数据
                QByteArray array = file.readLine();
                // 将读取到的数据，放入textEdit中
                ui->txt2->setText(array);

                // 定义个vector数组，用于存放绘图用的变量
                QVector<double> contact_normal_lm;
                QVector<double> x;
                QVector<double> y;


                // 读取csv文件
                readCsvFile read_csv(path, contact_normal_lm, x, y);
                // 绘制压力分布
                plotContactStress(contact_normal_lm, x, y);

                file.close(); });
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

    for (int i = 1; i < l; i++)
    {
        s += sqrt(pow(x[i] - x[i - 1], 2) + pow(y[i] - y[i - 1], 2));
        dist[i] = s;
    }

    return dist;
}

void Widget::plotContactStress(const QVector<double> &contact_normal_lm, const QVector<double> x, const QVector<double> &y)
{

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
}

void Widget::initForm()
{
    ui->bar1->setRange(0, 100);
    ui->bar2->setRange(0, 100);
    ui->slider1->setRange(0, 100);
    ui->slider2->setRange(0, 100);
    ui->btn1->setText("导入型线控制点并生成网格");
    ui->btn2->setText("生成默认网格");
    ui->btn3->setText("运行程序");
    ui->btn4->setText("查看结果");

    connect(ui->slider1, SIGNAL(valueChanged(int)), ui->bar1, SLOT(setValue(int)));
    connect(ui->slider2, SIGNAL(valueChanged(int)), ui->bar2, SLOT(setValue(int)));
    ui->slider1->setValue(30);
    ui->slider2->setValue(30);

    this->setStyleSheet("*{outline:0px;}QWidget#frmFlatUI{background:#FFFFFF;}");

    FlatUI::setPushButtonQss(ui->btn1);
    FlatUI::setPushButtonQss(ui->btn2, 5, 8, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(ui->btn3, 5, 8, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
    FlatUI::setPushButtonQss(ui->btn4, 5, 8, "#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996");

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

    //    // 设置列数和列宽
    //    int width = 1920;
    //    ui->tableWidget->setColumnCount(5);
    //    ui->tableWidget->setColumnWidth(0, width * 0.06);
    //    ui->tableWidget->setColumnWidth(1, width * 0.10);
    //    ui->tableWidget->setColumnWidth(2, width * 0.06);
    //    ui->tableWidget->setColumnWidth(3, width * 0.10);
    //    ui->tableWidget->setColumnWidth(4, width * 0.20);
    //    ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);

    //    QStringList headText;
    //    headText << "设备编号"
    //             << "设备名称"
    //             << "设备地址"
    //             << "告警内容"
    //             << "告警时间";
    //    ui->tableWidget->setHorizontalHeaderLabels(headText);
    //    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    //    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //    ui->tableWidget->setAlternatingRowColors(true);
    //    ui->tableWidget->verticalHeader()->setVisible(false);
    //    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    //    // 设置行高
    //    ui->tableWidget->setRowCount(300);

    //    for (int i = 0; i < 300; i++)
    //    {
    //        ui->tableWidget->setRowHeight(i, 24);
    //        QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(i + 1));
    //        QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString("测试设备%1").arg(i + 1));
    //        QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(i + 1));
    //        QTableWidgetItem *itemContent = new QTableWidgetItem("防区告警");
    //        QTableWidgetItem *itemTime = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    //        ui->tableWidget->setItem(i, 0, itemDeviceID);
    //        ui->tableWidget->setItem(i, 1, itemDeviceName);
    //        ui->tableWidget->setItem(i, 2, itemDeviceAddr);
    //        ui->tableWidget->setItem(i, 3, itemContent);
    //        ui->tableWidget->setItem(i, 4, itemTime);
    //    }
}
