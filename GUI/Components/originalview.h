#pragma once

#include <QWidget>
#include "dataadapter.h"
#include "viewif.h"
#include "monitor.h"

namespace Ui {
class OriginalView;
}

class OriginalView : public ViewIf
{
  Q_OBJECT

public:
  explicit OriginalView(DataAdapter *dataAdapater, QWidget *parent = nullptr);
  ~OriginalView();
  void refresh() override;

private:
  Ui::OriginalView *ui;
  DataAdapter *m_dataAdapter;
  QList <Monitor*> m_monitorsList;
};

