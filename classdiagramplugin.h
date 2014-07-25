#ifndef CLASSDIAGRAM_H
#define CLASSDIAGRAM_H

#include "classdiagram_global.h"

#include <extensionsystem/iplugin.h>

#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/project.h>

#include <classinfo.h>

#include <QTextEdit>

namespace ClassDiagram {
namespace Internal {

class ClassDiagramPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "ClassDiagram.json")

public:
    ClassDiagramPlugin();
    ~ClassDiagramPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private:
    ProjectExplorer::ProjectExplorerPlugin *pEPlugin;
    QList<ClassInfo> classInfo;
    void parseFile(QString fileName);
    void parseClass(QFile *file, QString currentLine);
    QTextEdit *outText;

private slots:
    void triggerAction();
};

} // namespace Internal
} // namespace ClassDiagram

#endif // CLASSDIAGRAM_H

