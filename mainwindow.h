#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dataadapter.h"
#include "viewif.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DataAdapter *dataAdapter, QList<ViewIf *> viewList, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ButtonLeft_clicked();
    void on_ButtonRigth_clicked();
    void refresh();

private:
    Ui::MainWindow *ui;
    DataAdapter *m_dataAdapter;
    QList<ViewIf *> m_viewList;
};
#endif // MAINWINDOW_H
