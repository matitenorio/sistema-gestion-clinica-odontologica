# Sistema de Gestión de Clínica Odontológica

Aplicación de escritorio desarrollada individualmente en **C++** como proyecto académico. El sistema permite gestionar pacientes, odontólogos, turnos, tratamientos y recaudación mediante una interfaz gráfica.

> **Estado:** proyecto académico en proceso de preparación para portfolio.

## Tecnologías y conceptos

- C++
- Programación Orientada a Objetos
- Programación estructurada
- STL (`std::vector`)
- Persistencia de datos mediante archivos binarios
- wxWidgets
- Manejo de eventos e interfaz gráfica
- Separación entre archivos `.h` y `.cpp`

## Funcionalidades

- Registro y consulta de pacientes
- Registro y gestión de odontólogos
- Asignación y cancelación de turnos
- Gestión de agenda por fecha
- Registro de tratamientos y cobros
- Consulta de recaudación mensual
- Persistencia de información entre ejecuciones

## Estructura

El proyecto mantiene la estructura original utilizada durante su desarrollo académico. Las clases principales incluyen:

- `Paciente`
- `Odontologo`
- `Turno`
- `Tratamiento`
- `Clinica`

La interfaz gráfica utiliza componentes generados con wxFormBuilder/wxWidgets.

## Datos de prueba y privacidad

Los archivos `.dat` utilizados por la aplicación para persistir información **no se incluyen en este repositorio**. Pueden contener datos introducidos durante las pruebas locales.

El repositorio utiliza `.gitignore` para evitar publicar accidentalmente archivos de persistencia.

## Ejecución

La aplicación fue desarrollada utilizando **C++ y wxWidgets**. Los archivos de proyecto originales se conservan para facilitar la apertura y compilación en el entorno utilizado durante el desarrollo.

La configuración exacta de compilación se documentará y ajustará antes de considerar el repositorio como versión final de portfolio.

## Mejoras futuras

- Incorporar validaciones más robustas de datos de entrada.
- Mejorar el sistema de autenticación.
- Reemplazar la persistencia en archivos binarios por una base de datos.
- Mejorar la arquitectura y separación de responsabilidades.
- Incorporar pruebas automatizadas.
- Mejorar la documentación y experiencia de instalación.
