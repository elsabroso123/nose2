#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
int orden = 0;

class Articulo
{
public:
    string nombre;
    string talla;
    string estilo;
    string marca;
    string descripcion;
    int calificacion = 5;
    int existencias;
    float precio;
    Articulo *siguiente;

    Articulo(string _nombre, string _talla, string _estilo, string _marca, string _descripcion, int _existencias, float _precio)
        : nombre(_nombre), talla(_talla), estilo(_estilo), marca(_marca), descripcion(_descripcion), existencias(_existencias), precio(_precio), siguiente(nullptr)
    {
    }
};

class Inventario
{
public:
    Articulo *inicio;

    Inventario() : inicio(nullptr)
    {
    }

    void guardarArchivo(const Inventario &inventario)
    {
        ofstream archivo("inventario.txt");

        if (!archivo.is_open())
        {
            cout << "No se pudo abrir el archivo" << endl;
            return;
        }

        Articulo *actual = inventario.inicio;
        while (actual)
        {
            archivo << actual->nombre << ',' << actual->talla << ',' << actual->estilo << ',' << actual->marca
                    << ',' << actual->descripcion << ',' << actual->existencias << ',' << actual->precio << endl;
            actual = actual->siguiente;
        }

        archivo.close();
    }

    void agregarArticulo(string nombre, string talla, string estilo, string marca, string descripcion, int existencias, float precio)
    {
        Articulo *nuevoArticulo = new Articulo(nombre, talla, estilo, marca, descripcion, existencias, precio);

        nuevoArticulo->siguiente = inicio;
        inicio = nuevoArticulo;

        cout << "Articulo registrado" << endl;
    }

    int eliminarArticulo()
    {
        if (!inicio)
        {
            cout << "El inventario esta vacio." << endl;
            return 0;
        }

        string nombreArticulo;
        cout << "Ingrese el nombre del articulo a eliminar: ";
        cin >> nombreArticulo;

        Articulo *actual = inicio;
        Articulo *anterior = nullptr;
        bool encontrado = false;

        while (actual)
        {
            if (actual->nombre == nombreArticulo)
            {
                encontrado = true;

                if (anterior)
                {
                    anterior->siguiente = actual->siguiente;
                }
                else
                {
                    inicio = actual->siguiente;
                }

                delete actual;
                cout << "Articulo eliminado" << endl;
                return 1;
            }

            anterior = actual;
            actual = actual->siguiente;
        }

        if (!encontrado)
        {
            cout << "No se encontro el articulo en el inventario." << endl;
            return 0;
        }
        return 0;
    }

    void mostrarArticulos()
    {
        Articulo *actual = inicio;
        while (actual)
        {
            cout << "*************" << endl;
            cout << "Nombre: " << actual->nombre << endl
                 << ", Talla: " << actual->talla << endl
                 << ", Estilo: " << actual->estilo << endl
                 << ", Marca: " << actual->marca << endl
                 << ", Descripcion: " << actual->descripcion << endl
                 << ", Calificacion: " << actual->calificacion << endl
                 << ", Existencias: " << actual->existencias << endl
                 << ", Precio: " << actual->precio << endl;
            cout << "*************" << endl;
            actual = actual->siguiente;
        }
    }

    void buscarArticulo()
    {
        if (!inicio)
        {
            cout << "El inventario esta vacio." << endl;
            return;
        }

        string nombreArticulo;
        cout << "Ingrese el nombre del articulo a buscar: ";
        cin >> nombreArticulo;

        Articulo *actual = inicio;
        bool encontrado = false;

        while (actual)
        {
            if (actual->nombre == nombreArticulo)
            {
                cout << "Nombre: " << actual->nombre << ", Talla: " << actual->talla << ", Estilo: " << actual->estilo
                     << ", Marca: " << actual->marca << ", Descripcion: " << actual->descripcion << ", Calificacion: " << actual->calificacion
                     << ", Existencias: " << actual->existencias << ", Precio: " << actual->precio << endl;
                encontrado = true;
                break;
            }
            actual = actual->siguiente;
        }

        if (!encontrado)
        {
            cout << "No se encontro el articulo en el inventario." << endl;
        }
    }

    int modificarArticulo()
    {
        if (!inicio)
        {
            cout << "El inventario esta vacio." << endl;
            return 0;
        }

        string nombreArticulo;
        cout << "Ingrese el nombre del articulo a modificar: ";
        cin >> nombreArticulo;

        Articulo *actual = inicio;
        bool encontrado = false;

        while (actual)
        {
            if (actual->nombre == nombreArticulo)
            {
                cout << "Ingrese el nuevo precio para el articulo " << actual->nombre << ": ";
                cin >> actual->precio;
                cout << "Ingrese la nueva talla para el articulo " << actual->nombre << ": ";
                cin >> actual->talla;
                cout << "Ingrese el nuevo estilo para el articulo " << actual->nombre << ": ";
                cin >> actual->estilo;
                cout << "Ingrese la nueva marca para el articulo " << actual->nombre << ": ";
                cin >> actual->marca;
                cout << "Ingrese la nueva descripcion para el articulo " << actual->nombre << ": ";
                cin.ignore();
                getline(cin, actual->descripcion);
                cout << "Ingrese las nuevas existencias para el articulo " << actual->nombre << ": ";
                cin >> actual->existencias;

                cout << "Articulo modificado" << endl;
                encontrado = true;
                return 1;
            }
            actual = actual->siguiente;
        }

        if (!encontrado)
        {
            cout << "No se encontro el articulo en el inventario." << endl;
            return 0;
        }
        return 0;
    }

    void recuperarArchivo(Inventario &inventario)
    {
        ifstream archivo("inventario.txt");
        string line;

        if (!archivo.is_open())
        {
            cout << "No se pudo abrir el archivo" << endl;
            return;
        }

        while (getline(archivo, line))
        {
            stringstream ss(line);

            string nombre, talla, estilo, marca, descripcion;
            int existencias;
            float precio;

            getline(ss, nombre, ',');
            getline(ss, talla, ',');
            getline(ss, estilo, ',');
            getline(ss, marca, ',');
            getline(ss, descripcion, ',');
            ss >> existencias >> precio;

            inventario.agregarArticulo(nombre, talla, estilo, marca, descripcion, existencias, precio);
        }

        archivo.close();
        cout << "Informacion recuperada desde inventario.txt, revise el inventario" << endl;
    }

    ~Inventario()
    {
        Articulo *actual = inicio;
        while (actual)
        {
            Articulo *siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }
};

class Pedido {
public:
    int numeroPedido;
    vector<string> articulos;

    Pedido(int num) : numeroPedido(num) {}

    void agregarArticulo(const string& articulo) {
        articulos.push_back(articulo);
    }

    void limpiarArticulos() {
        articulos.clear();
    }
};

class OrganizadorPedidos {
public:
    void agregarPedido(Pedido& pedido) {
        pedidos.push_back(pedido);
    }

    void mostrarPedidos() {
        for (const auto& pedido : pedidos) {
            cout << "Pedido " << pedido.numeroPedido << " - Articulos:" << endl;
            for (const auto& articulo : pedido.articulos) {
                cout << "- " << articulo << endl;
            }
            cout << endl;
        }
    }

    void pedirPedidos() {
        int numPedido;
        cout << "Ingrese el numero del pedido: ";
        cin >> numPedido;

        Pedido nuevoPedido(numPedido);

        string articulo;
        do {
            cout << "Ingrese el nombre del articulo o 'fin' para terminar: ";
            getline(cin >> ws, articulo);
            if (articulo != "fin") {
                nuevoPedido.agregarArticulo(articulo);
            }
        } while (articulo != "fin");

        agregarPedido(nuevoPedido);
    }

    void guardarEnArchivo(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);

        if (archivo.is_open()) {
            for (const auto& pedido : pedidos) {
                archivo << "PedidoLength=" << sizeof(pedido.numeroPedido) + calcularLongitudArticulos(pedido) << "\n";
                archivo << "Pedido " << pedido.numeroPedido << "\n";
                for (const auto& articulo : pedido.articulos) {
                    archivo << "Articulo: " << articulo << "\n";
                }
                archivo << "\n";
            }
            archivo.close();
            cout << "Pedidos guardados en " << nombreArchivo << endl;
        } else {
            cerr << "No se pudo abrir el archivo." << endl;
        }
    }

    void eliminarPedido(int numPedido) {
        auto primer = remove_if(pedidos.begin(), pedidos.end(),
            [numPedido](const Pedido& pedido) { return pedido.numeroPedido == numPedido; });

        if (primer != pedidos.end()) {
            pedidos.erase(primer);
            cout << "Pedido " << numPedido << " eliminado." << endl;

            ofstream archivo("pedidos.txt", ofstream::trunc);
            archivo.close();

            guardarEnArchivo("pedidos.txt");
        } else {
            cout << "Pedido " << numPedido << " no encontrado." << endl;
        }
    }

    void modificarPedido(int numPedido) {
        auto pedidoAModificar = find_if(pedidos.begin(), pedidos.end(),
            [numPedido](const Pedido& pedido) { return pedido.numeroPedido == numPedido; });

        if (pedidoAModificar != pedidos.end()) {
            pedidoAModificar->limpiarArticulos();
            cout << "Ingrese los nuevos articulos para el Pedido " << numPedido << ":" << endl;

            string articulo;
            do {
                cout << "Ingrese el nombre del articulo o 'fin' para terminar: ";
                getline(cin >> ws, articulo);
                if (articulo != "fin") {
                    pedidoAModificar->agregarArticulo(articulo);
                }
            } while (articulo != "fin");

            cout << "Pedido " << numPedido << " modificado." << endl;

            ofstream archivo("pedidos.txt", ofstream::trunc);
            archivo.close();

            guardarEnArchivo("pedidos.txt");
        } else {
            cout << "Pedido " << numPedido << " no encontrado." << endl;
        }
    }

    void buscarPedido(int numPedido) {
        auto pedidoEncontrado = find_if(pedidos.begin(), pedidos.end(),
            [numPedido](const Pedido& pedido) { return pedido.numeroPedido == numPedido; });

        if (pedidoEncontrado != pedidos.end()) {
            cout << "Pedido " << pedidoEncontrado->numeroPedido << " encontrado:" << endl;
            for (const auto& articulo : pedidoEncontrado->articulos) {
                cout << "- " << articulo << endl;
            }
        } else {
            cout << "Pedido " << numPedido << " no encontrado." << endl;
        }
    }

private:
    vector<Pedido> pedidos;

    int calcularLongitudArticulos(const Pedido& pedido) {
        int longitud = 0;
        for (const auto& articulo : pedido.articulos) {
            longitud += articulo.length() + sizeof("Articulo: ") - 1;
        }
        return longitud;
    }
};

class Provedor
{
public:
    char numero_provedor[4], nombre[50], direccion[50], correo[30];
    void Agregar();
    void Mostrar();
    void Modificar();
    void Buscar();
    void Eliminar();
} provedor;
void Provedor::Agregar()
{
    cout<<"Agregar provedor"<<endl;
    cout<<"Numero de provedor: ";
    cin.ignore();
    cin.getline(numero_provedor,4);
    cout<<"Nombre: ";
    cin.getline(nombre, 50);
    cout<<"Direccion: ";
    cin.getline(direccion, 50);
    cout<<"Correo: ";
    cin.getline(correo, 50);

    ofstream archivo("provedores.txt",ios::app);
    archivo.write((char*)&provedor,sizeof(provedor));
    archivo.close();
}
void Provedor::Mostrar()
{
    char usuario2[10], password2[10];
    int band=0;
    ifstream archivo("provedores.txt");
    if(!archivo.good())
    {
        cout<<"\n El archivo no existe....."<<endl;
    }
    else
    {
        cout<<"Provedores"<<endl;
        while(!archivo.eof())
        {
            archivo.read((char*)&provedor,sizeof(provedor));
            if(archivo.eof())
            {
                break;
            }
            cout<<"Numero de provedor: "<<numero_provedor<<endl;
            cout<<"Nombre: "<<nombre<<endl;
            cout<<"Direccion: "<<direccion<<endl;
            cout<<"Correo: "<<correo<<endl;

            cout<<""<<endl;
        }
        archivo.close();
    }
}
void Provedor::Eliminar()
{
    char valor[4];
    int opcion=0;
    ifstream archivo("provedores.txt");
    if(!archivo.good())
    {
        cout<<"\n El archivo no existe....."<<endl;
    }
    else
    {
        cout<<"Eliminar un provedor"<<endl;
        cout<<"Ingrese el numero del provedor a eliminar: ";
        cin.ignore();
        cin.getline(valor,4);
        ofstream archivo2("temporal.txt",ios::app);
        while(!archivo.eof())
        {
            archivo.read((char*)&provedor,sizeof(provedor));
            if(archivo.eof())
            {
                break;
            }
            if(strcmp(numero_provedor,valor)==0)
            {
                cout<<"\tProvedor Encontrado"<<endl;
                cout<<"Numero de provedor: "<<numero_provedor<<endl;
                cout<<"Nombre: "<<nombre<<endl;
                cout<<"Direccion: "<<direccion<<endl;
                cout<<"Correo: "<<correo<<endl;
                cout<<"DESEAS ELIMINAR?\n1.- SI\n0.- NO\n>: ";
                cin>>opcion;
                if(opcion==1)
                {

                }
                else
                {
                    archivo2.write((char*)&provedor,sizeof(provedor));
                }
            }
            else
            {
                archivo2.write((char*)&provedor,sizeof(provedor));
            }
        }
        archivo.close();
        archivo2.close();
        remove("provedores.txt");
        char oldname[] ="temporal.txt";
        char newname[] ="provedores.txt";
        rename(oldname,newname);
    }
}

void Provedor::Modificar()
{
    char valor[4];
    ifstream archivo("provedores.txt");
    if(!archivo.good())
    {
        cout<<"\n El archivo no existe....."<<endl;
    }
    else
    {
        cout<<"Modificar provedor"<<endl;
        cout<<"Ingrese el numero del provedor a modificar: ";
        cin.ignore();
        cin.getline(valor,4);
        ofstream archivo2("temporal.txt",ios::app);
        while(!archivo.eof())
        {
            archivo.read((char*)&provedor,sizeof(provedor));
            if(archivo.eof())
            {
                break;
            }
            if(strcmp(numero_provedor,valor)==0)
            {
                cout<<""<<endl;
                cout<<"Nuevo nombre: ";
                cin.getline(nombre, 50);
                cout<<"Nueva direccion: ";
                cin.getline(direccion, 50);
                cout<<"Nuevo correo: ";
                cin.getline(correo, 30);
                ofstream archivo("provedores.txt",ios::app);
                archivo2.write((char*)&provedor,sizeof(provedor));
            }
            else
            {
                archivo2.write((char*)&provedor,sizeof(provedor));
            }

        }
        archivo.close();
        archivo2.close();
        remove("provedores.txt");
        char oldname[] ="temporal.txt";
        char newname[] ="provedores.txt";
        rename(oldname,newname);
    }
}

void Provedor::Buscar(){
    char valor[4];
    ifstream archivo("provedores.txt");
    if(!archivo.good())
    {
        cout<<"\n El archivo no existe....."<<endl;
    }
    else
    {
        cout<<"Buscar Proveedor"<<endl;
        cout<<"Ingrese el numero del proveedor a buscar: ";
        cin.getline(valor,4);
        cin.getline(valor,4);
        archivo.read((char*)&provedor,sizeof(provedor));
        if(strcmp(numero_provedor,valor)==0)
        {
            cout<<"\tProveedor Encontrado"<<endl;
            cout<<"Numero Provedor: "<<numero_provedor<<endl;
            cout<<"Nombre: "<<nombre<<endl;
            cout<<"Direccion: "<<direccion<<endl;
            cout<<"Correo: "<<correo<<endl;
        }
        else
        {
            cout << "Orden no encontrada..." << endl;
        }
    }
    archivo.close();
}

class CancelacionPedido {
public:
    int numeroPedido;
    string motivo;
    string fecha;

    CancelacionPedido() : numeroPedido(0), motivo(""), fecha("") {}

    CancelacionPedido(int numPedido, const string& motivoCancelacion, const string& fechaCancelacion)
        : numeroPedido(numPedido), motivo(motivoCancelacion), fecha(fechaCancelacion) {}
};

class RegistroCancelaciones {
public:
    vector<CancelacionPedido> cancelaciones;

    void agregarCancelacion(int numPedido, const string& motivo, const string& fecha) {
        CancelacionPedido cancelacion(numPedido, motivo, fecha);
        cancelaciones.push_back(cancelacion);
    }

    void mostrarCancelaciones() {
        for (const auto& cancelacion : cancelaciones) {
            cout << "Numero de Pedido: " << cancelacion.numeroPedido << endl;
            cout << "Motivo de Cancelacion: " << cancelacion.motivo << endl;
            cout << "Fecha de Cancelacion: " << cancelacion.fecha << endl;
            cout << "--------------------------" << endl;
        }
    }

    void guardarEnArchivo(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo, ios::binary);

        if (archivo.is_open()) {
            for (const auto& cancelacion : cancelaciones) {
                archivo.write((char*)&cancelacion, sizeof(CancelacionPedido));
            }
            archivo.close();
            cout << "Cancelaciones guardadas en " << nombreArchivo << endl;
        } else {
            cerr << "No se pudo abrir el archivo." << endl;
        }
    }

    void recuperarDesdeArchivo(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo, ios::binary);

        if (archivo.is_open()) {
            CancelacionPedido cancelacion;
            while (archivo.read((char*)&cancelacion, sizeof(CancelacionPedido))) {
                cancelaciones.push_back(cancelacion);
            }
            archivo.close();
            cout << "Cancelaciones recuperadas desde " << nombreArchivo << endl;
        } else {
            cerr << "No se pudo abrir el archivo." << endl;
        }
    }

    void buscarCancelacion(int numPedido) {
        bool encontrado = false;
        for (const auto& cancelacion : cancelaciones) {
            if (cancelacion.numeroPedido == numPedido) {
                cout << "Numero de Pedido: " << cancelacion.numeroPedido << endl;
                cout << "Motivo de Cancelacion: " << cancelacion.motivo << endl;
                cout << "Fecha de Cancelacion: " << cancelacion.fecha << endl;
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            cout << "Cancelacion no encontrada para el numero de pedido " << numPedido << endl;
        }
    }

    void eliminarCancelacion(int numPedido) {
        auto it = remove_if(cancelaciones.begin(), cancelaciones.end(),
            [numPedido](const CancelacionPedido& cancelacion) { return cancelacion.numeroPedido == numPedido; });

        if (it != cancelaciones.end()) {
            cancelaciones.erase(it, cancelaciones.end());
            cout << "Cancelacion para el nomero de pedido " << numPedido << " eliminada." << endl;
            guardarEnArchivo("cancelaciones.bin");
        } else {
            cout << "Cancelacion no encontrada para el nomero de pedido " << numPedido << endl;
        }
    }

    void modificarCancelacion(int numPedido, const string& nuevoMotivo, const string& nuevaFecha) {
        for (auto& cancelacion : cancelaciones) {
            if (cancelacion.numeroPedido == numPedido) {
                cancelacion.motivo = nuevoMotivo;
                cancelacion.fecha = nuevaFecha;
                cout << "Cancelacion para el numero de pedido " << numPedido << " modificada." << endl;
                guardarEnArchivo("cancelaciones.bin");
                return;
            }
        }
        cout << "Cancelacion no encontrada para el numero de pedido " << numPedido << endl;
    }
};

class Empleado
{
public:
    char nombre[35], correo[50], contrasena[20];
    double salario;

    void capturar();
    void buscar();
    void mostrar();
    void Modificar();
    void Eliminar();
    void Mostrar_Indice();
    void Orden();
} x;

class Indice
{
public:
    char nombre[35];
    long int pos;
} y;

void Empleado::mostrar()
{
    ifstream a("empleados.txt");
    if (!a.good())
        cout << "No existe el archivo";
    else
    {
        while (!a.eof())
        {
            a.read((char *)&x, sizeof(x));
            if (a.eof())
                break;
            cout << "Nombre: " << x.nombre << endl
                 << "Correo: " << x.correo << endl
                 << "Salario: " << x.salario << endl;
        }
    }
    a.close();
}

void Empleado::Mostrar_Indice()
{
    ifstream a("indice.txt");
    if (!a.good())
        cout << "No existe el archivo";
    else
    {
        while (!a.eof())
        {
            a.read((char *)&y, sizeof(y));
            if (a.eof())
                break;
            cout << "Nombre: " << y.nombre << endl << endl;
        }
    }
    a.close();
}

void Empleado::capturar()
{
    fflush(stdin);
    cout << "Dame el nombre del empleado" << endl;
    cin.getline(nombre, 35);
    cout << "Dame el correo" << endl;
    cin.getline(correo, 50);
    cout << "Dame el salario" << endl;
    cin >> salario;
    cout << "Dame la contraseña" << endl;
    cin.ignore();
    cin.getline(contrasena, 20);

    ofstream a("empleados.txt", ios::app);
    a.write((char *)&x, sizeof(x));
    y.pos = a.tellp();
    y.pos -= sizeof(x);
    a.close();
    strcpy(y.nombre, nombre);
    ofstream b("indice.txt", ios::app);
    b.write((char *)&y, sizeof(y));
    b.close();
    orden++;
}

void Empleado::buscar()
{
    char nombre_buscar[35];
    int band = 0;

    ifstream b("indice.txt");
    if (!b.good())
    {
        cout << "No existe el archivo";
    }
    else
    {
        cout << "\nNombre a buscar:" << endl;
        fflush(stdin);
        cin.getline(nombre_buscar, 35);

        while (!b.eof())
        {
            b.read((char *)&y, sizeof(y));
            if (b.eof())
            {
                break;
            }
            if (strcmp(y.nombre, nombre_buscar) == 0)
            {
                ifstream a("empleados.txt");
                a.seekg(y.pos, ios::beg);
                a.read((char *)&x, sizeof(x));
                cout << "Nombre: " << x.nombre << endl
                     << "Correo: " << x.correo << endl
                     << "Salario: " << x.salario << endl;
                a.close();
                band = 1;
                break;
            }
        }
        if (band == 0)
        {
            cout << "\n NO EXISTE REGISTRO.....";
        }
    }
    b.close();
}

void Empleado::Modificar()
{
    char nombre_mod[35];
    int band = 0;
    int opc;

    ifstream b("indice.txt");
    if (!b.good())
    {
        cout << "No existe el archivo";
    }
    else
    {
        cout << "\nNombre a modificar:" << endl;
        fflush(stdin);
        cin.getline(nombre_mod, 35);

        while (!b.eof())
        {
            opc = 0;
            b.read((char *)&y, sizeof(y));
            if (b.eof())
            {
                break;
            }
            if (strcmp(y.nombre, nombre_mod) == 0 && band == 0)
            {
                ifstream a("empleados.txt");
                a.seekg(y.pos, ios::beg);
                a.read((char *)&x, sizeof(x));
                if (a.eof())
                    break;
                cout << "Nombre: " << x.nombre << endl
                     << "Correo: " << x.correo << endl
                     << "Salario: " << x.salario << endl;
                cout << "Deseas modificarlo\n"
                     << "1.-Si   2.-No";
                cin >> opc;
                band = 1;
                a.close();
                break;
            }
        }
        b.close();
        if (opc == 1)
        {
            fflush(stdin);
            ifstream indice("indice.txt");
            ifstream datos("empleados.txt");
            while (!indice.eof())
            {
                indice.read((char *)&y, sizeof(y));
                datos.read((char *)&x, sizeof(x));
                if (indice.eof())
                {
                    break;
                }
                if (strcmp(y.nombre, nombre_mod) == 0)
                {
                    cout << "Dame el nombre del empleado" << endl;
                    cin.getline(nombre, 35);
                    cout << "Dame el correo" << endl;
                    cin.getline(correo, 50);
                    cout << "Dame el salario" << endl;
                    cin >> salario;
                }

                ofstream c("temp.txt", ios::app);
                c.write((char *)&x, sizeof(x));
                strcpy(y.nombre, nombre);
                ofstream d("tempind.txt", ios::app);
                d.write((char *)&y, sizeof(y));
                d.close();
                c.close();
            }
        }

        if (band == 0)
        {
            cout << "\n NO EXISTE REGISTRO.....";
        }
    }
    remove("indice.txt");
    rename("tempind.txt", "indice.txt");
    remove("empleados.txt");
    rename("temp.txt", "empleados.txt");
}

void Empleado::Eliminar()
{
    char nombre_elim[35];
    int band = 0;
    int opc, cont = 0, cont2 = 0;

    ifstream b("indice.txt");
    if (!b.good())
    {
        cout << "No existe el archivo";
    }
    else
    {
        cout << "\nNombre a eliminar:" << endl;
        fflush(stdin);
        cin.getline(nombre_elim, 35);

        while (!b.eof())
        {
            b.read((char *)&y, sizeof(y));
            cont++;
            if (b.eof())
            {
                break;
            }
            if (strcmp(y.nombre, nombre_elim) == 0)
            {
                ifstream a("empleados.txt");
                a.seekg(y.pos, ios::beg);
                a.read((char *)&x, sizeof(x));
                if (a.eof())
                    break;

                cout << "Nombre: " << x.nombre << endl
                     << "Correo: " << x.correo << endl
                     << "Salario: " << x.salario << endl;
                cout << "Deseas eliminar\n"
                     << "1.-Si   2.-No";
                cin >> opc;
                band = 1;
                a.close();
                break;
            }
        }
        b.close();
        if (opc == 1)
        {
            ifstream indice("indice.txt");
            ifstream datos("empleados.txt");
            while (!indice.eof())
            {
                indice.read((char *)&y, sizeof(y));
                datos.read((char *)&x, sizeof(x));
                if (indice.eof())
                {
                    break;
                }
                if (strcmp(y.nombre, nombre_elim))
                {
                    cont2++;
                    ofstream c("temp.txt", ios::app);
                    c.write((char *)&x, sizeof(x));
                    strcpy(y.nombre, nombre);
                    ofstream d("tempind.txt", ios::app);
                    d.write((char *)&y, sizeof(y));
                    d.close();
                    c.close();
                }
            }
            indice.close();
            datos.close();
            remove("indice.txt");
            rename("tempind.txt", "indice.txt");
            remove("empleados.txt");
            rename("temp.txt", "empleados.txt");
        }

        if (band == 0)
        {
            cout << "\n NO EXISTE REGISTRO.....";
        }
    }
}

void Empleado::Orden()
{
    int i = 0;
    char indice[20][35];
    char aux[35];

    ifstream a("indice.txt");
    if (!a.good())
        cout << "No existe el archivo";
    else
    {
        cout << "else";
        while (!a.eof())
        {
            a.read((char *)&y, sizeof(y));
            if (a.eof())
                break;

            char *cadena = y.nombre;
            strcpy(indice[i], cadena);

            i++;
        }
    }
    a.close();

    for (int i = 0; i < orden - 1; i++)
        for (int j = i + 1; j < orden; j++)
            if (strcmp(indice[i], indice[j]) > 0)
            {
                strcpy(aux, indice[j]);
                strcpy(indice[j], indice[i]);
                strcpy(indice[i], aux);
            }
    for (int i = 0; i < orden; i++)
    {

        strcpy(y.nombre, indice[i]);

        ofstream a("tempind.txt", ios::app);
        a.write((char *)&y, sizeof(y));
        a.close();
    }

    remove("indice.txt");
    rename("tempind.txt", "indice.txt");
}

int main()
{
    RegistroCancelaciones cancelaciones;
    Inventario inventario;
    OrganizadorPedidos organizador;
    int opcion = 0, opcionmenu;
    int numPedidos, numPedidoA;
    string nombre, talla, estilo, marca, descripcion;
    int existencias;
    float precio;
    inventario.recuperarArchivo(inventario);

    cancelaciones.recuperarDesdeArchivo("cancelaciones.bin");

    do {
        cout << "--------------------------Menu principal--------------------------" << endl;
        cout << "1. Menu de Articulos" << endl;
        cout << "2. Menu de Pedidos" << endl;
        cout << "3. Menu de Provedores" << endl;
        cout << "4. Menu de Cancelacion de pedido" << endl;
        cout << "5. Menu de Empleados" << endl;
        cout << "6. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcionmenu;

        switch (opcionmenu) {
            case 1:
                while (opcion != 6)
                {
                    cout << "*****Menu*****" << endl;
                    cout << "1.- Agregar articulo" << endl;
                    cout << "2.- Eliminar articulo" << endl;
                    cout << "3.- Mostrar articulos" << endl;
                    cout << "4.- Buscar articulo" << endl;
                    cout << "5.- Modificar articulo" << endl;
                    cout << "6.- Regresar" << endl;
                    cout << "Ingrese su opcion: ";
                    cin >> opcion;

                    switch (opcion)
                    {
                    case 1:
                        cout << "Ingrese el nombre del articulo: ";
                        cin >> nombre;
                        cout << "Ingrese la talla del articulo: ";
                        cin >> talla;
                        cout << "Ingrese el estilo del articulo: ";
                        cin >> estilo;
                        cout << "Ingrese la marca del articulo: ";
                        cin >> marca;
                        cout << "Ingrese la descripcion del articulo: ";
                        cin.ignore();
                        getline(cin, descripcion);
                        cout << "Ingrese las existencias del articulo: ";
                        cin >> existencias;
                        cout << "Ingrese el precio del articulo: ";
                        cin >> precio;
                        inventario.agregarArticulo(nombre, talla, estilo, marca, descripcion, existencias, precio);
                        inventario.guardarArchivo(inventario);
                        break;
                    case 2:
                        if (inventario.eliminarArticulo() == 1)
                            inventario.guardarArchivo(inventario);
                        break;
                    case 3:
                        inventario.mostrarArticulos();
                        break;
                    case 4:
                        inventario.buscarArticulo();
                        break;
                    case 5:
                        if (inventario.modificarArticulo() == 1)
                            inventario.guardarArchivo(inventario);
                        break;
                    case 6:
                        cout << "Regresando..." << endl;
                        break;
                    default:
                        cout << "Seleccione otra opcion..." << endl;
                        break;
                    }
                }
                break;
            case 2:
                do {
                    cout << "*****Menu*****" << endl;
                    cout << "1.- Agregar pedido" << endl;
                    cout << "2.- Eliminar pedido" << endl;
                    cout << "3.- Mostrar pedidos" << endl;
                    cout << "4.- Buscar pedido" << endl;
                    cout << "5.- Modificar pedido" << endl;
                    cout << "6.- Regresar" << endl;
                    cout << "Ingrese su opcion: ";
                    cin >> opcion;

                    switch(opcion) {
                    case 1:
                        cout << "Ingrese el numero de pedidos que desea agregar: ";
                        cin >> numPedidos;

                        for (int i = 0; i < numPedidos; ++i) {
                            cout << "Ingrese los detalles para el pedido " << i + 1 << ":" << endl;
                            organizador.pedirPedidos();
                        }

                        organizador.guardarEnArchivo("pedidos.txt");
                        break;
                    case 2:
                        cout << "Ingrese el numero del pedido que desea eliminar: ";
                        cin >> numPedidoA;

                        organizador.eliminarPedido(numPedidoA);
                    case 3:
                        organizador.mostrarPedidos();
                        break;
                    case 4:
                        cout << "Ingrese el numero del pedido que desea buscar: ";
                        cin >> numPedidoA;

                        organizador.buscarPedido(numPedidoA);
                        break;
                    case 5:
                        cout << "Ingrese el numero del pedido que desea modificar: ";
                        cin >> numPedidoA;

                        organizador.modificarPedido(numPedidoA);
                        break;
                    default:
                        cout << "Opcion incorrecta :c" << endl;
                    }

                } while (opcion != 6);
                break;
            case 3:
                do {
                    cout << "*****Menu*****" << endl;
                    cout << "1.- Agregar provedor" << endl;
                    cout << "2.- Mostrar provedor" << endl;
                    cout << "3.- Eliminar provedor" << endl;
                    cout << "4.- Buscar provedor" << endl;
                    cout << "5.- Modificar provedor" << endl;
                    cout << "6.- Regresar" << endl;
                    cout << "Ingrese su opcion: ";
                    cin >> opcion;

                    switch(opcion) {
                    case 1:
                        provedor.Agregar();
                        break;
                    case 2:
                        provedor.Mostrar();
                        break;
                    case 3:
                        provedor.Eliminar();
                        break;
                    case 4:
                        cout << "Ingrese el numero del pedido que desea buscar: ";
                        cin >> numPedidoA;

                        organizador.buscarPedido(numPedidoA);
                        break;
                    case 5:
                        provedor.Modificar();
                        break;
                    default:
                        cout << "Opcion incorrecta :c" << endl;
                    }

                } while (opcion != 6);
                break;
            case 4:
                do {
                    cout << "--------------------------Menu Cancelaciones--------------------------" << endl;
                    cout << "1. Agregar Cancelacion" << endl;
                    cout << "2. Mostrar Cancelaciones" << endl;
                    cout << "3. Buscar Cancelacion" << endl;
                    cout << "4. Eliminar Cancelacion" << endl;
                    cout << "5. Modificar Cancelacion" << endl;
                    cout << "6. Salir" << endl;
                    cout << "Ingrese una opcion: ";
                    cin >> opcion;

                    switch (opcion) {
                        case 1: {
                            int numPedido;
                            string motivo, fecha;
                            cout << "Ingrese el numero de pedido: ";
                            cin >> numPedido;
                            cout << "Ingrese el motivo de la cancelacion: ";
                            cin.ignore();
                            getline(cin, motivo);
                            cout << "Ingrese la fecha de la cancelacion: ";
                            getline(cin, fecha);
                            cancelaciones.agregarCancelacion(numPedido, motivo, fecha);
                            cancelaciones.guardarEnArchivo("cancelaciones.bin");
                            break;
                        }
                        case 2:
                            cancelaciones.mostrarCancelaciones();
                            break;
                        case 3: {
                            int numPedido;
                            cout << "Ingrese el numero de pedido a buscar: ";
                            cin >> numPedido;
                            cancelaciones.buscarCancelacion(numPedido);
                            break;
                        }
                        case 4: {
                            int numPedido;
                            cout << "Ingrese el numero de pedido a eliminar: ";
                            cin >> numPedido;
                            cancelaciones.eliminarCancelacion(numPedido);
                            break;
                        }
                        case 5: {
                            int numPedido;
                            string nuevoMotivo, nuevaFecha;
                            cout << "Ingrese el numero de pedido a modificar: ";
                            cin >> numPedido;
                            cout << "Ingrese el nuevo motivo de la cancelacion: ";
                            cin.ignore();
                            getline(cin, nuevoMotivo);
                            cout << "Ingrese la nueva fecha de la cancelacion: ";
                            getline(cin, nuevaFecha);
                            cancelaciones.modificarCancelacion(numPedido, nuevoMotivo, nuevaFecha);
                            break;
                        }
                        case 6:
                            cout << "Saliendo..." << endl;
                            break;
                        default:
                            cout << "Opcion incorrecta." << endl;
                    }
                } while (opcion != 6);
                break;
            case 5:
                do {
                    cout << "Selecciona una de las siguientes opciones:" << endl
                         << "1.-Capturar" << endl
                         << "2.-Buscar" << endl
                         << "3.-Mostrar todos" << endl
                         << "4.-Modificar" << endl
                         << "5.-Eliminar" << endl
                         << "6.-Mostrar Indice" << endl
                         << "7-.Ordenar Indice" << endl
                         << "8-.Regresar" << endl;
                    cin >> opcion;
                    switch (opcion) {
                    case 1:
                        x.capturar();
                        break;
                    case 2:
                        x.buscar();
                        break;
                    case 3:
                        x.mostrar();
                        break;
                    case 4:
                        x.Modificar();
                        break;
                    case 5:
                        x.Eliminar();
                        break;
                    case 6:
                        x.Mostrar_Indice();
                        break;
                    case 7:
                        x.Orden();
                        break;
                    case 8:
                        cout << "Regresando..." << endl;
                        break;
                    }
                } while (opcion != 8);
                break;
            case 6:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion incorrecta" << endl;
        }
    } while (opcionmenu != 6);

    return 0;
}
