#ifndef TRATAMIENTO_H
#define TRATAMIENTO_H
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Tratamiento{
private:
	int id;
	int idPaciente;
	int idTurno;
	string descripcion;
	double costo;
	bool pagado;
	
public:
	Tratamiento();
	
	Tratamiento(int id, int idPaciente, int idTurno, const string &descripcion, double costo,bool pagado);
	
	int VerId() const;
	int VerIdPaciente() const;
	int VerIdTurno() const;
	string VerDescripcion() const;
	double VerCosto() const;
	bool estaPagado() const;
	
	void marcarPagado();
	
	void EscribirBinario(ofstream &out) const;
	void LeerBinario(ifstream &in);
	
	bool guardarEnArchivo() const;
	static vector<Tratamiento> leerDesdeArchivo();
};

#endif
