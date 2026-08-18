#include <fstream>
#include "Odontologo.h"
#include <string>
using namespace std;

Odontologo::Odontologo(): id(0), nombre(""),especialidad(""), dias(), horaInicio(""),horaFin(""){}
Odontologo::Odontologo(int id,const string &nombre,const string &especialidad, const vector<string> &dias, const string &horaInicio, const string &horaFin)
	:id(id),nombre(nombre),especialidad(especialidad), dias(dias), horaInicio(horaInicio),horaFin(horaFin){}

int Odontologo::Verid()const{
	return id;
}

string Odontologo::Vernombre()const{
	return nombre;
}

string Odontologo::Verespecialidad()const{
	return especialidad;
}

vector<string> Odontologo :: VerDias() const{
	return dias;
}

string Odontologo::VerHoraInicio() const{
	return horaInicio;
}

string Odontologo::VerHoraFin() const{
	return horaFin;
}

void Odontologo::Setnombre(const string &nombre){
	this ->nombre = nombre;
}
void Odontologo::Setespecialidad(const string &especialidad){
	this->especialidad = especialidad;
}

void Odontologo::AsignarNombre(const string &n){
	nombre = n;
}

void Odontologo::AsignarEspecialidad(const string &e){
	especialidad = e;
}

void Odontologo::AsignarDias(const vector<string> &d){
	dias = d;
}

void Odontologo::AsignarHoraInicio(const string &h){
	horaInicio = h;
}

void Odontologo::AsignarHoraFin(const string &h){
	horaFin = h;
}

void Odontologo::guardarListaCompleta (const vector<Odontologo> &lista){
	
	ofstream out ("odontologos.dat",ios::binary|ios::trunc);
	
	for(const auto &o:lista){
		o.EscribirBinario(out);
	}
}
///ESCRIBIMOS ODONTOLOGO EN BINARIO
void Odontologo::EscribirBinario(ofstream &out) const {
	
	out.write(reinterpret_cast<const char*>(&id), sizeof(id));
	
	size_t tamNombre = nombre.size();
	out.write(reinterpret_cast<const char*>(&tamNombre), sizeof(tamNombre));
	out.write(nombre.c_str(), tamNombre);
	
	size_t tamEsp = especialidad.size();
	out.write(reinterpret_cast<const char*>(&tamEsp), sizeof(tamEsp));
	out.write(especialidad.c_str(), tamEsp);
	
	size_t cantDias = dias.size();
	out.write(reinterpret_cast<const char*>(&cantDias),sizeof(cantDias));
	
	for(const auto &d : dias){
		size_t tamDia = d.size();
		out.write(reinterpret_cast<const char*>(&tamDia),sizeof(tamDia));
		out.write(d.c_str(),tamDia);
	}
	
	size_t tamHoraInicio = horaInicio.size();
	out.write(reinterpret_cast<const char*>(&tamHoraInicio),sizeof(tamHoraInicio));
	out.write(horaInicio.c_str(),tamHoraInicio);
	
	size_t tamHoraFin = horaFin.size();
	out.write(reinterpret_cast<const char*>(&tamHoraFin),sizeof(tamHoraFin));
	out.write(horaFin.c_str(),tamHoraFin);
}	
	
///LEEMOS ODONTOLOGO EN BINARIO
void Odontologo::LeerBinario(ifstream &in) {

	in.read(reinterpret_cast<char*>(&id), sizeof(id));
	
	size_t tamNombre;
	in.read(reinterpret_cast<char*>(&tamNombre), sizeof(tamNombre));
	nombre.resize(tamNombre);
	in.read(&nombre[0], tamNombre);
	
	size_t tamEsp;
	in.read(reinterpret_cast<char*>(&tamEsp), sizeof(tamEsp));
	especialidad.resize(tamEsp);
	in.read(&especialidad[0], tamEsp);
	
	size_t cantDias;
	in.read(reinterpret_cast<char*>(&cantDias), sizeof(cantDias));
	
	dias.clear();
	
	for (size_t i = 0; i < cantDias; i++) {
		size_t tamDia;
		in.read(reinterpret_cast<char*>(&tamDia), sizeof(tamDia));
		
		string dia;
		dia.resize(tamDia);
		in.read(&dia[0], tamDia);
		
		dias.push_back(dia);
	}
	
	// Leer horaInicio
	size_t tamHoraInicio;
	in.read(reinterpret_cast<char*>(&tamHoraInicio), sizeof(tamHoraInicio));
	horaInicio.resize(tamHoraInicio);
	in.read(&horaInicio[0], tamHoraInicio);
	
	// Leer horaFin
	size_t tamHoraFin;
	in.read(reinterpret_cast<char*>(&tamHoraFin), sizeof(tamHoraFin));
	horaFin.resize(tamHoraFin);
	in.read(&horaFin[0], tamHoraFin);
}


