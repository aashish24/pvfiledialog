// Define the SIP wrapper for pvFileDialogModel

%Module pvFileDialogModelWrapper

%Import QtGui/QtGuimod.sip
%Import QtCore/QtCoremod.sip

class pvFileDialogModelWrapper : QObject {

%TypeHeaderCode
#include <pvFileDialogModelWrapper.h>
%End

public:
    pvFileDialogModelWrapper(QWidget *parent /TransferThis/ = 0);

    const char* getCurrentPath();
    void setCurrentPath(const char*);

    QAbstractItemModel* getModel();

    const char* absoluteFilePath(const char *);
    QStringList getFilePaths(const QModelIndex&);

    bool dirExists(const char *dir, const char *fullpath);

private:
    pvFileDialogModelWrapper(const pvFileDialogModelWrapper &);
};

