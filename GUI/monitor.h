#ifndef MONITOR_H
#define MONITOR_H

#include <QWidget>
#include "dataadapter.h"
#include "viewif.h"

namespace Ui {
class Monitor;
}

class Monitor : public ViewIf
{
  Q_OBJECT

public:
  explicit Monitor(DataAdapter *dataAdapter, eDataName dataName, QWidget *parent = nullptr);
  ~Monitor();
  void refresh() override;

private:
  Ui::Monitor *ui;
  DataAdapter *m_dataAdapter;
  eDataName m_dataName;
  static const char * m_titleNameList[];
  static const char * m_measureUnitNameList[];
};

#endif // MONITOR_H
