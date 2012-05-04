#ifndef WEBCOMMS_H
#define WEBCOMMS_H

#include <QtGui/QWidget>

class WebComms : public QWidget
{
    Q_OBJECT

public:
    WebComms(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~WebComms();

public slots:
    void sendGameJSON();
    void receiveGameJSON();
};

#endif // WEBCOMMS_H
