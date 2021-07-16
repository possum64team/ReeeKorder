/**********************************************************************

  ReeeKorder: A Digital Audio Editor

  Project.cpp

  Dominic Mazzoni
  Vaughan Johnson

*//*******************************************************************/


#include "Project.h"

#include "KeyboardCapture.h"
#include "TempDirectory.h"
#include "./widgets/ErrorDialog.h"

#include <wx/display.h>
#include <wx/filename.h>
#include <wx/frame.h>

wxDEFINE_EVENT(EVT_TRACK_PANEL_TIMER, wxCommandEvent);
wxDEFINE_EVENT(EVT_PROJECT_ACTIVATION, wxCommandEvent);

size_t AllProjects::size() const
{
   return gReeeKorderProjects.size();
}

auto AllProjects::begin() const -> const_iterator
{
   return gReeeKorderProjects.begin();
}

auto AllProjects::end() const -> const_iterator
{
   return gReeeKorderProjects.end();
}

auto AllProjects::rbegin() const -> const_reverse_iterator
{
   return gReeeKorderProjects.rbegin();
}

auto AllProjects::rend() const -> const_reverse_iterator
{
   return gReeeKorderProjects.rend();
}

auto AllProjects::Remove( ReeeKorderProject &project ) -> value_type
{
   std::lock_guard<std::mutex> guard{ Mutex() };
   auto start = begin(), finish = end(), iter = std::find_if(
      start, finish,
      [&]( const value_type &ptr ){ return ptr.get() == &project; }
   );
   if (iter == finish)
      return nullptr;
   auto result = *iter;
   gReeeKorderProjects.erase( iter );
   return result;
}

void AllProjects::Add( const value_type &pProject )
{
   std::lock_guard<std::mutex> guard{ Mutex() };
   gReeeKorderProjects.push_back( pProject );
}

bool AllProjects::sbClosing = false;

bool AllProjects::Close( bool force )
{
   ValueRestorer<bool> cleanup{ sbClosing, true };
   while (AllProjects{}.size())
   {
      // Closing the project has global side-effect
      // of deletion from gReeeKorderProjects
      if ( force )
      {
         GetProjectFrame( **AllProjects{}.begin() ).Close(true);
      }
      else
      {
         if (! GetProjectFrame( **AllProjects{}.begin() ).Close())
            return false;
      }
   }
   return true;
}

std::mutex &AllProjects::Mutex()
{
   static std::mutex theMutex;
   return theMutex;
}

int ReeeKorderProject::mProjectCounter=0;// global counter.

/* Define Global Variables */
//This is a pointer to the currently-active project.
static ReeeKorderProject *gActiveProject;
//This array holds onto all of the projects currently open
AllProjects::Container AllProjects::gReeeKorderProjects;

AUDACITY_DLL_API ReeeKorderProject *GetActiveProject()
{
   return gActiveProject;
}

void SetActiveProject(ReeeKorderProject * project)
{
   if ( gActiveProject != project ) {
      gActiveProject = project;
      KeyboardCapture::Capture( nullptr );
      wxTheApp->QueueEvent( safenew wxCommandEvent{ EVT_PROJECT_ACTIVATION } );
   }
   wxTheApp->SetTopWindow( FindProjectFrame( project ) );
}

ReeeKorderProject::ReeeKorderProject()
{
   mProjectNo = mProjectCounter++; // Bug 322
   AttachedObjects::BuildAll();
   // But not for the attached windows.  They get built only on demand, such as
   // from menu items.

   // Make sure there is plenty of space for Sqlite files
   wxLongLong freeSpace = 0;

   auto path = TempDirectory::TempDir();
   if (wxGetDiskSpace(path, NULL, &freeSpace)) {
      if (freeSpace < wxLongLong(wxLL(100 * 1048576))) {
         auto volume = FileNames::AbbreviatePath( path );
         /* i18n-hint: %s will be replaced by the drive letter (on Windows) */
         ShowErrorDialog(nullptr, 
            XO("Warning"),
            XO("There is very little free disk space left on %s\n"
               "Please select a bigger temporary directory location in\n"
               "Directories Preferences.").Format( volume ),
            "Error:_Disk_full_or_not_writable"
            );
      }
   }

}

ReeeKorderProject::~ReeeKorderProject()
{
}

void ReeeKorderProject::SetFrame( wxFrame *pFrame )
{
   mFrame = pFrame;
}

void ReeeKorderProject::SetPanel( wxWindow *pPanel )
{
   mPanel = pPanel;
}

const wxString &ReeeKorderProject::GetProjectName() const
{
   return mName;
}

void ReeeKorderProject::SetProjectName(const wxString &name)
{
   mName = name;
}

FilePath ReeeKorderProject::GetInitialImportPath() const
{
   return mInitialImportPath;
}

void ReeeKorderProject::SetInitialImportPath(const FilePath &path)
{
   if (mInitialImportPath.empty())
   {
      mInitialImportPath = path;
   }
}

AUDACITY_DLL_API wxFrame &GetProjectFrame( ReeeKorderProject &project )
{
   auto ptr = project.GetFrame();
   if ( !ptr )
      THROW_INCONSISTENCY_EXCEPTION;
   return *ptr;
}

AUDACITY_DLL_API const wxFrame &GetProjectFrame( const ReeeKorderProject &project )
{
   auto ptr = project.GetFrame();
   if ( !ptr )
      THROW_INCONSISTENCY_EXCEPTION;
   return *ptr;
}

AUDACITY_DLL_API wxWindow &GetProjectPanel( ReeeKorderProject &project )
{
   auto ptr = project.GetPanel();
   if ( !ptr )
      THROW_INCONSISTENCY_EXCEPTION;
   return *ptr;
}

AUDACITY_DLL_API const wxWindow &GetProjectPanel(
   const ReeeKorderProject &project )
{
   auto ptr = project.GetPanel();
   if ( !ptr )
      THROW_INCONSISTENCY_EXCEPTION;
   return *ptr;
}
