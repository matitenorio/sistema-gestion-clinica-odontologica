///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wxfb_project.h"

///////////////////////////////////////////////////////////////////////////

GrillaPrincipal::GrillaPrincipal( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	p_contrasena = new wxStaticText( this, wxID_ANY, wxT("Contraseña:"), wxDefaultPosition, wxDefaultSize, 0 );
	p_contrasena->Wrap( -1 );
	bSizer3->Add( p_contrasena, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	p_texto = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( p_texto, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	p_iniciar = new wxButton( this, wxID_ANY, wxT("Iniciar"), wxDefaultPosition, wxDefaultSize, 0 );

	p_iniciar->SetDefault();
	bSizer3->Add( p_iniciar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer2 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	p_iniciar->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GrillaPrincipal::OnBotonIniciar ), NULL, this );
}

GrillaPrincipal::~GrillaPrincipal()
{
	// Disconnect Events
	p_iniciar->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GrillaPrincipal::OnBotonIniciar ), NULL, this );

}

FramePrincipal::FramePrincipal( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );


	this->Centre( wxBOTH );
}

FramePrincipal::~FramePrincipal()
{
}

PanelContenedor::PanelContenedor( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizerPrincipal;
	bSizerPrincipal = new wxBoxSizer( wxHORIZONTAL );

	PanelIzquierdo = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerAuxiliar;
	bSizerAuxiliar = new wxBoxSizer( wxVERTICAL );

	wxString b_pacientesChoices[] = { wxT("Pacientes"), wxT("Agregar nuevo Paciente"), wxT("Lista de Pacientes") };
	int b_pacientesNChoices = sizeof( b_pacientesChoices ) / sizeof( wxString );
	b_pacientes = new wxChoice( PanelIzquierdo, wxID_ANY, wxDefaultPosition, wxDefaultSize, b_pacientesNChoices, b_pacientesChoices, 0 );
	b_pacientes->SetSelection( 0 );
	bSizerAuxiliar->Add( b_pacientes, 0, wxALL, 0 );

	b_boton = new wxButton( PanelIzquierdo, wxID_ANY, wxT("Odontologos"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerAuxiliar->Add( b_boton, 1, wxALL, 10 );

	b_boton2 = new wxButton( PanelIzquierdo, wxID_ANY, wxT("Cerrar Cesion"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerAuxiliar->Add( b_boton2, 1, wxALL, 10 );

	m_button4 = new wxButton( PanelIzquierdo, wxID_ANY, wxT("Recaudacion"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerAuxiliar->Add( m_button4, 0, wxALL, 5 );


	PanelIzquierdo->SetSizer( bSizerAuxiliar );
	PanelIzquierdo->Layout();
	bSizerAuxiliar->Fit( PanelIzquierdo );
	bSizerPrincipal->Add( PanelIzquierdo, 1, wxEXPAND | wxALL, 5 );

	PanelDerecho = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerContenido;
	bSizerContenido = new wxBoxSizer( wxVERTICAL );

	PanelSuperior = new wxPanel( PanelDerecho, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	m_staticText5 = new wxStaticText( PanelSuperior, wxID_ANY, wxT("CLINICA ODONTOLOGICA"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer14->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	PanelSuperior->SetSizer( bSizer14 );
	PanelSuperior->Layout();
	bSizer14->Fit( PanelSuperior );
	bSizerContenido->Add( PanelSuperior, 0, wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_calendar5 = new wxCalendarCtrl( PanelDerecho, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SHOW_HOLIDAYS );
	bSizerContenido->Add( m_calendar5, 1, wxALL|wxEXPAND, 5 );


	PanelDerecho->SetSizer( bSizerContenido );
	PanelDerecho->Layout();
	bSizerContenido->Fit( PanelDerecho );
	bSizerPrincipal->Add( PanelDerecho, 1, wxALL|wxEXPAND, 5 );


	this->SetSizer( bSizerPrincipal );
	this->Layout();

	// Connect Events
	b_pacientes->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelContenedor::OnBotonPacientes ), NULL, this );
	b_boton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelContenedor::OnBotonOdonto ), NULL, this );
	b_boton2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelContenedor::OnBotonCerrar ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelContenedor::OnVerRecaudacion ), NULL, this );
	m_calendar5->Connect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( PanelContenedor::OnDiaSeleccionado ), NULL, this );
}

PanelContenedor::~PanelContenedor()
{
	// Disconnect Events
	b_pacientes->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( PanelContenedor::OnBotonPacientes ), NULL, this );
	b_boton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelContenedor::OnBotonOdonto ), NULL, this );
	b_boton2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelContenedor::OnBotonCerrar ), NULL, this );
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PanelContenedor::OnVerRecaudacion ), NULL, this );
	m_calendar5->Disconnect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( PanelContenedor::OnDiaSeleccionado ), NULL, this );

}
