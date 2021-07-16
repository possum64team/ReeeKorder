/**********************************************************************
 
 ReeeKorder: A Digital Audio Editor
 
 SelectUtilities.h
 
 Paul Licameli split from SelectMenus.h
 
 **********************************************************************/

#ifndef __AUDACITY_SELECT_UTILITIES__
#define __AUDACITY_SELECT_UTILITIES__

class ReeeKorderProject;
class Track;

/// Namespace for functions for Select menu
namespace SelectUtilities {

AUDACITY_DLL_API void DoSelectTimeAndTracks(
   ReeeKorderProject &project, bool bAllTime, bool bAllTracks);
AUDACITY_DLL_API void SelectAllIfNone( ReeeKorderProject &project );
AUDACITY_DLL_API bool SelectAllIfNoneAndAllowed( ReeeKorderProject &project );
AUDACITY_DLL_API void SelectNone( ReeeKorderProject &project );
AUDACITY_DLL_API void DoListSelection(
   ReeeKorderProject &project, Track *t,
   bool shift, bool ctrl, bool modifyState );
AUDACITY_DLL_API void DoSelectAll( ReeeKorderProject &project );
AUDACITY_DLL_API void DoSelectAllAudio( ReeeKorderProject &project );
AUDACITY_DLL_API void DoSelectSomething( ReeeKorderProject &project );

}

#endif
