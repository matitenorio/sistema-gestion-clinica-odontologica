#include "Turno.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

Turno::Turno(): id(0),idPaciente(0),idOdontologo(0),fecha(""),hora(""),cancelado(false),atendido(false),pagado(false){}

Turno::Turno(int id, int idPaciente, int idOdontologo, const string &fecha, const string &hora)
	: id(id),idPaciente(idPaciente),idOdontologo(idOdontologo),fecha(fecha),hora(hora),cancelado(false),atendido(false),pagado(false),tratamiento(""),costo(0){}

int Turno::VerId() const{
	return id;
}

int Turno::verIdPaciente() const{
	return idPaciente;
}

int Turno::VerIdOdontologo() const{
	return idOdontologo;
}

string Turno::VerFecha()const{
	return fecha;
}

string Turno::VerHora() const{
	return hora;
}

bool Turno::estaCancelado() const{
	return cancelado;
}

bool Turno::estaAtendido() const{
	return atendido;
}

void Turno::cancelar(){
	cancelado = true;
}

void Turno::marcarAtendido(){
	if(!cancelado){
		atendido = true;	
	}
}

bool Turno::estaPagado() const{
	return pagado;
}

void Turno::marcarPagado(){
	pagado = true;
}

string Turno::VerTratamiento() const{
	return tratamiento;
}

float Turno::VerCosto() const{
	return costo;
}

void Turno::AsignarTratamiento(const string &t){
	tratamiento = t;
}

void Turno::AsignarCosto(float c){
	costo = c;
}
///FUNCION PARA GUARDAR EL ARCHIVO EN BINARIO
bool Turno::GuardarEnArchivo() const{
	ofstream file("turnos.dat",ios::binary|ios::app);
	if(!file) return false;
	EscribirBinario(file);
	return true;
}

void Turno::guardarListaCompleta(const vector<Turno> &lista){
	ofstream file("turnos.dat",ios::binary|ios::trunc);
	
	for(const auto &t : lista){
		t.EscribirBinario(file);
	}
}
///VECTOR PARA LEER EL ARCHIVO EN BINARIO
vector<Turno> Turno::LeerDesdeArchivo(){
	vector<Turno> lista;
	ifstream file("turnos.dat",ios::binary);
	if(!file) return lista;
	
	while(true){
		Turno t;
		t.LeerBinario(file);
		if(file.eof() || file.fail()) break;
		lista.push_back(t);
	}
	return lista;
}

///ESCRIBIMOS TURNO EN BINARIO
void Turno::EscribirBinario(ofstream &out) const{
	out.write(reinterpret_cast<const char*>(&id),sizeof(id));
	out.write(reinterpret_cast<const char*>(&idPaciente),sizeof(idPaciente));
	out.write(reinterpret_cast<const char*>(&idOdontologo),sizeof(idOdontologo));

    size_t tamFecha = fecha.size();
	out.write(reinterpret_cast<const char*>(&tamFecha),sizeof(tamFecha));
	out.write(fecha.c_str(),tamFecha);
	
	size_t tamHora = hora.size();
	out.write(reinterpret_cast<const char*>(&tamHora),sizeof(tamHora));
	out.write(hora.c_str(),tamHora);
	
	out.write(reinterpret_cast<const char*> (&cancelado),sizeof(cancelado));
	out.write(reinterpret_cast<const char*> (&atendido),sizeof(atendido));
	out.write(reinterpret_cast<const char*> (&pagado),sizeof(pagado));
}

///LEEMOS TURNO EN BINARIO
void Turno::LeerBinario(ifstream &in){
	in.read(reinterpret_cast<char*>(&id),sizeof(id));
	in.read(reinterpret_cast<char*>(&idPaciente),sizeof(idPaciente));
	in.read(reinterpret_cast<char*>(&idOdontologo),sizeof(idOdontologo));

    
	size_t tamFecha;
	in.read(reinterpret_cast< char*>(&tamFecha),sizeof(tamFecha));
	fecha.resize(tamFecha);
	in.read(&fecha[0],tamFecha);
	
	size_t tamHora;
	in.read(reinterpret_cast< char*>(&tamHora),sizeof(tamHora));
	hora.resize(tamHora);
	in.read(&hora[0],tamHora);
	
	in.read(reinterpret_cast<char*> (&cancelado),sizeof(cancelado));
	in.read(reinterpret_cast<char*> (&atendido),sizeof(atendido));
    in.read(reinterpret_cast<char*> (&pagado),sizeof(pagado));
}
