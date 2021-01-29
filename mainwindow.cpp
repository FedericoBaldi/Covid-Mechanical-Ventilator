#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewif.h"

MainWindow::MainWindow(DataAdapter *dataAdapter, QList<ViewIf *> viewList, QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_dataAdapter(dataAdapter),
  m_viewList(viewList)
{
  ui->setupUi(this);
  for (int index = 0; index < m_viewList.size(); index++)
  {
    ui->ShowStackedWidget->addWidget(m_viewList.at(index));
  }
  ui->ShowStackedWidget->setCurrentIndex(1);

  bool connectionOk = QObject::connect(m_dataAdapter, SIGNAL(dataChanged()),
                                       this, SLOT(refresh()), Qt::QueuedConnection);
  assert(connectionOk);
}

MainWindow::~MainWindow()
{
  delete ui;
}

//By buttons we control the stacked widget current View.
void MainWindow::on_ButtonLeft_clicked()
{
  int currentIndex = ui->ShowStackedWidget->currentIndex();
  if (currentIndex != 1)
  {
    currentIndex--;
    ui->ShowStackedWidget->setCurrentIndex(currentIndex);
    ui->ShowStackedWidget->show();
  }
}

void MainWindow::on_ButtonRigth_clicked()
{
  int currentIndex = ui->ShowStackedWidget->currentIndex();
  if (currentIndex < m_viewList.size())
  {
    currentIndex++;
    ui->ShowStackedWidget->setCurrentIndex(currentIndex);
    ui->ShowStackedWidget->show();
  }
}

void MainWindow::refresh()
{
  m_viewList.at(ui->ShowStackedWidget->currentIndex()-1)->refresh();
}
