// Define the SIP wrapper to the hello library.

%Module pvFileDialogModelWrapper

%Import QtGui/QtGuimod.sip

class pvFileDialogModelWrapper : QObject {

%TypeHeaderCode
#include <pvFileDialogModelWrapper.h>
%End

public:
    pvFileDialogModelWrapper(QWidget *parent /TransferThis/ = 0);

    QString getCurrentPath();
    void setCurrentPath(QString);

    QAbstractItemModel* getModel();

    QString absoluteFilePath(const QString&);
    QStringList getFilePaths(const QModelIndex&);

    bool dirExists(const QString &dir, QString &fullpath);

private:
    pvFileDialogModelWrapper(const pvFileDialogModelWrapper &);
};

