#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QDebug>
#include <QLabel>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTime>
#include <QCoreApplication>
#include <QProgressDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setWindowTitle("Tablewiget+...test");
    ui->tabWidget->addTab(new QTextEdit, "QTextEdit");
    ui->tabWidget->addTab(new QLabel("<h1><font color=blue>Hello!World!</font></h1>"),"QLabel");
    ui->tabWidget->addTab(new QPushButton("Push XD"), "QPushButton");//前面的为控件的类型（和控件的内容显示），后面为标签框的名字
    ui->tabWidget->addTab(new QTextEdit, "QTextEdit");
    qDebug()<<"in main "<<ui->tabWidget->count();
    ui->tabWidget->setTabsClosable(true);
    //connect(ui->tabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));
    connect(ui->tabWidget,&QTabWidget::tabCloseRequested,this,&MainWindow::removeSubTab) ;//关闭时，对应到的内容。

    //1)tableview的简单使用
   {//******************************************************************************tableview的简单使用
    //1、定义模型尺寸
    ColumnSize = 4;//列多少咧
    RowSize=10;//行多少行
    model = new QStandardItemModel;
    model->setColumnCount(ColumnSize);    //列
    model->setRowCount(RowSize);    //行

    //2、设置标题。即列名称
    model->setHeaderData(0,Qt::Horizontal,"ID");
    model->setHeaderData(1,Qt::Horizontal,"User");
    model->setHeaderData(2,Qt::Horizontal,"PassWd");

    //3、添加数据
    for(int j=0;j<RowSize;j++)//添加数据
    {
        QStandardItem *itemID = new QStandardItem(QString::number(j));//显示第一列内容
        model->setItem(j,0,itemID);
        QStandardItem *itemUser = new QStandardItem("author"+QString::number(j));//显示第二列内容
        model->setItem(j,1,itemUser);
        QStandardItem *itemPassWd = new QStandardItem("123456");//显示第三列内容
        model->setItem(j,2,itemPassWd);
    }

    //4、显示
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->hide();//隐藏最左边的排序的栏
    ui->tableView->setColumnWidth(0,30);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设为选中时为一整条，不用则是单个的选中
    //ui->tabWidget->setCurrentIndex(0);//显示为当前标签页
    }//***************************************************************************************************

    //2）tableWidget使用
    {//====================================================================================================
        //这里需要自己在ui中对tablewidget进行模板的编辑，然后在执行下面的格式定义，计入模板，显示数据


        QLabel *label = new QLabel();//定义控件
        label->setText("Tom");
        ui->tableWidget->setCellWidget(0,0,label);//对内容位置的排版 （行，列，要填进去的内容）0，表示第一列

        QComboBox *ComboBoxSex = new QComboBox();//多选的下拉框
        ComboBoxSex->addItem("Man");
        ComboBoxSex->addItem("Woman");
        ui->tableWidget->setCellWidget(0,1,ComboBoxSex);

        QDateTimeEdit *dateTimeEdit1 = new QDateTimeEdit();//显示可选的日期
        dateTimeEdit1->setDateTime(QDateTime::currentDateTime());//以当前系统的时间显示日期
        dateTimeEdit1->setDisplayFormat("dd/MM/yyyy");//显示的格式
        dateTimeEdit1->setCalendarPopup(true);//选择选择日期的方式，是直接以日期表显示选择还是，影藏这条语句一个个数字加
        ui->tableWidget->setCellWidget(0,2,dateTimeEdit1);

        QComboBox *ComboBoxWork1 = new QComboBox();
        ComboBoxWork1->addItem(tr("Worker"));
        ComboBoxWork1->addItem(tr("Farmer"));
        ComboBoxWork1->addItem(tr("Doctor"));
        ComboBoxWork1->addItem(tr("Lawyer"));
        ComboBoxWork1->addItem(tr("Solder"));
        ui->tableWidget->setCellWidget(0,3,ComboBoxWork1);

//        //4. 表格表头的显示与隐藏
//        ui->tableWidget->verticalHeader()->setVisible(false); //隐藏列表头
//        ui->tableWidget->horizontalHeader()->setVisible(false); //隐藏行表头//即最前面的排序的列那一行

//        //5. 对表头文字的字体、颜色进行设置

         QTableWidgetItem *columnHeaderItem0 = ui->tableWidget->horizontalHeaderItem(0); //获得水平方向表头的Item对象
         columnHeaderItem0->setFont(QFont("Helvetica")); //设置字体
         columnHeaderItem0->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色
         columnHeaderItem0->setTextColor(QColor(200,111,30)); //设置文字颜色

         QTableWidgetItem *columnHeaderItem2 = ui->tableWidget->horizontalHeaderItem(1); //获得水平方向表头的Item对象
         columnHeaderItem2->setFont(QFont("Helvetica")); //设置字体
         columnHeaderItem2->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色
         columnHeaderItem2->setTextColor(QColor(100,100,120)); //设置文字颜色

         QTableWidgetItem *columnHeaderItem3 = ui->tableWidget->verticalHeaderItem(1); //获得水平方向表头的Item对象
         columnHeaderItem3->setFont(QFont("Helvetica")); //设置字体
         columnHeaderItem3->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色
         columnHeaderItem3->setTextColor(QColor(200,111,30)); //设置文字颜色
//       // 3. 合并单元格效果的实现：

         ui->tableWidget->setSpan(4, 1, 2, 3);  // 其参数为： (从第几行开始，从第几列开始，把几行合并，把几列合并)要改变单元格的   1行数  2列数     要合并的  3行数  4列数
//       void QTableView::setSpan(int row, int column, int rowSpanCount, int columnSpanCount)；
//       // 5. 获得单击单元格的内容

//        //通过实现 itemClicked (QTableWdgetItem *) 信号的槽函数，就可以获得鼠标单击到的单元格指针，进而获得其中的文字信息
//         connect(ui->tableWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(getItem(QTreeWidgetItem*,int)));
        //将itemClicked信号与函数getItem绑定
//----------------------------------------------另外一种用法


//        ui->tableWidget->setColumnCount(3);//只设置列数，行数动态中增加
//        ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"篇名"<<"关键字"<<"简介");
//        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
//        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
//        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个

        int RowCont;
        RowCont=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(RowCont);//增加一行

//        //插入元素//插的内容暂且为字符串
        ui->tableWidget->setItem(RowCont,0,new QTableWidgetItem("tanyi"));
        ui->tableWidget->setItem(RowCont,1,new QTableWidgetItem("KeyWord"));
        ui->tableWidget->setItem(RowCont,2,new QTableWidgetItem("hello"));
        ui->tableWidget->setItem(RowCont,3,new QTableWidgetItem("hello world"));

//         //15.添加表头内容：======可用
//           方法一：
//           QStringList header;
//           header<<""<<tr("1")<<tr("2")<<tr("3")<<tr("4)<<tr("5");
//           方法二：
//          ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<tr("1")<<tr("2")<<tr("3")<<tr("4")<<tr("5"));
//        // 16.清除：
//           ui->tableWidget->clear();//清除所有可见数据（包括表头数据也清掉），行还在
//           ui->tableWidget->clearContents();//只清除表中数据，不清除表头内容



        ui->tabWidget->setCurrentIndex(1);//显示为当前标签页


    }//====================================================================================================

    //3、date 时间的使用
    {//-------------------------------------------------------------------------------------------------------
      QString date=QDate::currentDate().toString();
      QString time=QTime::currentTime().toString() ;
        ui->timeEdit->setDisplayFormat("hh:mm:ss");
        ui->dateEdit->setDisplayFormat("yyyy-MM-dd");
        ui->dateEdit->setCalendarPopup(true);
        ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");//显示的格式
        ui->dateTimeEdit->setDate(QDate::currentDate());
        ui->dateTimeEdit->setTime(QTime::currentTime());
        ui->lineEdit->setText(date+"  "+time );
        QTimer *timer=new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(timeoutslot()));//timeoutslot()Ϊ�Զ�����
        timer->start(1000);

        ui->tabWidget->setCurrentIndex(2);//显示为当前标签页
    }//-------------------------------------------------------------------------------------------------------

    //6.QGraphicsView 暂时也不知道干嘛的
    {//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        QGraphicsScene *scene = new QGraphicsScene;
        scene->setSceneRect(-300,-300,600,600);
        scene->setItemIndexMethod(QGraphicsScene::NoIndex);
        QPixmap pixmap(":/1.jpg");
        pixmap = pixmap.scaledToWidth(200);
        QGraphicsPixmapItem *item1 = scene->addPixmap(pixmap);

        ui->view->setScene(scene);
        ui->view->setRenderHint(QPainter::Antialiasing);
        ui->view->setCacheMode(QGraphicsView::CacheBackground);
        ui->view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        ui->view->setDragMode(QGraphicsView::ScrollHandDrag);
        ui->view->resize(400,300);
        ui->tabWidget->setCurrentIndex(3);//显示为当前标签页

    }//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     //7.progressDialog
    {//=============================================================================

        ui->tabWidget->setCurrentIndex(4);//显示为当前标签页
    }//==============================================================================
    //8.1数码管
    {//========================================
        //直接使用的ui中的信号连接
     ui->tabWidget->setCurrentIndex(5);//显示为当前标签页
    }//========================================

    //8.2数码管，代码实现
    {//========================================
        //直接使用的ui中的信号连接

     ui->tabWidget->setCurrentIndex(6);//显示为当前标签页
    }//========================================

    //9.日历按键显示和影藏
    {//========================================
        //直接使用的ui中的信号连接
     ui->calendarWidget->hide();
     ui->tabWidget->setCurrentIndex(7);//显示为当前标签页
    }//========================================
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeoutslot()//date 3/////
{
    //    QTime n(14, 0, 0);                // n == 14:00:00
    //     QTime t;
    //     t = n.addSecs(70);                // t == 14:01:10

        QDate date = ui->dateTimeEdit->date();
        QTime time = ui->dateTimeEdit->time();
        QTime time1(23,59,59);

        if(time == time1)
        {
            date = date.addDays(1);
        }
        time = time.addSecs(1);
        ui->dateTimeEdit->setDate(date);
        ui->dateTimeEdit->setTime(time);
        ui->timeEdit->setTime(time);
}


void MainWindow::removeSubTab(int index)
{
      ui->tabWidget->removeTab(index);
}

void MainWindow::on_addtabbutton_clicked()//增加标签页
{
    QTextEdit *edit=new QTextEdit;
    edit->setHtml("<h1><font color=red>Hello!World!</font></h1>");
    ui->tabWidget->addTab(edit,"New Tab");
    qDebug()<<"in click "<<ui->tabWidget->count();
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
   // ui->tabWidget->setCurrentIndex(1);//这里的count从0开始计数0显示第一个框，1显示第二个框。。。
   //显示当前即为count()-1
}



void MainWindow::on_btnProgressBar_clicked()//7.QProgressDialog基本模型
{
    int num=10;
    ui->progressBar->setRange(0,10);
    for(int i=1;i<=num;i++)
    {
        ui->progressBar->setValue(i);
        Delay_MSec(50);
        //sleep(1);
    }
}


void MainWindow::on_btnProgressDialog_clicked()//7.QProgressDialog，重生成模型
{
    int num=10;
    QProgressDialog *progressDialog = new QProgressDialog(this);
    QFont font("ZYSong18030",12);
    progressDialog->setFont(font);
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->setMinimumDuration(5);
    progressDialog->setWindowTitle("Please Waiting");
    progressDialog->setLabelText(tr("Copying..."));
    progressDialog->setCancelButtonText(tr("Cancel"));

    progressDialog->setRange(0,num);
    for(int i=1;i<=num;i++)
    {
        progressDialog->setValue(i);
        qApp->processEvents();//这里的事件怎么用？最后使用了延时进行代替
        Delay_MSec(1000);
        //sleep(1);
        if(progressDialog->wasCanceled())
            return;
    }
}

void MainWindow::Delay_MSec(unsigned int msec)//7.QProgressDialog，延时函数秒级，研究下
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    ui->lcdNumber_2->display(arg1);//该控件能设置的最大值为99，所以显示为99
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    ui->lcdNumber_2->display(QString::number(ui->lineEdit_2->text().toInt()));
}



void MainWindow::on_pushButton_clicked()
{
    ui->calendarWidget->show();
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    ui->dateEdit_2->setDate(ui->calendarWidget->selectedDate());
    ui->calendarWidget->hide();
}
