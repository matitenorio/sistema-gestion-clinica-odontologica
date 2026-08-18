#include "Clinica.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <wx/msgdlg.h>
#include <fstream>
using namespace std;


//Constructor:
Clinica::Clinica(){
	pacientes = Paciente::leerDesdeArchivo();
	turnos = Turno::LeerDesdeArchivo();
	tratamientos = Tratamiento::leerDesdeArchivo();
	
	cargarOdontologos();

}

vector<Paciente> &Clinica :: obtenerPacientesEditable(){
	return pacientes;
}
//Generadores:
int Clinica::generarIdPaciente() const{
	int maxId = 0;
	for(const auto &p: pacientes){
		if(p.Verid() > maxId){
			maxId = p.Verid();
		}
	}
	return maxId + 1;
}


int Clinica::generarIdOdontologo() const{
	int maxId = 0;
	for(const auto &o: odontologos){
		if(o.Verid() > maxId){
			maxId = o.Verid();
		}
	}
	return maxId+1;
}


int Clinica::generarIdTurno() const{
	int maxId = 0;
	for(const auto &t : turnos){
		if(t.VerId() > maxId){
			maxId = t.VerId();
		}
	}
	return maxId + 1;
}


int Clinica::generarIdTratamiento() const{
	int maxId=0;
	
	for(const auto &tr: tratamientos){
		if(tr.VerId() > maxId){
			maxId = tr.VerId();
		}
	}
	
	return maxId + 1;
}



//Odontologos

void Clinica::cargarOdontologos() {
	ifstream archivo("odontologos.dat", ios::binary);
	if (!archivo) return;
	
	while(true){
		Odontologo o;
		o.LeerBinario(archivo);
		if(archivo.eof() || archivo.fail()) break;
		odontologos.push_back(o);
	}
	archivo.close();
}

void Clinica::registrarOdontologo(const string &nombre, const string &especialidad, const vector<string> &dias, const string &horaInicio, const string &horaFin) {
	
	int id = generarIdOdontologo();
	Odontologo o(id, nombre, especialidad, dias, horaInicio, horaFin);
	
	odontologos.push_back(o);
	
	ofstream archivo("odontologos.dat", ios::binary | ios::app);
	if (archivo.is_open()) {
		o.EscribirBinario(archivo);
		archivo.close();
	}
}

void Clinica::listarOdontologos() const {
	if (odontologos.empty()) {
		cout << "No hay odontologos registrados." << endl;
		return;
	}
	for (const auto &o : odontologos) {
		cout << "ID: " << o.Verid() 
			<< " | Nombre: " << o.Vernombre() 
			<< " | Especialidad: " << o.Verespecialidad() << endl;
	}
}

///NOMBRE DEL ODONTOLOGO DANDO SU ID
string Clinica::obtenerNombreOdontologo(int idOdontologo) const{
	for(const auto &o: odontologos){
		if(o.Verid() == idOdontologo){
			return o.Vernombre();
		}
	}
	return "Desconocido";
}

vector<Odontologo> &Clinica:: obtenerOdontologosEditable(){
	return odontologos;
}
//Pacientes:

///REGISTRAR PACIENTE
void Clinica::registrarPaciente(const string &nombre, int dni, string telefono, const string &mail, string ObraSocial){
	
	for(const auto &p : pacientes){
		if(p.Verdni() ==dni){
			cout << "DNI ya registrado" << endl;
			return;
		}
	}
	
	int id = generarIdPaciente();
	
	Paciente p(id, nombre, dni, telefono, mail, ObraSocial);
	pacientes.push_back(p);
	p.guardarEnArchivo();
}

///BUSCAR UN PACIENTE POR SU DNI
Paciente* Clinica::buscarPacientePorDni(int dni){
	for(auto &p: pacientes){
		if(p.Verdni() == dni){
			return &p;
		}
	}
	return nullptr;
}


///CREAR LISTA DE PACIENTES
void Clinica::listarPacientes() const{
	for(const auto &p: pacientes){
		cout << "ID: " << p.Verid()
			<< ",Nombre: " << p.Vernombre()
			<<",DNI: " << p.Verdni()
			<<",TELEFONO: " << p.Vertelefono()
			<<",MAIL: " << p.Vermail() << endl;
	}
}

///OBTENER EL NOMBRE DE UN PACIENTE DANDO SU ID
string Clinica::obtenerNombrePaciente(int idPaciente) const{
	for(const auto &p: pacientes){
		if(p.Verid() == idPaciente){
			return p.Vernombre();
		}
	}
	return "Desconocido";
}

///OBTENER EL DNI DEL PACIENTE DANDO SU ID
string Clinica::obtenerDniPaciente(int idPaciente) const{
	for(const auto &p : pacientes){
		if(p.Verid() == idPaciente){
			return to_string(p.Verdni());
		}
	}
	return "Desconocido";
}



//Turnos:
///ODONTOLOGO DISPONIBLE
bool Clinica::odontologoDisponible(int idOdontologo, const string &fecha, const string &hora, const string &diaNombre) const {
	const Odontologo *odonto = nullptr;
	for(const auto &o : odontologos) {
		if(o.Verid() == idOdontologo) { odonto = &o; break; }
	}
	
	if(!odonto) {
		wxMessageBox("Error: Odontologo no encontrado");
		return false;
	}
	
	bool trabajaEseDia = false;
	for(auto d : odonto->VerDias()) {
		// Usamos wxString para limpiar espacios (Trim) y pasar todo a Mayusculas (Upper)
		wxString diaGuardado = wxString(d).Trim(true).Trim(false).Upper();
		wxString diaCalendario = wxString(diaNombre).Trim(true).Trim(false).Upper();
		
		if(diaGuardado == diaCalendario) { 
			trabajaEseDia = true;
			break;
		}
	}
	
	if(!trabajaEseDia) {
		wxMessageBox("El medico no trabaja los " + diaNombre); // Te avisará si el problema es el día
		return false;
	}
	
	if(hora < odonto->VerHoraInicio() || hora > odonto->VerHoraFin()){
		wxMessageBox("Hora " + hora + " fuera de rango (" + odonto->VerHoraInicio() + " - " + odonto->VerHoraFin() + ")");
		return false;
	}
	
	return true; 
}



///ASIGNAR UN TURNO DANDO EL ID DEL PACIENTE DEL ODONTOLOGO LA FECHA Y LA HORA
bool Clinica::asignarTurno(int idPaciente, int idOdontologo, const string &fecha, const string &hora, const string &diaNombre) {
	if (!odontologoDisponible(idOdontologo, fecha, hora, diaNombre)) {
		return false;
	}
	
	for(const auto &t : turnos){
		if(t.verIdPaciente() == idPaciente && t.VerFecha() == fecha && t.VerHora() == hora){
			cout << "El Paciente ya tiene un turno en esa fecha y hora " << endl;
			return false;
		}
	}
	int id = generarIdTurno();
	Turno t(id, idPaciente, idOdontologo, fecha, hora);
	turnos.push_back(t);
	t.GuardarEnArchivo();
	return true;
}


///CANCELAR UN TURNO DANDO ID DEL TURNO
void Clinica::cancelarTurno(int idTurno) {
	for (auto &t : turnos) {
		if (t.VerId() == idTurno) {
			t.cancelar();
			break;
		}
	}
	Turno::guardarListaCompleta(turnos);
}

///MARCAR UN TURNO COMO ATENDDIDO DANDO SU ID
void Clinica::marcarTurnoAtendido(int idTurno) {
	for (auto &t : turnos) {
		if (t.VerId() == idTurno) {
			t.marcarAtendido();
			t.GuardarEnArchivo();
			break;
		}
	}
	Turno::guardarListaCompleta(turnos);
}

///LISTAR LOS TURNOS POR  DIA DANDO UNA FECHA ESPECIAL
void Clinica::listarTurnosPorDia(const string &fecha) const{
	
	vector<Turno> turnosDelDia;
	
	for(const auto &t : turnos){
		if(t.VerFecha() == fecha){
			turnosDelDia.push_back(t);
		}
	}
	
	if(turnosDelDia.empty()){
		cout << "No hay turnos para esa fecha" << endl;
		return;
	}
	
	sort(turnosDelDia.begin(), turnosDelDia.end(),[](const Turno &a, const Turno &b){
		return a.VerHora() < b.VerHora();
	});
	
	for(const auto &t : turnosDelDia){
		cout << "ID Turno: " << t.VerId()
			<<", Hora: " << t.VerHora()
			<<", Paciente: " << obtenerNombrePaciente(t.verIdPaciente())
			<<", DNI: " << obtenerDniPaciente(t.verIdPaciente())
			<<", Odontologo: " << obtenerNombreOdontologo(t.VerIdOdontologo())
			<<", Cancelado: " << (t.estaCancelado() ? "si" : "no")
			<<", Atendido: " << (t.estaAtendido() ? "si" : "no")
			<< endl;
		
	}
}


///LISTAR TURNOS POR PACIENTE DANDO EL ID DEL PACIENTE
void Clinica::listarTurnosPorPaciente(int idPaciente) const{
	
	vector<Turno> turnosPaciente;
	
	for(const auto &t : turnos){
		if(t.verIdPaciente() == idPaciente){
		 turnosPaciente.push_back(t);
	    }
    }

	if(turnosPaciente.empty()){
		cout << "El paciente no tiene turnos." << endl;
		return;
	}
	
	sort(turnosPaciente.begin(), turnosPaciente.end(),[](const Turno &a, const Turno &b){
		return a.VerFecha() == b.VerFecha()
				? a.VerHora() < b.VerHora()
				: a.VerFecha() < b.VerFecha();
	});
	
	for(const auto &t : turnosPaciente){
		
		cout << "ID Turno: " << t.VerId()
			<< ", Fecha: " << t.VerFecha()
			<< ", Hora: " << t.VerHora()
			<< ", Paciente: " << obtenerNombrePaciente(idPaciente)
			<< " (DNI: " << obtenerDniPaciente(idPaciente) << ")"
			<< ", Odontologo: " << obtenerNombreOdontologo(t.VerIdOdontologo())
			<< ", Cancelado: " << (t.estaCancelado() ? "Si" : "No")
			<< ", Atendido: " << (t.estaAtendido() ? "Si" : "No")
			<< endl;
	}
}

void Clinica::marcarTurnoPagado(int idTurno){
	for(auto &t : turnos){
		if(t.VerId() == idTurno){
			t.marcarPagado();
			break;
		}
	}
	Turno::guardarListaCompleta(turnos);
}
//Tratamiento

void Clinica::mostrarTratamientosPendientes() const {
	bool hayPendientes = false;
	cout << "--- Tratamientos Pendientes de Pago ---" << endl;
	for (const auto &tr : tratamientos) {
		if (!tr.estaPagado()) {
			cout << "ID Tratamiento: " << tr.VerId()
				<< " | Paciente: " << obtenerNombrePaciente(tr.VerIdPaciente())
				<< " | Costo: $" << tr.VerCosto() 
				<< " | Desc: " << tr.VerDescripcion() << endl;
			hayPendientes = true;
		}
	}
	if (!hayPendientes) cout << "No hay pagos pendientes." << endl;
}


double Clinica::obtenerCostoPorTipo(const string &tipo) const{
	
	if(tipo == "consulta") return 5000;
	if(tipo == "arreglo") return 15000;
	if(tipo == "conducto") return 30000;
	if(tipo == "ortodoncia") return 80000;
	if(tipo == "implante") return 120000;
	
	return 0;
}


void Clinica::registrarTratamiento(int idPaciente,int idTurno,const string &tipo){
	Paciente* p = nullptr;
	
	for(auto &pac : pacientes){
		if(pac.Verid() == idPaciente){
			p = &pac;
			break;
		}
	}
	
	if(!p){
		cout << "Paciente no encontrado\n";
		return;
	}
	
	double costo = obtenerCostoPorTipo(tipo);
	bool pagado = false;
	
	if(p->VerObraSocial().empty()){
		cout << "Paciente con obra social.\n";
		cout << "Se factura $" << costo << " a la obra social.\n";
		pagado = true;
	}
	else{
		cout << "Paciente particular.\n";
		cout << "Debe pagar $" << costo << endl;
		pagado = true;
	}
	
	int nuevoId = generarIdTratamiento();
	
	Tratamiento nuevo(nuevoId, idPaciente, idTurno, tipo, costo, pagado);
	
	tratamientos.push_back(nuevo);
	nuevo.guardarEnArchivo();
	
	cout << "Tratamiento registrado correctamente.\n";
}

float Clinica::calcularRecaudacionMensual(const string &mes) {
	float total = 0;
	
	for(const auto &t : turnos){
		if(t.estaPagado() && t.VerFecha().substr(3,2)==mes){
			total+=t.VerCosto();
		}
	}
	return total;
}

void Clinica::cobrarTurno (int idTurno, const string &tratamiento, float costo){
	for(auto &t : turnos){
		if(t.VerId()== idTurno){
			t.AsignarTratamiento(tratamiento);
			t.AsignarCosto(costo);
			t.marcarPagado();
			break;
		}
	}
	Turno::guardarListaCompleta(turnos);
}
