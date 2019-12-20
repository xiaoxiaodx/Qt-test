#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mbr_info.h"
#include <QTreeWidgetItem>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addPartitionView();
    void addFileView(QTreeWidgetItem *parent,Fat_fileItem *fileinfo);

public slots:
    void OnTreeItemDoubleClick(QTreeWidgetItem *,int num);
    void OnTreeItemClick(QTreeWidgetItem *,int num);

private:
    Ui::MainWindow *ui;

    MBR_info *mbr;




};

#endif // MAINWINDOW_H
