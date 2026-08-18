#include "GrillaHija.h"
#include <wx/string.h>
#include <wx/msgdlg.h>
#include <wx/wx.h>
#include "FramePrincipalHija.h"
#include "Application.h"

DECLARE_APP(Application)

//Convierte el input  en contraseña, permite usar el enter y conecta el enter con OnEnter
GrillaHija::GrillaHija(wxWindow *parent) : GrillaPrincipal(parent) {
	p_texto->SetWindowStyleFlag(wxTE_PROCESS_ENTER | wxTE_PASSWORD);
	p_texto->Bind(wxEVT_TEXT_ENTER, &GrillaHija::OnEnter, this);
}

//Lee la contraseña si es correcta, crea ventana principal, muestra y oculta el login
//Si es incorrecta muestra error
void GrillaHija::OnBotonIniciar( wxCommandEvent  &event)  {
	wxString pass = p_texto->GetValue();
	
	Clinica &c = wxGetApp().GetClinica();
	
	if(pass == "1234"){
		FramePrincipalHija *principal = new FramePrincipalHija(NULL);
		principal->Show();
		
		this->Destroy(); //Evita que se cierre todo cuando se abre
	}else{
		wxMessageBox("Contraseña incorrecta","Error",wxOK | wxICON_ERROR);
	}
}

//Reusa el mismo codigo para que ENTER = boton iniciar
void GrillaHija::OnEnter(wxCommandEvent &event){
	OnBotonIniciar(event);
}
GrillaHija::~GrillaHija() {
	
}

