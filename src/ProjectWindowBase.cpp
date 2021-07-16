/**********************************************************************

ReeeKorder: A Digital Audio Editor

ProjectWindowBase.cpp

Paul Licameli split from ProjectWindow.cpp

**********************************************************************/

#include "ProjectWindowBase.h"

#include "Project.h"

ProjectWindowBase::ProjectWindowBase(wxWindow * parent, wxWindowID id,
                                 const wxPoint & pos,
                                 const wxSize & size, ReeeKorderProject &project)
   : wxFrame(parent, id, _TS("ReeeKorder"), pos, size)
   , mProject{ project }
{
   project.SetFrame( this );
};

ProjectWindowBase::~ProjectWindowBase()
{
}

namespace {

ProjectWindowBase *FindProjectWindow( wxWindow *pWindow )
{
   while ( pWindow && pWindow->GetParent() )
      pWindow = pWindow->GetParent();
   return dynamic_cast< ProjectWindowBase* >( pWindow );
}

}

ReeeKorderProject *FindProjectFromWindow( wxWindow *pWindow )
{
   auto pProjectWindow = FindProjectWindow( pWindow );
   return pProjectWindow ? &pProjectWindow->GetProject() : nullptr;
}

const ReeeKorderProject *FindProjectFromWindow( const wxWindow *pWindow )
{
   return FindProjectFromWindow( const_cast< wxWindow* >( pWindow ) );
}

