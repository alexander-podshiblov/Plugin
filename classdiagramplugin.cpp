#include "classdiagramplugin.h"
#include "classdiagramconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

#include <QtPlugin>

#include <QFile>
#include <QtDebug>

using namespace ClassDiagram::Internal;

ClassDiagramPlugin::ClassDiagramPlugin()
{
    // Create your members
    pEPlugin = ProjectExplorer::ProjectExplorerPlugin::instance();
/////////for debug
    outText = new QTextEdit(Core::ICore::instance()->mainWindow());
    outText->setGeometry(350,50, 700, 700);
}

ClassDiagramPlugin::~ClassDiagramPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool ClassDiagramPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    QAction *action = new QAction(tr("ClassDiagram action"), this);
    Core::Command *cmd = Core::ActionManager::registerAction(action, Constants::ACTION_ID,
                                                             Core::Context(Core::Constants::C_GLOBAL));
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
    connect(action, SIGNAL(triggered()), this, SLOT(triggerAction()));

    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
    menu->menu()->setTitle(tr("ClassDiagram"));
    menu->addAction(cmd);
    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

    return true;
}

void ClassDiagramPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag ClassDiagramPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void ClassDiagramPlugin::triggerAction()
{

    ///////////
    QStringList filesList = pEPlugin->currentProject()->files(ProjectExplorer::Project::ExcludeGeneratedFiles);

    for (int i = 0; i < filesList.count(); i++)
    {
        //if (filesList.at(i).indexOf(tr(".cpp")) == -1 && filesList.at(i).indexOf(tr(".h")) == -1)
        if (!filesList.at(i).contains(tr(".h")))
        {
            filesList.removeAt(i);
            i--;
        }
        else
            parseFile(filesList.at(i));

    }




    ///////////
}

void ClassDiagramPlugin::parseFile(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))
        return;

    while (!file.atEnd())
    {
        QString currentLine = tr(file.readLine());
        if (currentLine.contains(tr("class ")))
        {
            parseClass(&file, currentLine);
        }

    }

}

void ClassDiagramPlugin::parseClass(QFile *file, QString currentLine)
{
    ClassInfo *newClass = new ClassInfo();
    char accessInd = '+'; // '+' is public, '-' is private, '#' is protected
    char isSignalOrSlot = ' '; // ' ' is not signal or slot, '>' is signal, ']' is slot

    currentLine = currentLine.simplified();
    outText->insertPlainText(currentLine);



}

Q_EXPORT_PLUGIN2(ClassDiagram, ClassDiagramPlugin)

