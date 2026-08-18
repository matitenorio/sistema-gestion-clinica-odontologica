#ifndef PANELCONTENEDORHIJO_H
#define PANELCONTENEDORHIJO_H
#include "wxfb_project.h"
#include <wx/panel.h>
#include <wx/grid.h>

class PanelContenedorHijo : public PanelContenedor {
	
private:
	wxPanel *panelActual = nullptr;
	wxString m_fechaSeleccionada;
protected:
	void OnBotonOdonto( wxCommandEvent& event )  override;
	void OnBotonCerrar( wxCommandEvent& event )  override;
	void OnBotonPacientes(wxCommandEvent &event) override;
	void OnDiaSeleccionado(wxCalendarEvent &event) override;
	
	void CambiarPanel(wxPanel *nuevo);
	
	void ActualizarListaVisual(wxCommandEvent &event);
	void OnNuevoPacienteClick(wxCommandEvent &event);
	
	void MostrarGrillaPacientes();
	
	void MostrarGrillaOdontologos();
	void OnNuevoOdontologoClick(wxCommandEvent &event);
	
	void OnNuevoTurnoClick(wxCommandEvent &event);
	
	void OnBuscarPacienteNombre(wxCommandEvent &event);
	wxTextCtrl* m_txtBusquedaNombre;
	
	void RefrescarAgenda();
	
	void MostrarPanelRecaudacion();
	void OnVerRecaudacion(wxCommandEvent &event);
	
public:
	PanelContenedorHijo(wxWindow *parent=NULL);
	~PanelContenedorHijo();
};

#endif

