/**
**    Hatchit Editor
**    Copyright(c) 2015 Third-Degree
**
**    GNU General Public License
**    This file may be used under the terms of
**    the GNU General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.GPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU General Public License requirements
**    will be met: https://www.gnu.org/licenses/gpl.html
**
**/

#include <ht_editor_about.h>
#include <ht_editor_version.h>
#include <ht_os.h>

#include <QBoxLayout>
#include <QFile>
#include <QKeyEvent>
#include <QWebEngineView>

namespace Hatchit {

    namespace Editor {

        AboutDialog::AboutDialog(QWidget* widget)
            : QDialog(widget)
        {
            setWindowTitle(tr("About Hatchit Editor"));

            m_firstLoad = true;
           
            QString aboutText = QString("Hatchit Editor\nVersion %1.%2.%3\n").arg(HatchitEditor_VERSION_MAJOR)
                                                                           .arg(HatchitEditor_VERSION_MINOR)
                                                                           .arg(HatchitEditor_VERSION_BUILD);


            QString creditsText = QString("Copyright(c) 2015 Third - Degree\nCopyright(c) 2015 Matt Guerrette");

            QTextBrowser* aboutBrowser = new QTextBrowser;
            aboutBrowser->setText(aboutText + "\n" + creditsText);
            m_aboutPane = new CollapsePane("About", aboutBrowser);
            //m_aboutPane->setCollapseState(CollapseState::ExpandedDisabled);


            m_mainLayout = new QVBoxLayout;
            m_mainLayout->addWidget(m_aboutPane);
            m_mainLayout->setAlignment(m_aboutPane, Qt::AlignTop);
        }



        void AboutDialog::keyPressEvent(QKeyEvent* e)
        {
            if (e->key() == Qt::Key::Key_Escape)
                close();
        }


        void AboutDialog::OnLoadLicense(bool ok)
        {

            if (m_firstLoad)
            {
                if (!ok)
                {
                    QTextBrowser* browser = new QTextBrowser;
                    QFile license("LICENSE.GPLv3");
                    license.open(QIODevice::ReadOnly);
                    browser->setText(license.readAll());

                    m_collapsePane = new CollapsePane(tr("License"), browser);
                }
               

                //m_collapsePane->setCollapseState(CollapseState::ExpandedDisabled);
                m_mainLayout->addWidget(m_collapsePane);
                m_mainLayout->setAlignment(m_collapsePane, Qt::AlignTop);
                setLayout(m_mainLayout);

            }

            m_firstLoad = false;
        }

    }

}
