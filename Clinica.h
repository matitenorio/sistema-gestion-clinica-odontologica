#ifndef CLINICA_H
#define CLINICA_H
#include <vector>
#include "Paciente.h"
#include "Odontologo.h"
#include "Turno.h"
#include "Tratamiento.h"
#include <string>
using namespace std;

class Clinica{
private:
	vector<Paciente> pacientes;
	vector<Odontologo> odontologos;
	vector<Turno> turnos;
	vector<Tratamiento> tratamientos;
	
	int generarIdPaciente() const;
	int generarIdOdontologo() const;
	int generarIdTurno() const;
	int generarIdTratamiento() const;
	
	bool odontologoDisponible(int idOdontologo, const string &fecha, const string &hora, const string &diaNombre) const;
	void cargarOdontologos();
	/*void guardarTurnosEnArchivo() const;*/
	
	double obtenerCostoPorTipo(const string &tipo) const;
	
	
public:
	
	Clinica();
	
	vector<Paciente> &obtenerPacientesEditable();
	
	string obtenerNombrePaciente(int idPaciente) const;
	string obtenerDniPaciente(int idPaciente) const;
	string obtenerNombreOdontologo(int idOdontologo) const;
	
	//Pacientes
	void registrarPaciente(const string &nombre, int dni, string telefono, const string &mail, string ObraSocial);
	Paciente* buscarPacientePorDni(int dni);
	void listarPacientes() const;
	const vector<Paciente>& obtenerPacientes() const { return pacientes; }
	
	//Odontologos
	void registrarOdontologo(const string &nombre, const string &especialidad,const vector<string> &dias, const string &horaInicio, const string &horaFin);
	void listarOdontologos() const;
	const vector<Odontologo>& obtenerOdontologos() const { return odontologos; }
	vector<Odontologo> &obtenerOdontologosEditable();
	
	//Turnos
	bool asignarTurno(int idPaciente, int idOdontologo, const string &fecha, const string &hora, const string &diaNombre);
	void cancelarTurno(int idTurno);
	void marcarTurnoAtendido(int idTurno);
	void listarTurnosPorDia(const string &fecha) const;
	void listarTurnosPorPaciente(int idPaciente) const;
	const vector<Turno>& obtenerTurnos() const { return turnos; }
	void marcarTurnoPagado(int idTurno);
	void cobrarTurno(int idTurno, const string &tratamiento, float costo);
	
	//tratamientos
	void mostrarTratamientosPendientes() const;
	void registrarTratamiento(int idPaciente,int idTurno, const string &tipo);
	float calcularTotalRecaudado() const;
	
	float calcularRecaudacionMensual(const string &mes);
	static constexpr double PORC_ODONTOLOGO = 0.6;
	static constexpr double PORC_CLINICA = 0.4;
};

#endif
