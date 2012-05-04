#include "wkwrap.h"

QtWkWrap::QtWkWrap(QWidget *parent)
    : QMainWindow(parent)
{   
    setupWkWrap();
}

QtWkWrap::~QtWkWrap()
{
}

void QtWkWrap::setupWkWrap()
{
    /**
      * Create the central widget
      * and set it.
      */
    QFrame* cW = new QFrame(this);
    setCentralWidget(cW);

    /**
      * Set the layout to central widget.
      */
    _layout = new QVBoxLayout(this);
    cW->setLayout(_layout);
    _layout->setMargin(0);
    _layout->setSpacing(0);

    openAct = new QAction(("&Open"), this);
    connect(openAct, SIGNAL(triggered()),this,SLOT(openGame()));
    saveAct = new QAction(("&Save"), this);
    connect(saveAct, SIGNAL(triggered()),this,SLOT(saveGame()));
    bar = menuBar()->addMenu("&File");
    bar->addAction(openAct);
    bar->addAction(saveAct);

    /**
      * Let's create the web view which
      * will be used to display our page.
      */
    _webView = new QWebView(this);
    _webView->setUrl(QUrl("qrc:///html/index.html"));
    connect(_webView->page()->mainFrame(),
            SIGNAL(javaScriptWindowObjectCleared()),
            this,
            SLOT(populateJavaScriptWindowObject()));
    //_webView->setEnabled();
    _webView->show();

    /** Add it to layout */
    _layout->addWidget(_webView);
}

void QtWkWrap::populateJavaScriptWindowObject()
{
    _webView->page()->mainFrame()->addToJavaScriptWindowObject("gameComms", this);
}

QString QtWkWrap::getGameJson()
{
    return QString("This came from the app");
}

void QtWkWrap::setGameJson(QString json)
{
    QMessageBox::warning(this, tr("Data from WebComms"),json);
}

void QtWkWrap::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton response;
    response = QMessageBox::warning(this, tr("Save before closing?"),
                   tr("Do you want to save your game?"),
                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (response == QMessageBox::Save) {
        saveGame();
        event->accept();
    }
    else if (response == QMessageBox::Discard) {
        event->accept();
    }
    else if (response == QMessageBox::Cancel) {
        event->ignore();
    }
 }

void QtWkWrap::openGame()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open a saved game"), "",
        tr("Game save file (*.sav)"));

    if (!fileName.isEmpty())
        loadGameFile(fileName);
}

bool QtWkWrap::saveGame()
{
    QString fileName = QFileDialog::getSaveFileName(this,
             tr("Save current game"), "",
             tr("Game save file (*.sav)"));

    if (fileName.isEmpty())
             return false;

    return saveGameFile(fileName);
}

bool QtWkWrap::saveGameFile(const QString &fileName)
 {
     QFile file(fileName);
     if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Application"),
                              tr("Cannot write file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return false;
     }

     QTextStream out(&file);
 #ifndef QT_NO_CURSOR
     QApplication::setOverrideCursor(Qt::WaitCursor);
 #endif
     out << "Save game data here";
 #ifndef QT_NO_CURSOR
     QApplication::restoreOverrideCursor();
 #endif

     //setCurrentFile(fileName);
     return true;
 }

void QtWkWrap::loadGameFile(const QString &fileName)
{
     QFile file(fileName);
     if (!file.open(QFile::ReadOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Application"),
                              tr("Cannot read file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return;
     }

     QTextStream in(&file);

 #ifndef QT_NO_CURSOR
     QApplication::setOverrideCursor(Qt::WaitCursor);
 #endif
     QString fileData = in.readAll();
 #ifndef QT_NO_CURSOR
     QApplication::restoreOverrideCursor();
 #endif

     //setCurrentFile(fileName);
 }
