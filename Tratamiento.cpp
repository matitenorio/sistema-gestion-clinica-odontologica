#include "Tratamiento.h"
#include <string>
#include <fstream>
using namespace std;

Tratamiento::Tratamiento():id(0),idPaciente(0),idTurno(0),descripcion(""),costo(0.0),pagado(false){}

Tratamiento::Tratamiento(int id,int idPaciente,int idTurno,const string &descripcion,double costo,bool pagado)
: id(id),idPaciente(idPaciente),idTurno(idTurno),descripcion(descripcion),costo(costo),pagado(pagado){}

int Tratamiento::VerId()const {
	return id;
}

int Tratamiento::VerIdPaciente()const{
	return idPaciente;
}

int Tratamiento::VerIdTurno()const{
	return idTurno;
}

string Tratamiento::VerDescripcion()const{
	return descripcion;
}

double Tratamiento::VerCosto()const{
	return costo;
}

bool Tratamiento::estaPagado()const{
	return pagado;
}

void Tratamiento::marcarPagado(){
	pagado= true;
}

///ESCRIBIMOS EL ARCHIVO EN BINARIO
void Tratamiento::EscribirBinario(ofstream &out) const {

	out.write(reinterpret_cast<const char*>(&id), sizeof(id));
	out.write(reinterpret_cast<const char*>(&idPaciente), sizeof(idPaciente));
	out.write(reinterpret_cast<const char*>(&idTurno), sizeof(idTurno));
	
	size_t tam = descripcion.size();
	out.write(reinterpret_cast<const char*>(&tam), sizeof(tam));
	out.write(descripcion.c_str(), tam);
	
	out.write(reinterpret_cast<const char*>(&costo), sizeof(costo));
	out.write(reinterpret_cast<const char*>(&pagado), sizeof(pagado));
}

///LEEMOS EL ARCHIVO EN BINARIO
void Tratamiento::LeerBinario(ifstream &in) {
	in.read(reinterpret_cast<char*>(&id), sizeof(id));
	in.read(reinterpret_cast<char*>(&idPaciente), sizeof(idPaciente));
	in.read(reinterpret_cast<char*>(&idTurno), sizeof(idTurno));
	
	size_t tam;
	in.read(reinterpret_cast<char*>(&tam), sizeof(tam));
	descripcion.resize(tam);
	in.read(&descripcion[0], tam);
	
	in.read(reinterpret_cast<char*>(&costo), sizeof(costo));
	in.read(reinterpret_cast<char*>(&pagado), sizeof(pagado));
}

bool Tratamiento::guardarEnArchivo() const{
	ofstream file("tratamientos.dat",ios::binary|ios::app);
	if(!file) return false;
	
	EscribirBinario(file);
	return true;
}

vector<Tratamiento> Tratamiento::leerDesdeArchivo(){
	
	vector<Tratamiento> lista;
	
	ifstream file("tratamientos.dat", ios::binary);
	if(!file) return lista;
	
	while(true){
		Tratamiento t;
		t.LeerBinario(file);
		
		if(file.eof()||file.fail()){
			break;
		}
		
		lista.push_back(t);
	}
	return lista;
}
