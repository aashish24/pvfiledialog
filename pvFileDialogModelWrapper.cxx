
#include "pvFileDialogModelWrapper.h"

#include "pqSessionFileDialogModel.h"

#include <vtkProcessModule.h>
#include <vtkSMSession.h>

#include <QDebug>
#include <QDialog>

class pvFileDialogModelWrapper::pvFileDialogModelWrapperInternal
{
  public:
    pvFileDialogModelWrapperInternal();
    ~pvFileDialogModelWrapperInternal();

//    pqFileDialog* FileDialog;
    QDialog *FileDialog;
    pqSessionFileDialogModel *FileDialogModel;
};


pvFileDialogModelWrapper::pvFileDialogModelWrapperInternal::pvFileDialogModelWrapperInternal()
{
  qDebug() << "Creating dialog";
// this->FileDialog = new pqFileDialog(0, 0);
  this->FileDialog = new QDialog();

  std::cerr << "vtkProcessModule::GetProcessModule() "
            << vtkProcessModule::GetProcessModule() << std::endl;

  vtkSMSession *activeSession = NULL;
  vtkProcessModule *processModule = vtkProcessModule::GetProcessModule();

  if(processModule)
    {
    activeSession =
      vtkSMSession::SafeDownCast(vtkProcessModule::GetProcessModule()->GetActiveSession());
    }

  this->FileDialogModel = new pqSessionFileDialogModel(activeSession);
}


pvFileDialogModelWrapper::pvFileDialogModelWrapperInternal::~pvFileDialogModelWrapperInternal()
{
}


pvFileDialogModelWrapper::pvFileDialogModelWrapper(QWidget *parent) :
  QObject(parent)
{
  this->Implementation = new pvFileDialogModelWrapperInternal();
}


pvFileDialogModelWrapper::~pvFileDialogModelWrapper()
{
}


QString pvFileDialogModelWrapper::getCurrentPath()
{
  return this->Implementation->FileDialogModel->getCurrentPath();
}


void pvFileDialogModelWrapper::setCurrentPath(QString path)
{
  this->Implementation->FileDialogModel->setCurrentPath(path);
}


QString pvFileDialogModelWrapper::absoluteFilePath(const QString &path)
{
 return this->Implementation->FileDialogModel->absoluteFilePath(path);
}


QStringList pvFileDialogModelWrapper::getFilePaths(const QModelIndex &mi)
{
  return this->Implementation->FileDialogModel->getFilePaths(mi);
}


QAbstractItemModel* pvFileDialogModelWrapper::getModel()
{
  return this->Implementation->FileDialogModel;
}


bool pvFileDialogModelWrapper::dirExists(const QString &dir, QString &fullpath)
{
  return this->Implementation->FileDialogModel->dirExists(dir, fullpath);
}

