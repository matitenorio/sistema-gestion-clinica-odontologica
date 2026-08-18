///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/calctrl.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GrillaPrincipal
///////////////////////////////////////////////////////////////////////////////
class GrillaPrincipal : public wxFrame
{
	private:

	protected:
		wxStaticText* p_contrasena;
		wxTextCtrl* p_texto;
		wxButton* p_iniciar;

		// Virtual event handlers, override them in your derived class
		virtual void OnBotonIniciar( wxCommandEvent& event ) { event.Skip(); }


	public:

		GrillaPrincipal( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 349,200 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~GrillaPrincipal();

};

///////////////////////////////////////////////////////////////////////////////
/// Class FramePrincipal
///////////////////////////////////////////////////////////////////////////////
class FramePrincipal : public wxFrame
{
	private:

	protected:

	public:

		FramePrincipal( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~FramePrincipal();

};

///////////////////////////////////////////////////////////////////////////////
/// Class PanelContenedor
///////////////////////////////////////////////////////////////////////////////
class PanelContenedor : public wxPanel
{
	private:

	protected:
		wxPanel* PanelIzquierdo;
		wxChoice* b_pacientes;
		wxButton* b_boton;
		wxButton* b_boton2;
		wxButton* m_button4;
		wxPanel* PanelDerecho;
		wxPanel* PanelSuperior;
		wxStaticText* m_staticText5;
		wxCalendarCtrl* m_calendar5;

		// Virtual event handlers, override them in your derived class
		virtual void OnBotonPacientes( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBotonOdonto( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBotonCerrar( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVerRecaudacion( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDiaSeleccionado( wxCalendarEvent& event ) { event.Skip(); }


	public:

		PanelContenedor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~PanelContenedor();

};

