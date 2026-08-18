#include "FramePrincipalHija.h"
#include <wx/init.h>
#include "Application.h"
#include "PanelContenedorHijo.h"
#include "Clinica.h"

	
//Crea un size vertical,crea el panel principal y lo agrega ocupando toda la ventana.
FramePrincipalHija::FramePrincipalHija(wxWindow *parent) : FramePrincipal(parent) {
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(sizer);
	
	PanelContenedorHijo *panel = new PanelContenedorHijo(this);
	
	sizer->Add(panel,1,wxEXPAND);
	this->Layout();
}

FramePrincipalHija::~FramePrincipalHija() {
	
}

