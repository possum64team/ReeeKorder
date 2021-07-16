/**********************************************************************

ReeeKorder: A Digital Audio Editor

ProjectWindowBase.h

Paul Licameli split from ProjectWindow.h

**********************************************************************/

#ifndef __AUDACITY_PROJECT_WINDOW_BASE__
#define __AUDACITY_PROJECT_WINDOW_BASE__

#include <wx/frame.h> // to inherit

class ReeeKorderProject;

///\brief A top-level window associated with a project
class ProjectWindowBase /* not final */ : public wxFrame
{
public:
   explicit ProjectWindowBase(
      wxWindow * parent, wxWindowID id,
      const wxPoint & pos, const wxSize &size,
      ReeeKorderProject &project );

   ~ProjectWindowBase() override;

   ReeeKorderProject &GetProject() { return mProject; }
   const ReeeKorderProject &GetProject() const { return mProject; }

protected:
   ReeeKorderProject &mProject;
};

AUDACITY_DLL_API ReeeKorderProject *FindProjectFromWindow( wxWindow *pWindow );
const ReeeKorderProject *FindProjectFromWindow( const wxWindow *pWindow );

#endif

