#pragma once

#include <QWidget>
#include "dataadapter.h"
#include "viewif.h"
#include "monitor.h"
#include "plotAxis/plotaxis.h"

namespace Ui {
class AlternativeView2;
}

class AlternativeView2 : public ViewIf
{
  Q_OBJECT

public:
  explicit AlternativeView2(DataAdapter *dataAdapater, QWidget *parent = nullptr);
  ~AlternativeView2();
  void refresh() override;

private:
  Ui::AlternativeView2 *ui;
  DataAdapter *m_dataAdapter;
  QList <Monitor*> m_monitorsList;
  PlotAxis * m_plotAxis;
};

