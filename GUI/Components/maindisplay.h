#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QWidget>
#include "dataadapter.h"
#include "viewif.h"
#include "monitor.h"

namespace Ui {
class MainDisplay;
}

class MainDisplay : public ViewIf
{
  Q_OBJECT

public:
  explicit MainDisplay(DataAdapter *dataAdapater, QWidget *parent = nullptr);
  ~MainDisplay();
  void refresh() override;

private:
  Ui::MainDisplay *ui;
  DataAdapter *m_dataAdapter;
  QList <Monitor*> m_monitorsList;
};

#endif // MAINDISPLAY_H
