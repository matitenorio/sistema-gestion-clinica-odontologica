#include "PanelContenedorHijo.h"
#include"GrillaHija.h"
#include <wx/msgdlg.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/window.h>
#include <wx/frame.h>
#include "Application.h"
#include <wx/wx.h>
#include "Clinica.h"
#include <wx/grid.h>
#include <wx/menu.h>
#include <wx/tokenzr.h>
#include <wx/choicdlg.h>
#include <wx/string.h>
DECLARE_APP(Application)
	
//Conecta el calendario con la funcion
PanelContenedorHijo::PanelContenedorHijo(wxWindow *parent) : PanelContenedor(parent) {
	m_calendar5->Bind(wxEVT_CALENDAR_SEL_CHANGED, &PanelContenedorHijo::OnDiaSeleccionado,this);
}

//Borra el panel anterior, guarda el nuevo, lo mete dentro del panel derech
//lo agrega al layout. Permite cambiar de pantallas
void PanelContenedorHijo::CambiarPanel(wxPanel *nuevo){
	if(panelActual!= nullptr){
		panelActual->Destroy();
	}
	
	panelActual = nuevo;
	
	//Metemos dentro del panel derecho
    panelActual->Reparent(PanelDerecho);
	
	//Obtenemos el sizer real del panel derecho
	wxBoxSizer *sizer = (wxBoxSizer*)PanelDerecho->GetSizer();
	
	sizer->Add(panelActual,1,wxEXPAND| wxALL,5);
	
	PanelDerecho->Layout();
}

//Boton Pacientes
void PanelContenedorHijo::OnBotonPacientes(wxCommandEvent &event) {
	// 1. Obtenemos qué lugar de la lista tocó el usuario
	int seleccion = b_pacientes->GetSelection(); 
	
	// 2. Ejecutamos la acción según el orden de tu menú
	if (seleccion == 1) { 
		// Si eligió el primero de la lista (después del título), es AGREGAR
		this->OnNuevoPacienteClick(event); 
	} 
	else if (seleccion == 2) { 
		// Si eligió el segundo, es MOSTRAR LA GRILLA
		this->MostrarGrillaPacientes(); 
	}
	
	// 3. Reseteamos el menú para que vuelva a decir "Pacientes" arriba
	b_pacientes->SetSelection(0); 
}

void PanelContenedorHijo::ActualizarListaVisual(wxCommandEvent &event) {
	// Obtenemos la instancia de Clinica que vive en la App
	Clinica &c = wxGetApp().GetClinica();
	const auto &lista = c.obtenerPacientes();
	
	// b_pacientes es el nombre del desplegable (wxChoice)
	b_pacientes->Clear(); 
	
	if(lista.empty()) {
		wxMessageBox("No hay pacientes registrados.", "Clinica");
	} else {
		for(const auto &p : lista) {
			b_pacientes->Append(p.Vernombre()); // Agregamos el nombre al desplegable
		}
		wxMessageBox("Lista actualizada en el menu superior izquierdo.", "Exito");
	}
}
//Boton odontologos, muestra el panel simple con texto
void PanelContenedorHijo::OnBotonOdonto(wxCommandEvent& event) {
	wxMenu menu;
	menu.Append(2001, "Ver lista de Odontólogos");
	menu.Append(2002, "Registrar nuevo Odontólogo");
	
	// Conectamos las opciones
	Bind(wxEVT_MENU, [this](wxCommandEvent&){ this->MostrarGrillaOdontologos(); }, 2001);
	
	// CONEXIÓN CORREGIDA:
	Bind(wxEVT_MENU, [this](wxCommandEvent& e){ this->OnNuevoOdontologoClick(e); }, 2002); 
	
	PopupMenu(&menu);
}

//Boton cerrar sesion
//Abre el login, cierra la ventana principal
void PanelContenedorHijo::OnBotonCerrar( wxCommandEvent& event )  {
	GrillaHija *login = new GrillaHija(NULL);
	login->Show();
	
	wxWindow *top = wxGetTopLevelParent(this);
	top->Destroy();
}

//Evento calendario
//Detecta el dia elegido, crea un panel, muestra la fecha, boton nnuevo turno
void PanelContenedorHijo::OnDiaSeleccionado(wxCalendarEvent &event) {
	// 1. Solo guardamos la fecha que se tocó en el calendario
	m_fechaSeleccionada = event.GetDate().FormatISODate(); 
	
	// 2. Llamamos a la función que dibuja todo
	this->RefrescarAgenda(); 
}


// Al final de PanelContenedorHijo.cpp
void PanelContenedorHijo::OnNuevoPacienteClick(wxCommandEvent &event) {
	wxString nombre = wxGetTextFromUser("Nombre completo:", "Nuevo Paciente");
	if (nombre.IsEmpty()) return;
	
	wxString dniStr = wxGetTextFromUser("DNI:", "Nuevo Paciente");
	long dni;
	if (!dniStr.ToLong(&dni)) return;
	
	wxString tel = wxGetTextFromUser("Telefono:", "Nuevo Paciente");
	wxString mail = wxGetTextFromUser("E-mail:", "Nuevo Paciente");
	
	wxString obraSocial = wxGetTextFromUser("Obra Social (dejar vacio si no tiene):", "Paciente");
	
	// Accedemos a la clinica y registramos
	Clinica &c = wxGetApp().GetClinica();
	c.registrarPaciente(nombre.ToStdString(), dni, tel.ToStdString(), mail.ToStdString(), obraSocial.ToStdString());
	
	wxMessageBox("¡Paciente guardado con éxito!", "Clinica");
}

void PanelContenedorHijo::MostrarGrillaPacientes() {
	// 1. Creamos el contenedor y los organizadores (Sizers)
	wxPanel* panelContenedor = new wxPanel(PanelDerecho);
	wxBoxSizer* sizerPrincipal = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* sizerBusqueda = new wxBoxSizer(wxHORIZONTAL);
	
	// 2. Barra de búsqueda
	wxStaticText* labelBusq = new wxStaticText(panelContenedor, wxID_ANY, "Buscar por Nombre y Apellido:");
	m_txtBusquedaNombre = new wxTextCtrl(panelContenedor, wxID_ANY, "", wxDefaultPosition, wxSize(150, -1));
	wxButton* btnBuscar = new wxButton(panelContenedor, wxID_ANY, "Buscar");
	
	btnBuscar->Bind(wxEVT_BUTTON, &PanelContenedorHijo::OnBuscarPacienteNombre, this);
	
	sizerBusqueda->Add(labelBusq, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	sizerBusqueda->Add(m_txtBusquedaNombre, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	sizerBusqueda->Add(btnBuscar, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	
	// 3. Configuración de la Grilla
	wxGrid* grilla = new wxGrid(panelContenedor, wxID_ANY);
	Clinica &c = wxGetApp().GetClinica();
	const auto &lista = c.obtenerPacientes();
	
	grilla->CreateGrid(lista.size(), 6);
	grilla->SetColLabelValue(0, "ID");
	grilla->SetColLabelValue(1, "Nombre");
	grilla->SetColLabelValue(2, "DNI");
	grilla->SetColLabelValue(3, "Telefono");
	grilla->SetColLabelValue(4, "E-mail");
	grilla->SetColLabelValue(5, "O. Social");
	
	// 4. Llenado de datos con los nombres de funciones correctos
	for (size_t i = 0; i < lista.size(); ++i) {
		grilla->SetCellValue(i, 0, wxString::Format("%d", lista[i].Verid()));
		grilla->SetCellValue(i, 1, lista[i].Vernombre());
		grilla->SetCellValue(i, 2, wxString::Format("%d", lista[i].Verdni()));
		grilla->SetCellValue(i, 3, lista[i].Vertelefono());
		
		// CORRECCIONES SEGÚN EL COMPILADOR:
		grilla->SetCellValue(i, 4, lista[i].Vermail()); // Cambiado de Veremail a Vermail
		grilla->SetCellValue(i,5,lista[i].VerObraSocial()); // Cambiado de Verobrasocial a tieneObraSocial
		
		grilla->SetReadOnly(i,0); //Bloqueamos ID
		//Habilitamos edicion de los demas campos
		grilla->SetReadOnly(i,1,false);
		grilla->SetReadOnly(i,2,false);
		grilla->SetReadOnly(i,3,false);
		grilla->SetReadOnly(i,4,false);
		grilla->SetReadOnly(i,5,false);
	}
	
	grilla->AutoSizeColumns();
	
	//Bind para actualizar datos al editar
	grilla->Bind(wxEVT_GRID_CELL_CHANGED,[this,&c,grilla](wxGridEvent &event){
		int row = event.GetRow();
		int col = event.GetCol();
		
		auto &pac = c.obtenerPacientesEditable()[row];
		wxString nuevoValor = grilla-> GetCellValue(row,col);
		
		switch(col){
		 case 1: pac.AsignarNombre(nuevoValor.ToStdString()); break;
		 case 2:{
			long dni;
			if(nuevoValor.ToLong(&dni))pac.AsignarDni((int)dni);
		    break;
		 }
		 case 3: pac.AsignarTelefono(nuevoValor.ToStdString()); break;
		 case 4: pac.AsignarMail(nuevoValor.ToStdString()); break;
		 case 5: {
			 wxString valor = nuevoValor.Lower();
			 pac.AsignarObraSocial(nuevoValor.ToStdString());
			 break;
		 }
		}
		Paciente::guardarListaCompleta(c.obtenerPacientes());
	});
	
	
	// 5. Unir todo y mostrar
	sizerPrincipal->Add(sizerBusqueda, 0, wxEXPAND | wxALL, 5);
	sizerPrincipal->Add(grilla, 1, wxEXPAND | wxALL, 5);
	
	panelContenedor->SetSizer(sizerPrincipal);
	CambiarPanel(panelContenedor);
}

void PanelContenedorHijo::MostrarGrillaOdontologos() {
	wxPanel* panelTabla = new wxPanel(PanelDerecho);
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	
	wxGrid* grilla = new wxGrid(panelTabla, wxID_ANY);
	Clinica &c = wxGetApp().GetClinica(); 
	const auto &lista = c.obtenerOdontologos(); 
	
	// 1. Ampliamos a 6 columnas: ID, Nombre, Especialidad, Dias, Inicio, Fin
	grilla->CreateGrid(lista.size(), 6);
	grilla->SetColLabelValue(0, "ID");
	grilla->SetColLabelValue(1, "Nombre");
	grilla->SetColLabelValue(2, "Especialidad");
	grilla->SetColLabelValue(3, "Dias");
	grilla->SetColLabelValue(4, "Inicio");
	grilla->SetColLabelValue(5, "Fin");
	
	for (size_t i = 0; i < lista.size(); ++i) {
		// Datos básicos
		grilla->SetCellValue(i, 0, wxString::Format("%d", lista[i].Verid())); 
		grilla->SetCellValue(i, 1, lista[i].Vernombre()); 
		grilla->SetCellValue(i, 2, lista[i].Verespecialidad()); 
		
		// 2. Procesamos el vector de días para mostrarlo como un solo texto
		wxString diasStr;
		const auto& dias = lista[i].VerDias(); // Obtenemos el vector<string>
		for(size_t j = 0; j < dias.size(); ++j) {
			diasStr << dias[j] << (j == dias.size() - 1 ? "" : ", ");
		}
		grilla->SetCellValue(i, 3, diasStr);
		
		// 3. Horarios
		grilla->SetCellValue(i, 4, lista[i].VerHoraInicio());
		grilla->SetCellValue(i, 5, lista[i].VerHoraFin());
		
		// Bloqueamos la edición
		grilla->SetReadOnly(i, 0);
		for(int j=1;j<6;++j){
			grilla->SetReadOnly(i,j,false);
		}
	}
	
	grilla->Bind(wxEVT_GRID_CELL_CHANGED, [this, &c, grilla](wxGridEvent &event){
		int row = event.GetRow();
		int col = event.GetCol();
		
		auto &od = c.obtenerOdontologosEditable()[row];
		wxString valor = grilla->GetCellValue(row, col);
		
		switch(col){
		case 1: od.AsignarNombre(valor.ToStdString()); break;
		case 2: od.AsignarEspecialidad(valor.ToStdString()); break;
		
		case 3: { // días (texto ? vector)
			std::vector<std::string> dias;
			wxStringTokenizer tokenizer(valor, ",");
			while(tokenizer.HasMoreTokens()){
				dias.push_back(tokenizer.GetNextToken().Trim().ToStdString());
			}
			od.AsignarDias(dias);
			break;
		}
		
		case 4: od.AsignarHoraInicio(valor.ToStdString()); break;
		case 5: od.AsignarHoraFin(valor.ToStdString()); break;
		}
		
		// (Opcional pero MUY recomendado)
		Odontologo::guardarListaCompleta(c.obtenerOdontologos());
	});
	
	wxButton* btnEliminar = new wxButton(panelTabla, wxID_ANY, "Eliminar Odontólogo");
	
	// Evento
	btnEliminar->Bind(wxEVT_BUTTON, [this, &c, grilla](wxCommandEvent&){
		
		int fila = grilla->GetGridCursorRow();
		
		if(fila == wxNOT_FOUND){
			wxMessageBox("Seleccione un odontólogo");
			return;
		}
		
		if(wxMessageBox("¿Seguro que desea eliminar?", "Confirmar", wxYES_NO) == wxNO)
		   return;
		
		auto &lista = c.obtenerOdontologosEditable();
		
		if(fila < lista.size()){
			lista.erase(lista.begin() + fila);
		}
		
		Odontologo::guardarListaCompleta(c.obtenerOdontologos());
		
		this->MostrarGrillaOdontologos(); // refresca
	});
	
	grilla->AutoSizeColumns();
	
	// ?? PRIMERO la grilla
	sizer->Add(grilla, 1, wxEXPAND | wxALL, 15);
	
	// ?? DESPUÉS el botón (importante)
	sizer->Add(btnEliminar, 0, wxALL | wxALIGN_CENTER, 10);
	
	panelTabla->SetSizer(sizer);
	
	// Mostramos en el panel derecho
	CambiarPanel(panelTabla);
	
}

void PanelContenedorHijo::OnNuevoOdontologoClick(wxCommandEvent &event) {
	// 1. Pedimos los datos básicos
	wxString nombre = wxGetTextFromUser("Nombre completo del Odontólogo:", "Nuevo Odontólogo");
	if (nombre.IsEmpty()) return;
	
	wxString especialidad = wxGetTextFromUser("Especialidad:", "Nuevo Odontólogo");
	if (especialidad.IsEmpty()) return;
	
	// 2. Pedimos los días (ej: Lunes, Miercoles, Viernes)
	wxString diasTexto = wxGetTextFromUser("Días que atiende (separados por coma):", "Nuevo Odontólogo");
	
	// Convertimos el texto en un vector<string> para Clinica.cpp
	std::vector<std::string> diasVector;
	wxStringTokenizer tokenizer(diasTexto, ",");
	while (tokenizer.HasMoreTokens()) {
		diasVector.push_back(tokenizer.GetNextToken().Trim().ToStdString());
	}
	
	// 3. Horarios
	wxString horaInicio = wxGetTextFromUser("Hora de inicio (HH:MM):", "Nuevo Odontólogo", "08:00");
	wxString horaFin = wxGetTextFromUser("Hora de fin (HH:MM):", "Nuevo Odontólogo", "16:00");
	
	// 4. Guardamos en el sistema
	Clinica &c = wxGetApp().GetClinica();
	c.registrarOdontologo(nombre.ToStdString(), especialidad.ToStdString(), diasVector, 
						  horaInicio.ToStdString(), horaFin.ToStdString());
	
	wxMessageBox("Odontólogo registrado con éxito y guardado en archivo.", "Éxito");
}

wxString ObtenerNombreDiaEspanol(const wxString& fechaISO) {
	wxDateTime dt;
	dt.ParseISODate(fechaISO); // Convierte "2026-02-24" a objeto fecha
	
	// Obtenemos el índice (0 = Domingo, 1 = Lunes, ..., 2 = Martes, etc.)
	int diaSemana = dt.GetWeekDay(); 
	
	switch(diaSemana) {
	case 0: return "Domingo";
	case 1: return "Lunes";
	case 2: return "Martes";
	case 3: return "Miercoles";
	case 4: return "Jueves";
	case 5: return "Viernes";
	case 6: return "Sabado";
	default: return "";
	}
}

void PanelContenedorHijo::OnNuevoTurnoClick(wxCommandEvent &event) {
	Clinica &c = wxGetApp().GetClinica();
	int idPaciente = -1;
	
	// 1. PREGUNTAR SI DESEA BUSCAR POR DNI
	int opcion = wxMessageBox("¿Desea buscar al paciente por DNI?\n(Si presiona 'No', se mostrará la lista completa)", 
							  "Seleccion de Paciente", wxYES_NO | wxCANCEL | wxICON_QUESTION);
	
	if (opcion == wxYES) {
		wxString dniBusqueda = wxGetTextFromUser("Ingrese el DNI del paciente:", "Buscar Paciente");
		long dni;
		if (dniBusqueda.ToLong(&dni)) {
			Paciente* p = c.buscarPacientePorDni((int)dni);
			if (p) {
				idPaciente = p->Verid();
				wxMessageBox("Paciente seleccionado: " + p->Vernombre(), "Éxito");
			} else {
				wxMessageBox("No se encontró el paciente. Se procederá a mostrar la lista completa.", "Aviso");
			}
		}
	} else if (opcion == wxCANCEL) {
		return; // El usuario canceló la operación
	}
	
	// 2. SI NO SE ENCONTRÓ POR DNI, MOSTRAR LISTA COMPLETA
	if (idPaciente == -1) {
		const auto &pacientes = c.obtenerPacientes();
		wxArrayString listaPacientes;
		for(const auto &p : pacientes) 
			listaPacientes.Add(wxString::Format("%d - %s", p.Verid(), p.Vernombre()));
		
		wxSingleChoiceDialog dlgPac(this, "Seleccione el Paciente:", "Nuevo Turno", listaPacientes);
		if (dlgPac.ShowModal() != wxID_OK) return;
		idPaciente = pacientes[dlgPac.GetSelection()].Verid();
	}
	
	// 3. ELEGIR ODONTÓLOGO (El resto del código sigue igual)
	const auto &odonto = c.obtenerOdontologos();
	wxArrayString listaOdonto;
	for(const auto &o : odonto) 
		listaOdonto.Add(wxString::Format("%d - %s (%s)", o.Verid(), o.Vernombre(), o.Verespecialidad()));
	
	wxSingleChoiceDialog dlgOdo(this, "Seleccione el Odontólogo:", "Nuevo Turno", listaOdonto);
	if (dlgOdo.ShowModal() != wxID_OK) return;
	int idOdonto = odonto[dlgOdo.GetSelection()].Verid();
	
	// 4. PEDIR HORA Y ASIGNAR
	wxString hora = wxGetTextFromUser("Ingrese la hora (HH:MM):", "Nuevo Turno", "09:00");
	if (hora.IsEmpty()) return;
	
	wxString diaNombre = ObtenerNombreDiaEspanol(m_fechaSeleccionada);
	
	if (c.asignarTurno(idPaciente, idOdonto, m_fechaSeleccionada.ToStdString(), 
					   hora.ToStdString(), diaNombre.ToStdString())) {
		wxMessageBox("Turno asignado correctamente.", "Éxito");
		this->RefrescarAgenda();
	} else {
		wxMessageBox("No se pudo asignar el turno (verifique disponibilidad).", "Error", wxICON_ERROR);
	}
}

void PanelContenedorHijo::OnBuscarPacienteNombre(wxCommandEvent &event){
	Clinica &c = wxGetApp().GetClinica();
	const auto &lista = c.obtenerPacientes();
	
	wxString texto = m_txtBusquedaNombre -> GetValue().Lower();
	bool encontrado = false;
	
	for(const auto &p : lista){
		wxString nombreCompleto = wxString(p.Vernombre()).Lower();
		if(nombreCompleto.Contains(texto)){
			wxMessageBox("Paciente encontrado: " + nombreCompleto, "Resultado");
			encontrado = true;
			break;
		}
	}
	if(!encontrado){
		wxMessageBox("No se encontro paciente con ese nombre y apellido");
	}
}

void PanelContenedorHijo::RefrescarAgenda() {
	Clinica &c = wxGetApp().GetClinica();
	
	wxPanel *panel = new wxPanel(PanelDerecho);
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	
	wxStaticText *titulo = new wxStaticText(panel, wxID_ANY,"Turnos del día: " + m_fechaSeleccionada);
	sizer->Add(titulo, 0, wxALL, 10);
	
	wxButton *btnNuevo = new wxButton(panel, wxID_ANY, "Nuevo Turno");
	btnNuevo->Bind(wxEVT_BUTTON, &PanelContenedorHijo::OnNuevoTurnoClick, this);
	sizer->Add(btnNuevo, 0, wxALL, 5);
	
	for(const auto &t : c.obtenerTurnos()){
		
		if(t.VerFecha() == m_fechaSeleccionada.ToStdString() && !t.estaCancelado()){
			
			wxBoxSizer *fila = new wxBoxSizer(wxHORIZONTAL);
			
			wxString estadoPago = t.estaPagado() ? "Pagado" : "No pagado";
			
			wxString info = "Hora: " + t.VerHora()
				+ " | Paciente: " + c.obtenerNombrePaciente(t.verIdPaciente())
				+ " |Odontologo: " + c.obtenerNombreOdontologo (t.VerIdOdontologo())
				+ " |Estado: " + estadoPago;
			
			wxStaticText *lbl = new wxStaticText(panel, wxID_ANY, info);
			fila->Add(lbl, 1, wxALL, 5);
			
			wxButton *btnCancelar = new wxButton(panel, wxID_ANY, "Cancelar");
			
			int idTurno = t.VerId();
			
			btnCancelar->Bind(wxEVT_BUTTON,[this,idTurno](wxCommandEvent&){
				Clinica &c2 = wxGetApp().GetClinica();
				c2.cancelarTurno(idTurno);
				this->RefrescarAgenda();
			});
			
			fila->Add(btnCancelar, 0, wxALL, 5);
			
			wxButton *btnCobrar = new wxButton(panel, wxID_ANY, "Atender / Cobrar");
			
			btnCobrar->Bind(wxEVT_BUTTON, [this, idTurno](wxCommandEvent&){
				
				Clinica &c2 = wxGetApp().GetClinica();
				
				// 1. PEDIR TRATAMIENTO
				wxTextEntryDialog dlg1(nullptr, "Ingrese el tratamiento:");
				if(dlg1.ShowModal() != wxID_OK) return;
				
				wxString tratamiento = dlg1.GetValue();
				
				// 2. PEDIR COSTO
				wxTextEntryDialog dlg2(nullptr, "Ingrese el costo:");
				if(dlg2.ShowModal() != wxID_OK) return;
				
				double costo;
				if(!dlg2.GetValue().ToDouble(&costo)){
					wxMessageBox("Costo inválido");
					return;
				}
				
				// 3. GUARDAR EN EL TURNO
				c2.cobrarTurno(idTurno, tratamiento.ToStdString(), costo);
				
				this->RefrescarAgenda();
			});
			
			fila->Add(btnCobrar, 0, wxALL, 5);
			sizer->Add(fila, 0, wxEXPAND);
		}
	}
	
	panel->SetSizer(sizer);
	CambiarPanel(panel);
}

void PanelContenedorHijo::OnVerRecaudacion(wxCommandEvent&event){
	MostrarPanelRecaudacion();
}

void PanelContenedorHijo::MostrarPanelRecaudacion(){
	wxPanel *panel = new wxPanel(PanelDerecho);
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	
	Clinica &c = wxGetApp().GetClinica();
	
	wxTextEntryDialog dlg(this,"Ingrese mes","Recaudacion mensual");
	
	if(dlg.ShowModal() != wxID_OK) return;
	
	wxString mesWx = dlg.GetValue();
	string mes = mesWx.ToStdString();
	
	double total = c.calcularRecaudacionMensual(mes);
	
	double montoOdontologo = total * Clinica::PORC_ODONTOLOGO;
	double montoClinica = total * Clinica::PORC_CLINICA;
	
	wxStaticText *txtTotal = new wxStaticText(panel,wxID_ANY,"Total recaudado: $" + wxString::Format("%.2f",total));
    wxStaticText *txtOdonto= new wxStaticText(panel,wxID_ANY,"Odontologo (" + wxString :: Format("%.0f%%", Clinica::PORC_ODONTOLOGO*100)+"): $"+ wxString::Format("%.2f",montoOdontologo));
	wxStaticText *txtClinica= new wxStaticText(panel,wxID_ANY,"Clinica (" + wxString :: Format("%.0f%%", Clinica::PORC_CLINICA*100)+"): $"+ wxString::Format("%.2f",montoClinica));

    sizer->Add(txtTotal, 0 , wxALL,10);
	sizer->Add(txtOdonto, 0, wxALL,10);
	sizer->Add(txtClinica,0,wxALL,10);
	
	panel->SetSizer(sizer);
	
	CambiarPanel(panel);

}
PanelContenedorHijo::~PanelContenedorHijo(){}




