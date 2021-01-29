#ifndef MAINDISPLAYCLONE_H
#define MAINDISPLAYCLONE_H

#include <QWidget>
#include "dataadapter.h"
#include "viewif.h"
#include "monitor.h"

namespace Ui {
class MainDisplayClone;
}

class MainDisplayClone : public ViewIf
{
  Q_OBJECT

public:
  explicit MainDisplayClone(DataAdapter *dataAdapater, QWidget *parent = nullptr);
  ~MainDisplayClone();
  void refresh() override;

private:
  Ui::MainDisplayClone *ui;
  DataAdapter *m_dataAdapter;
  QList <Monitor*> m_monitorsList;
};

#endif // MAINDISPLAYCLONE_H
