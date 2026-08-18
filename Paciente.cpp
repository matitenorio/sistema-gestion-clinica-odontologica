#include "Paciente.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

Paciente::Paciente() : id(0),nombre(""), dni(0), telefono(""),mail(""), ObraSocial(" "){}

Paciente::Paciente(int id, const string &nombre, int dni, string telefono, const string &mail, string ObraSocial)
	      : id(id), nombre(nombre), dni(dni), telefono(telefono), mail(mail), ObraSocial(ObraSocial){}


int Paciente::Verid() const{
	return id;
}

string Paciente::Vernombre()const{
	return nombre;
}

int Paciente::Verdni()const{
	return dni;
}

string Paciente::Vertelefono()const{
	return telefono;
}

string Paciente::Vermail()const{
	return mail;
}

string Paciente::VerObraSocial() const{
	return ObraSocial;
}


void Paciente::SetNombre(const string &nombre){
	this ->nombre = nombre;
}
void Paciente::SetTelefono(const string &telefono){
	this->telefono = telefono;
}

void Paciente::setMail(const string &mail){
	this->mail = mail;
}

void Paciente::AsignarNombre(const string &nombre){
	this-> nombre = nombre;
}

void Paciente::AsignarDni(int dni){
	this-> dni = dni;
}

void Paciente::AsignarTelefono(const string &telefono){
	this-> telefono = telefono;
}

void Paciente::AsignarMail(const string &mail){
	this-> mail = mail;
}

void Paciente:: AsignarObraSocial(const string &os){
	this->ObraSocial=os;
}
///FUNCION PARA GUARDAR ARCHIVO BINARIO
bool Paciente::guardarEnArchivo() const{
	ofstream file("pacientes.dat",ios::binary|ios::app);
	if(!file) return false;
	
	EscribirBinario(file);
	return true;
}

///VECTOR PARA LEER DESDE BINARIO
vector<Paciente> Paciente::leerDesdeArchivo(){
	vector<Paciente> lista;
	
	ifstream file("pacientes.dat",ios::binary);
	if(!file) return lista;
	
	while(true){
		Paciente p;
		p.LeerBinario(file);
		if(file.eof()|| file.fail()) break;
		lista.push_back(p);
	}
	
	return lista;
}
	
///ESCRIBIR EN BINARIO A PACIENTE
void Paciente::EscribirBinario(ofstream &out) const{
	out.write(reinterpret_cast<const char*>(&id),sizeof(id));
	out.write(reinterpret_cast<const char*>(&dni),sizeof(dni));
	
	size_t tamTelefono = telefono.size();
	out.write(reinterpret_cast<const char*>(&tamTelefono),sizeof(tamTelefono));
	out.write(telefono.c_str(),tamTelefono);
    
	size_t tamNombre = nombre.size();
	out.write(reinterpret_cast<const char*>(&tamNombre),sizeof(tamNombre));
	out.write(nombre.c_str(),tamNombre);
	
	size_t tamMail = mail.size();
	out.write(reinterpret_cast<const char*>(&tamMail),sizeof(tamMail));
	out.write(mail.c_str(),tamMail);
    
	size_t tamObraSocial = ObraSocial.size();
	out.write(reinterpret_cast<const char*>(&tamObraSocial),sizeof(tamObraSocial));
    out.write(ObraSocial.c_str(),tamObraSocial);
}

///LEER EN BINARIO A PACIENTE
void Paciente::LeerBinario(ifstream &in){
	in.read(reinterpret_cast<char*>(&id),sizeof(id));
	in.read(reinterpret_cast<char*>(&dni),sizeof(dni));
	
	size_t tamTelefono;
	in.read(reinterpret_cast<char*>(&tamTelefono),sizeof(tamTelefono));
	telefono.resize(tamTelefono);
	in.read(&telefono[0],tamTelefono);
	
	size_t tamNombre;
	in.read(reinterpret_cast<char*>(&tamNombre),sizeof(tamNombre));
	nombre.resize(tamNombre);
	in.read(&nombre[0],tamNombre);
	
	size_t tamMail;
	in.read(reinterpret_cast<char*>(&tamMail),sizeof(tamMail));
	mail.resize(tamMail);
	in.read(&mail[0],tamMail);
	
	size_t tamObraSocial;
	in.read(reinterpret_cast<char*>(&tamObraSocial),sizeof(tamObraSocial));
    ObraSocial.resize(tamObraSocial);
	in.read(&ObraSocial[0],tamObraSocial);

}

void Paciente::guardarListaCompleta(const vector<Paciente> &lista){
	ofstream file("pacientes.dat",ios::binary|ios::trunc);
	if(!file)return;
	
	for(const auto &p : lista){
		p.EscribirBinario(file);
	}
}
