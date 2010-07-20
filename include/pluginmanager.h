/******************************************************************************
 *
 *
 * Project:  OpenCPN
 * Purpose:  PlugIn Manager Object
 * Author:   David Register
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register   *
 *   $EMAIL$   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *
 */

#ifndef _PLUGINMGR_H_
#define _PLUGINMGR_H_

#include <wx/wx.h>
#include <wx/dynarray.h>
#include <wx/dynlib.h>

#include "ocpn_plugin.h"
#include "chart1.h"                 // for MyFrame
#include "chcanv.h"                 // for ViewPort
#include "nmea.h"                   // for GenericPosDat



//-----------------------------------------------------------------------------------------------------
//
//          The PlugIn Container Specification
//
//-----------------------------------------------------------------------------------------------------
class PlugInContainer
{
      public:
            opencpn_plugin    *m_pplugin;
            int               m_cap_flag;         // PlugIn Capabilities descriptor
            wxString          m_plugin_file;
            destroy_t         *m_destroy_fn;
            wxDynamicLibrary  *m_plibrary;
            wxString          m_description;
};

//    Declare an array of PlugIn Containers
WX_DEFINE_ARRAY_PTR(PlugInContainer *, ArrayOfPlugIns);

class PlugInMenuItemContainer
{
      public:
            wxMenuItem        *pmenu_item;
            opencpn_plugin    *m_pplugin;
            bool              b_viz;
            bool              b_grey;
            int               id;
};

//    Define an array of PlugIn MenuItem Containers
WX_DEFINE_ARRAY_PTR(PlugInMenuItemContainer *, ArrayOfPlugInMenuItems);


class PlugInToolbarToolContainer
{
      public:
            opencpn_plugin    *m_pplugin;
            int               id;
            wxChar            *label;
            wxBitmap          *bitmap;
            wxBitmap          *bmpDisabled;
            wxItemKind        kind;
            wxChar            *shortHelp;
            wxChar            *longHelp;
            wxObject          *clientData;
            int               position;
            bool              b_viz;
            int               tool_sel;

};

//    Define an array of PlugIn ToolbarTool Containers
WX_DEFINE_ARRAY_PTR(PlugInToolbarToolContainer *, ArrayOfPlugInToolbarTools);



//-----------------------------------------------------------------------------------------------------
//
//          The PlugIn Manager Specification
//
//-----------------------------------------------------------------------------------------------------

class PlugInManager
{

public:
      PlugInManager(MyFrame *parent);
      virtual ~PlugInManager();

      bool LoadAllPlugIns(wxString &shared_data_prefix);
      bool UnLoadAllPlugIns();
      bool DeactivateAllPlugIns();
      PlugInContainer *LoadPlugIn(wxString plugin_file);

      bool RenderAllCanvasOverlayPlugIns( wxMemoryDC *pmdc, ViewPort *vp);
      void SendCursorLatLonToAllPlugIns( double lat, double lon);

      void AddAllPlugInToolboxPanels( wxNotebook *pnotebook);
      void CloseAllPlugInPanels( int );

      ArrayOfPlugInToolbarTools &GetPluginToolbarToolArray(){ return m_PlugInToolbarTools; }
      int AddToolbarTool(wxChar *label, wxBitmap *bitmap, wxBitmap *bmpDisabled, wxItemKind kind,
                                        wxChar *shortHelp, wxChar *longHelp, wxObject *clientData, int position,
                                        int tool_sel, opencpn_plugin *pplugin );
      void RemoveToolbarTool(int tool_id);
      void SetToolbarToolViz(int tool_id, bool viz);


      ArrayOfPlugInMenuItems &GetPluginContextMenuItemArray(){ return m_PlugInMenuItems; }
      int AddCanvasContextMenuItem(wxMenuItem *pitem, opencpn_plugin *pplugin );
      void RemoveCanvasContextMenuItem(int item);
      void SetCanvasContextMenuItemViz(int item, bool viz);
      void SetCanvasContextMenuItemGrey(int item, bool grey);

      void SendNMEASentenceToAllPlugIns(wxString &sentence);
      void SendPositionFixToAllPlugIns(GenericPosDat *ppos);

      wxString GetLastError();
      MyFrame *GetParentFrame(){ return pParent; }

private:

      MyFrame                 *pParent;

      ArrayOfPlugIns    plugin_array;
      wxString          m_last_error_string;

      ArrayOfPlugInMenuItems        m_PlugInMenuItems;
      ArrayOfPlugInToolbarTools     m_PlugInToolbarTools;

      int               m_plugin_tool_id_next;
      int               m_plugin_menu_item_id_next;

 //     opencpn_plugin    *m_plugin_base;


};





#endif            // _PLUGINMGR_H_
