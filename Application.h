#ifndef APPLICATION_H
#define APPLICATION_H
#include "Clinica.h"
#include <wx/app.h>

class Application : public wxApp {
	Clinica clinica;
public:
	virtual bool OnInit();
	
	Clinica &GetClinica();
};

#endif
