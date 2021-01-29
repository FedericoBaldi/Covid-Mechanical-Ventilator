#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <QObject>
#include <QThread>
#include "datahandler.h"
#include "dataadapter.h"
#include "mainwindow.h"
#include "viewif.h"

class Initializer : public QObject
{
    Q_OBJECT
public:
    explicit Initializer(QObject *parent = nullptr);
    ~ Initializer();
    void start();
private:
    QThread m_handlerThread;
    DataHandler *m_dataHandler;
    DataAdapter *m_dataAdapater;
    MainWindow *m_mainWindow;
    QList<ViewIf *> m_viewList;

signals:
    void dataHandlerSetUp_signal();
};

#endif // INITIALIZER_H
