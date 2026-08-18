#ifndef GRILLAHIJA_H
#define GRILLAHIJA_H
#include "wxfb_project.h"

class GrillaHija : public GrillaPrincipal {
	
private:
	
protected:
	void OnBotonIniciar( wxCommandEvent& event )  override;
	void OnEnter(wxCommandEvent &event);
	
public:
	GrillaHija(wxWindow *parent=NULL);
	~GrillaHija();
};

#endif

