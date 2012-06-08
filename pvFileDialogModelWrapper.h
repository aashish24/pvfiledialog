
#include <QModelIndex>
#include <QObject>

#include <string>

class pvFileDialogModelWrapper : public QObject
{
  Q_OBJECT

public:
  explicit pvFileDialogModelWrapper(QWidget *parent = 0);
  ~pvFileDialogModelWrapper();

  const char* getCurrentPath();
  void setCurrentPath(const char*);

  const char* absoluteFilePath(const char*);

  QStringList getFilePaths(const QModelIndex&);

  QAbstractItemModel* getModel();

  bool dirExists(const char *dir, const char *fullpath);


private:
  class pvFileDialogModelWrapperInternal;
  pvFileDialogModelWrapperInternal *Implementation;
};



