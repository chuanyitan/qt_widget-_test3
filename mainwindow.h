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
private slots:
   // void on_btnAddTab_clicked();
    void removeSubTab(int index);
    void on_addtabbutton_clicked();
    void timeoutslot();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    int ColumnSize;
    int RowSize;
};

#endif // MAINWINDOW_H
