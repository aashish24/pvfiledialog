
#include <QModelIndex>
#include <QObject>

class pvFileDialogModelWrapper : public QObject
{
  Q_OBJECT

public:
  explicit pvFileDialogModelWrapper(QWidget *parent = 0);
  ~pvFileDialogModelWrapper();

  QString getCurrentPath();
  void setCurrentPath(QString);

  QString absoluteFilePath(const QString&);

  QStringList getFilePaths(const QModelIndex&);

  QAbstractItemModel* getModel();

  bool dirExists(const QString &dir, QString &fullpath);


private:
  class pvFileDialogModelWrapperInternal;
  pvFileDialogModelWrapperInternal *Implementation;
};



