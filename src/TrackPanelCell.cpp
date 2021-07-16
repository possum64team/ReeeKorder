/**********************************************************************
 
 ReeeKorder: A Digital Audio Editor
 
 TrackPanelCell.cpp
 
 Paul Licameli split from TrackPanel.cpp
 
 **********************************************************************/

#include "TrackPanelCell.h"

#include <wx/event.h>
#include "HitTestResult.h"
#include "RefreshCode.h"

TrackPanelNode::TrackPanelNode()
{
}

TrackPanelNode::~TrackPanelNode()
{
}

TrackPanelGroup::TrackPanelGroup()
{
}

TrackPanelGroup::~TrackPanelGroup()
{
}

TrackPanelCell::~TrackPanelCell()
{
}

HitTestPreview TrackPanelCell::DefaultPreview
(const TrackPanelMouseState &, const ReeeKorderProject *)
{
   return {};
}

unsigned TrackPanelCell::HandleWheelRotation
(const TrackPanelMouseEvent &, ReeeKorderProject *)
{
   return RefreshCode::Cancelled;
}

unsigned TrackPanelCell::DoContextMenu
   (const wxRect &, wxWindow*, wxPoint *, ReeeKorderProject*)
{
   return RefreshCode::RefreshNone;
}

unsigned TrackPanelCell::CaptureKey(
   wxKeyEvent &event, ViewInfo &, wxWindow *, ReeeKorderProject *)
{
   event.Skip();
   return RefreshCode::RefreshNone;
}

unsigned TrackPanelCell::KeyDown(
   wxKeyEvent &event, ViewInfo &, wxWindow *, ReeeKorderProject *)
{
   event.Skip();
   return RefreshCode::RefreshNone;
}

unsigned TrackPanelCell::KeyUp(
   wxKeyEvent &event, ViewInfo &, wxWindow *, ReeeKorderProject *)
{
   event.Skip();
   return RefreshCode::RefreshNone;
}

unsigned TrackPanelCell::Char(
   wxKeyEvent &event, ViewInfo &, wxWindow *, ReeeKorderProject *)
{
   event.Skip();
   return RefreshCode::RefreshNone;
}
