#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <map>
#include <string>

using namespace std;

class Clase {
 private:
  int entero;
  float real;
 public:
  Clase();
  Clase(int a, float b);
  Clase(Clase &a);
  ~Clase();
  Clase operator=(Clase & a);
  Clase & operator+(Clase a);
  void desplegar();
};

Clase::Clase(){};

Clase::~Clase(){};

Clase::Clase(int a, float b){
  this->entero = a;
  this->real = b;
}

Clase::Clase(Clase & a){
  this->entero = a.entero;
  this->real = a.real;
}

Clase Clase::operator=(Clase & a){
  this->entero = a.entero;
  this->real = a.real;
}

Clase & Clase::operator+(Clase a){
  this->entero += a.entero;
  this->real += a.real;
}

void Clase::desplegar(){
  cout << "Entero: " << this->entero << "\nReal: " << this->real << "\n";
}

class Publicacion{
  private:
    string titulo;
    int anio;
  public:
    void setAnio(int anio);
    void setTitulo(string titulo);
    int getAnio();
    string getTitulo();
    virtual string getDescripcion();
};

void Publicacion::setAnio(int anio){
  this->anio = anio;
}

void Publicacion::setTitulo(string titulo){
  this->titulo = titulo;
}

int Publicacion::getAnio(){
  return this->anio;
}

string Publicacion::getTitulo(){
  return this->titulo;
}

string Publicacion::getDescripcion(){
  string res = "\nTipo: Publicacion\nTitulo: ";
  res += this->titulo;
  res += "\nAnio: ";
  res += to_string(this->anio);
  res += "\n";
  return res;
}

class Libro: public Publicacion{
  private:
    string editorial;
  public:
    Libro(Publicacion *p);
    void setEditorial(string editorial);
    string getDescripcion();
};

void Libro::setEditorial(string editorial){
  this->editorial = editorial;
}

string Libro::getDescripcion(){
  string res = "\nTipo: Libro\nTitulo: ";
  res += this->getTitulo();
  res += "\nAnio: ";
  res += to_string(this->getAnio());
  res += "\nEditorial: ";
  res += this->editorial;
  res += "\n";
  return res;
}

Libro::Libro(Publicacion *p){
  this->setAnio(p->getAnio()); 
  this->setTitulo(p->getTitulo());
}

class Revista: public Publicacion{
  private:
    int numero;
  public:
    Revista(Publicacion *p);
    void setNumero(int numero);
    string getDescripcion();
};

void Revista::setNumero(int numero){
  this->numero = numero;
}

string Revista::getDescripcion(){
  string res = "\nTipo: Revista\nTitulo: ";
  res += this->getTitulo();
  res += "\nAnio: ";
  res += to_string(this->getAnio());
  res += "\nNumero: ";
  res += to_string(this->numero);
  res += "\n";
  return res;
}

Revista::Revista(Publicacion *p){
  this->setAnio(p->getAnio()); 
  this->setTitulo(p->getTitulo());
}

class Padre{
  public:
    virtual int sumar(int a, int b);
};

class Hijo: public Padre{
  public:
    virtual int sumar(int a, int b);
};

int Padre::sumar(int a, int b){
  return 0;
}

int Hijo::sumar(int a, int b){
  return a+b;
}

void f1(){
  map<float, int> res;
  map<float, int>::iterator it;
  res[1.2] = 1;
  res[0.2] = 2;
  res[3.2] = 3;
  for(it = res.begin(); it != res.end(); it++){
    std::cout << it->first;
    std::cout << "  ";
    std::cout << it->second;
    std::cout << "\n";
  }
}

void f21(){
  Clase c1;
  Clase c2(3,2.54);
  Clase c3=c2;
  c1=c2+c3;
  c1.desplegar();
}

void f25(){
  Publicacion* p = new Publicacion();
  p->setAnio(2001);
  p->setTitulo("PUBLI");
  cout << p->getDescripcion();
  Libro l = p;
  Revista r = p;
  l.setEditorial("EDIT");
  cout << l.getDescripcion();
  r.setNumero(11);
  cout << r.getDescripcion();
}

class Empleado{
  private:
    string nombre;
    string ci; //identificador
  public:
    virtual ~Empleado()=0;
    void setNombre(string nombre);
    void setCi(string ci);
    string getNombre();
    string getCi();
};

class Comun: public Empleado{
  private:
    int sueldo;
  public:
    ~Comun();
    Comun(string nombre, string ci, int sueldo);
    int getSueldo();
};

class Jornalero: public Empleado{
  private:
    int horas;
    int valor;
  public: 
    ~Jornalero();
    Jornalero(string nombre, string ci, int valor);
    void agregarJornal();
    int getHoras();
    int getValor();
};

class IEmpresa{
  public:
    virtual ~IEmpresa(){}
    virtual void agregarJornalero()=0;
    virtual void agregarComun()=0;
    virtual void removerJornalero(string ci)=0;
    virtual void removerComun(string ci)=0;
    virtual bool isJornalero(string ci)=0;
    virtual int getSueldos()=0;
    virtual void agregarJornal(string ci)=0;
};

class Empresa: public IEmpresa{//Singleton
  private:
    static Empresa* instance;
    Empresa();
    map<string,Jornalero*> jornaleros;
    map<string,Comun*> comunes;
  public:
    ~Empresa();
    static Empresa* getInstance();
    void agregarJornalero();
    void agregarComun();
    void removerJornalero(string ci);
    void removerComun(string ci);
    bool isJornalero(string ci);
    int getSueldos();
    void agregarJornal(string ci);
};

class FabricaEmpresa{
  private:
    static FabricaEmpresa* instance;
    FabricaEmpresa();
  public:
    ~FabricaEmpresa();
    static FabricaEmpresa* getInstance();
    IEmpresa* getIEmpresa();
};

Empleado::~Empleado(){}

void Empleado::setCi(string ci){
  ci = ci;
}

void Empleado::setNombre(string nombre){
  nombre = nombre;
}

string Empleado::getCi(){
  return ci;
}

string Empleado::getNombre(){
  return nombre;
}

Comun::Comun(string nombre, string ci, int sueldo){
  this->sueldo = sueldo;
  this->setNombre(nombre);
  this->setCi(ci);
}

Comun::~Comun(){}

int Comun::getSueldo(){
  return this->sueldo;
}

void Jornalero::agregarJornal(){
  int horasJornal;
  cout << "Cuantas horas trabajo en la jornada: ";
  cin >> horasJornal;
  this->horas += horasJornal;
}

Jornalero::Jornalero(string nombre, string ci, int valor){
  this->horas = 0;
  this->valor = valor;
  this->setNombre(nombre);
  this->setCi(ci);
}

Jornalero::~Jornalero(){}

int Jornalero::getHoras(){
  return this->horas;
}

int Jornalero::getValor(){
  return this->valor;
}

Empresa* Empresa::instance = NULL;

Empresa::Empresa(){}

Empresa::~Empresa(){
  for(map<string, Jornalero*>::iterator it = jornaleros.begin(); it != jornaleros.end(); it++){
    Jornalero* del = it->second;
    jornaleros.erase(it);
    delete del;
  }
  for(map<string, Comun*>::iterator it = comunes.begin(); it != comunes.end(); it++){
    Comun* del = it->second;
    comunes.erase(it);
    delete del;
  }
}

Empresa* Empresa::getInstance(){
  if (instance == NULL)
    instance = new Empresa();
  return instance;
}

void Empresa::agregarJornalero(){
  string nombre, ci;
  float valor;
  cout << "Ingrese nombre: ";
  cin >> nombre;
  cout << "Ingrese ci: ";
  cin >> ci;
  cout << "Ingrese valor de la hora: ";
  cin >> valor;
  Jornalero* nuevo = new Jornalero(nombre, ci, valor);
  jornaleros.insert({ci, nuevo});
}

void Empresa::agregarComun(){
  string nombre, ci;
  float sueldo;
  cout << "Ingrese nombre: ";
  cin >> nombre;
  cout << "Ingrese ci: ";
  cin >> ci;
  cout << "Ingrese sueldo: ";
  cin >> sueldo;
  Comun* nuevo = new Comun(nombre, ci, sueldo);
  comunes.insert({ci, nuevo});
}

void Empresa::removerJornalero(string ci){
  map<string,Jornalero*>::iterator it = jornaleros.find(ci);
  Jornalero* del = it->second;
  jornaleros.erase(it);
  delete del;
}

void Empresa::removerComun(string ci){
  map<string,Comun*>::iterator it = comunes.find(ci);
  Comun* del = it->second;
  comunes.erase(it);
  delete del;
}

bool Empresa::isJornalero(string ci){
  return jornaleros.find(ci) != jornaleros.end();
}

int Empresa::getSueldos(){
  int res = 0;
  map<string,Comun*>::iterator it1;
  for(it1 = comunes.begin(); it1 != comunes.end(); it1++)
    res += (it1->second->getSueldo());
  map<string,Jornalero*>::iterator it2;
  for(it2 = jornaleros.begin(); it2 != jornaleros.end(); it2++)
    res += (it2->second->getValor()) * (it2->second->getHoras());
  return res;
}

void Empresa::agregarJornal(string ci){
  Jornalero* jornalero = jornaleros.find(ci)->second;
  jornalero->agregarJornal();
}

FabricaEmpresa* FabricaEmpresa::instance = NULL;

FabricaEmpresa::FabricaEmpresa(){}

FabricaEmpresa* FabricaEmpresa::getInstance(){
  if (instance==NULL)
    instance = new FabricaEmpresa();
  return instance;
}

IEmpresa* FabricaEmpresa::getIEmpresa(){
  return Empresa::getInstance();
}

FabricaEmpresa::~FabricaEmpresa(){
  delete Empresa::getInstance();
}

void f29(){
/*Ejercicio 9 *
  Se considera una empresa que mantiene información de sus empleados. De cada
  empleado se almacena su cédula de identidad (que lo identifica) y su nombre. Los
  empleados de la empresa pueden ser comunes, de los cuales se conoce su sueldo, o
  jornaleros, de los cuales se mantiene información de sus jornadas de trabajo (fecha y
  cantidad de horas trabajadas) y el valor de la hora. Todos los meses, al realizarse la
  liquidación de los sueldos, la empresa calcula el monto total por concepto de sueldos,
  en base al sueldo fijo para empleados comunes y como la cantidad de horas trabajadas
  en todas las jornadas por el valor de la hora para empleados jornaleros.
  Se pide desarrollar un programa en C++ que implemente las siguientes
  funcionalidades:
    • Agregar un empleado.
    • Eliminar un empleado.
    • Agregar un jornal a un empleado jornalero.
    • Calcular el total de sueldos a pagar por la empresa.
*/
  int operacion = 1;
  FabricaEmpresa* fabrica = FabricaEmpresa::getInstance();
  IEmpresa* empresa = fabrica->getIEmpresa();
  string ci;
  string tipo;
  while(operacion != 0 && operacion != -2){
    cout << "\n1.Agregar empleado\n2.Eliminar empleado\n3.Agregar un jornal a jornalero\n4.Calcular el total de sueldos a pagar\n0.Salir\nIngrese numero: ";
    cin >> operacion;
    switch (operacion){
      case 1:
        cout << "Que clase de empleado desea agregar (jornalero/comun): ";
        cin >> tipo;
        if (tipo == "jornalero")
          empresa->agregarJornalero();
        else 
          empresa->agregarComun();
        cout << "Empleado agregado!\n";
        break;
      case 2:
        cout << "Ingrese ci de empleado que desea eliminar: ";
        cin >> ci;
        if (empresa->isJornalero(ci))
          empresa->removerJornalero(ci);
        else 
          empresa->removerComun(ci);
        cout << "Empleado eliminado!\n";
        break;
      case 3:
        cout << "Ingrese ci de jornalero al que desea agreagar jornal: ";
        cin >> ci;
        empresa->agregarJornal(ci);
        cout << "Jornal agregado!\n";
        break;
      case 4:
        cout << "El total de sueldos a pagar es: " << empresa->getSueldos() << endl;
        break;
    }
  }
  delete fabrica;
}

void f210(){
  Padre test;
  Hijo nuevo;
  int a,b;
  cout << "Ingrese numero 1 a sumar: ";
  cin >> a;
  cout << "Ingrese numero 2 a sumar: ";
  cin >> b;
  cout << "Resultado: " << nuevo.sumar(a,b) << "\n";
}

int main() {
  int operacion = 1;
  while (operacion != 0) {
    cout << "\n1.Map\n2.Clases\n0.Salir\nIngrese numero: ";
    cin >> operacion;
    switch (operacion){
      case 1: 
        f1();
        break;
      case 2:
        while(operacion != -1 && operacion != 0){
          cout << "\n1.Ejercicio 1\n5.Ejercicio 5 (Publicaciones)\n9.Ejercicio 9 (Empleados)\n10.Ejemplo 10\n-1.Atras\n0.Salir\nIngrese numero: ";
          cin >> operacion;
          switch(operacion){
            case 1:
              f21();
              break;
            case 5:
              f25();
              break;
            case 9:
              f29();
              operacion = 0;
              break;
            case 10:
              f210();
              break;
          }
        }
    }
  }
}