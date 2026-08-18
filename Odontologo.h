#ifndef ODONTOLOGO_H
#define ODONTOLOGO_H
#include <string>
#include <fstream>
#include <vector>
using namespace std;


class Odontologo{
private:
	int id;
	string nombre;
	string especialidad;
	vector<string> dias;
	string horaInicio;
	string horaFin;
	
public:
	Odontologo();
	Odontologo(int id,const string &nombre,const string &especialidad,const vector<string> &dias, const string &horaInicio,const string &horaFin);
	
	int Verid()const;
	string Vernombre()const;
	string Verespecialidad()const;
	
	vector<string> VerDias() const;
	string VerHoraInicio() const;
	string VerHoraFin() const;
	
	void AsignarNombre(const string &n);
	void AsignarEspecialidad(const string &e);
	void AsignarDias(const vector<string> &d);
	void AsignarHoraInicio(const string &h);
	void AsignarHoraFin(const string &h);
	
	void Setespecialidad(const std::string &especialidad);
	void Setnombre(const string &nombre);
	
	static void guardarListaCompleta(const vector<Odontologo> &lista);
	
	void EscribirBinario(ofstream &out) const;
	void LeerBinario(ifstream &in);
};
#endif



