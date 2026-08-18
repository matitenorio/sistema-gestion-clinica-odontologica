#ifndef PACIENTE_H
#define PACIENTE_H
#include <string>
#include <vector>
#include <fstream>
using namespace std;


class Paciente{
private:
	int id;
	string nombre;
	int dni;
	string telefono;
	string mail;
	string ObraSocial;
	
public:
	Paciente();
	Paciente(int id,const string &nombre, int dni,  string telefono, const string &mail, string ObraSocial);
	
	int Verid()const;
	string Vernombre()const;
	int Verdni()const;
	string Vertelefono()const;
	string Vermail()const;
	string VerObraSocial() const;
	
	void SetNombre(const string &nombre);
	void SetTelefono(const string &telefono);
	void setMail(const string &mail);
	
	void AsignarNombre(const string &nombre);
	void AsignarDni(int dni);
	void AsignarTelefono(const string &telefono);
	void AsignarMail(const string &mail);
	void AsignarObraSocial(const string &os);
	
	void EscribirBinario(ofstream &out) const;
	void LeerBinario(ifstream &in);
	
	static vector<Paciente> leerDesdeArchivo();
	bool guardarEnArchivo() const;
	
	static void guardarListaCompleta(const vector<Paciente> &lista);
};

#endif
