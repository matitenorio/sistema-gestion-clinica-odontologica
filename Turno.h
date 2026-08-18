#ifndef TURNO_H
#define TURNO_H
#include <string>
#include <vector>
using namespace std;


class Turno{
private:
	int id;
	int idPaciente;
	int idOdontologo;
	string fecha;
	string hora;
	bool cancelado;
	bool atendido;
	bool pagado;
	string tratamiento;
	float costo;
	
public:
	
	Turno();
	
	Turno(int id, int idPaciente,int idOdontologo,const string &fecha,const string &hora);
	
	int VerId() const;
	int verIdPaciente() const;
	int VerIdOdontologo() const;
	string VerFecha()const;
	string VerHora() const;
	string VerTratamiento() const;
	float VerCosto() const;
	
	bool estaCancelado() const;
	bool estaAtendido() const;
	bool estaPagado() const;
	void marcarPagado();
	void AsignarTratamiento(const string &t);
	void AsignarCosto(float c);
	
	void cancelar();
	void marcarAtendido();
	
	static void guardarListaCompleta(const vector<Turno> &lista);
	void EscribirBinario(ofstream &out) const;
	void LeerBinario(ifstream &in);
	
	bool GuardarEnArchivo() const;
	static vector<Turno> LeerDesdeArchivo();
};

#endif
