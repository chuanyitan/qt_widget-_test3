#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Delay_MSec(unsigned int msec);
private slots:
   // void on_btnAddTab_clicked();
    void removeSubTab(int index);
    void on_addtabbutton_clicked();
    void timeoutslot();

    void on_btnProgressBar_clicked();

    void on_btnProgressDialog_clicked();

    void on_spinBox_2_valueChanged(int arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);


    void on_pushButton_clicked();

    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    int ColumnSize;
    int RowSize;
};

#endif // MAINWINDOW_H
