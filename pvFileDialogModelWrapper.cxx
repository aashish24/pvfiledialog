
#include "pvFileDialogModelWrapper.h"

#include "pqSessionFileDialogModel.h"

#include <vtkProcessModule.h>
#include <vtkSMSession.h>

#include <QDebug>
#include <QDialog>

//-----------------------------------------------------------------------------
class pvFileDialogModelWrapper::pvFileDialogModelWrapperInternal
{
  public:
    pvFileDialogModelWrapperInternal();
    ~pvFileDialogModelWrapperInternal();

    QDialog *FileDialog;
    pqSessionFileDialogModel *FileDialogModel;
};

//-----------------------------------------------------------------------------
pvFileDialogModelWrapper::pvFileDialogModelWrapperInternal::pvFileDialogModelWrapperInternal()
{
  this->FileDialog = new QDialog();

  vtkSMSession *activeSession = NULL;
  vtkProcessModule *processModule = vtkProcessModule::GetProcessModule();

  if(processModule)
    {
    activeSession =
      vtkSMSession::SafeDownCast(vtkProcessModule::GetProcessModule()->GetSession());
    }

  qDebug() << "Active session: " << activeSession;

  this->FileDialogModel = new pqSessionFileDialogModel(activeSession);
  std::cout << this->FileDialogModel << std::endl;
}

//-----------------------------------------------------------------------------
pvFileDialogModelWrapper::pvFileDialogModelWrapperInternal::~pvFileDialogModelWrapperInternal()
{
}

//-----------------------------------------------------------------------------
pvFileDialogModelWrapper::pvFileDialogModelWrapper(QWidget *parent) :
  QObject(parent)
{
  this->Implementation = new pvFileDialogModelWrapperInternal();
}

//-----------------------------------------------------------------------------
pvFileDialogModelWrapper::~pvFileDialogModelWrapper()
{
}

//-----------------------------------------------------------------------------
const char* pvFileDialogModelWrapper::getCurrentPath()
{
  return this->Implementation->FileDialogModel->getCurrentPath().toStdString().c_str();
}

//-----------------------------------------------------------------------------
void pvFileDialogModelWrapper::setCurrentPath(const char* path)
{
  qDebug() << "Current path is: " << path;
  this->Implementation->FileDialogModel->setCurrentPath(QString(path));
}

//-----------------------------------------------------------------------------
const char* pvFileDialogModelWrapper::absoluteFilePath(const char *path)
{
  QString tmpPath = QString(path);
 return this->Implementation->FileDialogModel->absoluteFilePath(tmpPath).toStdString().c_str();
}

//-----------------------------------------------------------------------------
QStringList pvFileDialogModelWrapper::getFilePaths(const QModelIndex &mi)
{
  return this->Implementation->FileDialogModel->getFilePaths(mi);
}

//-----------------------------------------------------------------------------
QAbstractItemModel* pvFileDialogModelWrapper::getModel()
{
  return this->Implementation->FileDialogModel;
}

//-----------------------------------------------------------------------------
bool pvFileDialogModelWrapper::dirExists(const char* dir, const char* fullPath)
{
   QString tmpDir = QString(dir);
   QString tmpFullPath = QString(fullPath);
  return this->Implementation->FileDialogModel->dirExists(tmpDir, tmpFullPath);
}

//-----------------------------------------------------------------------------
QStringList pvFileDialogModelWrapper::buildFileGroup(const QString &filiename)
{
  return this->Implementation->FileDialogModel->buildFileGroup(filename);
}
