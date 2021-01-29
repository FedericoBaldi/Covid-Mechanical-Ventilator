#ifndef VIEWIF_H
#define VIEWIF_H

#include <QWidget>

class ViewIf : public QWidget
{
  Q_OBJECT
public:
  explicit ViewIf(QWidget *parent = nullptr);
  virtual void refresh() = 0;
};

#endif // VIEWIF_H
