#include <wx/image.h>
#include "Application.h"
#include "GrillaHija.h"

//Arranca la aplicacion
IMPLEMENT_APP(Application)

	//Crea la primer ventana login y la muestra
bool Application::OnInit() {
	wxInitAllImageHandlers();
	GrillaHija *win = new GrillaHija(NULL);
	win->Show();
	return true;
}

//Devuelve la clinica global para usarla en cualquier parte del programa
Clinica &Application::GetClinica(){
	return clinica;
}
