#ifndef QTWKWRAP_H
#define QTWKWRAP_H

#include <QtCore/QPointer>

#include <QtWebKit/QWebView>
#include <QtWebKit/QWebPage>
#include <QtWebKit/QWebFrame>

#include <QtGui/QWidget>
#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QFrame>
#include <QtGui/QVBoxLayout>

#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QAction>

#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

#include <QTextStream>
 #include <QCloseEvent>

class QtWkWrap : public QMainWindow
{
    Q_OBJECT

public:
    QtWkWrap(QWidget *parent = 0);
    ~QtWkWrap();

public slots:
    QString getGameJson();
    void setGameJson(QString json);

protected:
     void closeEvent(QCloseEvent *event);

private:
    QPointer<QWebView> _webView;
    QPointer<QVBoxLayout> _layout;

    QMenu *bar;
    QAction* openAct;
    QAction* saveAct;

    void setupWkWrap();
    void loadGameFile(const QString &fileName);
    bool saveGameFile(const QString &fileName);

private slots:
    void populateJavaScriptWindowObject();
    void openGame();
    bool saveGame();
};

#endif // QTWKWRAP_H
