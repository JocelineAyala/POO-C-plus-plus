#include <iostream>
#include <string>
#include <vector>

class Libro {
public:
    std::string titulo;
    std::string autor;
    int anioPublicacion;
    bool estaDisponible;

    Libro() : titulo(""), autor(""), anioPublicacion(0), estaDisponible(true) {}

    void mostrarDetallesCompletos() const{
        std::cout <<"----------------------------"<< std::endl;
        std::cout << "Titulo: " << titulo << std::endl;
        std::cout << "Autor: " << autor << std::endl; 
        std::cout << "Año: " << anioPublicacion << std::endl;
        std::cout << "Disponibilidad: " << (estaDisponible ? "Disponible": "Prestado") << std::endl;
    }
};
class Usuario {
public:
    std::string nombre;
    int id;
    std::vector<std::string> librosPrestados;

    Usuario(std::string n = "", int i = 0) : nombre(n), id(i) {}

    void mostrarPrestamos() const {
        std::cout << "--- Prestamos de " << nombre << " (ID " << id << ")" << std::endl;
        if (librosPrestados.empty()) {
            std::cout << "No tiene libros prestados" << std::endl;
        } else {
            for (int i = 0; i < (int)librosPrestados.size(); i++) {
                std::cout << "- " << librosPrestados[i] << std::endl;
            }
        }
    }

    bool tieneLibro(const std::string& titulo) const {
        for (int i = 0; i < (int)librosPrestados.size(); i++) {
            if (librosPrestados[i] == titulo) return true;
        }
        return false;
    }

    void quitarLibro(const std::string& titulo) {
        for (int i = 0; i < (int)librosPrestados.size(); i++) {
            if (librosPrestados[i] == titulo) {
                librosPrestados.erase(librosPrestados.begin() + i);
                return;
            }
        }
    }
};

class Biblioteca {
private:
    std::vector<Libro> coleccion;

public:
    void agregarLibro(const Libro& nuevoLibro) {
        for (int i = 0; i < (int)coleccion.size(); i++) {
            if (coleccion[i].titulo == nuevoLibro.titulo) {
                std::cout << "El libro '" << nuevoLibro.titulo << "' ya existe en la biblioteca "<<std::endl;
                return;
            }
        }
        coleccion.push_back(nuevoLibro);
        std::cout << "Libro agregado: " << nuevoLibro.titulo << std::endl;
    }

    void mostrarInventario() const {
        if (coleccion.empty()) {
            std::cout << "No hay libros en la biblioteca" << std::endl;
            return;
        }
        for (int i = 0; i < (int)coleccion.size(); i++) { //En esta línea usé IA porque no entendía la sintaxis y me estaba dando error.
            coleccion[i].mostrarDetallesCompletos();
        }
    }

    Libro* buscarLibro(const std::string& tituloBuscado) {
        for (int i = 0; i < (int)coleccion.size(); i++) {
            if (coleccion[i].titulo == tituloBuscado) {
                return &coleccion[i];
            }
        }
        return nullptr;
    }

    void prestarLibro(const std::string& tituloPrestamo, Usuario& usuario) {
        Libro* libro = buscarLibro(tituloPrestamo);
        if (libro == nullptr) {
            std::cout<< "El libro no se encuentra en la biblioteca" << std::endl;
            return;
        }
        if (!libro->estaDisponible) {
            std::cout << "El libro ya está prestado, regresa pronto" << std::endl;
            return; 
        }
        if (usuario.tieneLibro(libro->titulo)) {
            std::cout << "Ya tienes este libro prestado" <<std::endl;
            return;
        }
        libro->estaDisponible = false;
        usuario.librosPrestados.push_back(libro->titulo);
        std::cout << usuario.nombre << " ha prestado: " << libro->titulo << std::endl;
    }

    void devolverLibro(const std::string& tituloDevolucion, Usuario& usuario) {
        Libro* libro = buscarLibro(tituloDevolucion);
        if (libro == nullptr) {
            std::cout << "El libro no se encuentra en la biblioteca" << std::endl;
            return;
        }
        if (libro->estaDisponible) {
            std::cout << "El libro ya estaba disponible" << std::endl;
            return;
        }
        if (!usuario.tieneLibro(tituloDevolucion)) {
            std::cout << "Este usuario no tiene prestado ese libro." << std::endl;
            return;
        }

        usuario.quitarLibro(tituloDevolucion);
        libro->estaDisponible = true;
        std::cout << usuario.nombre << " ha devuelto: " << libro->titulo << std::endl;
    }
};

int main() {
    Biblioteca miBiblioteca;
    std::vector<Usuario> usuarios;
    int indiceUsuarioActivo = -1;

    // Agregar algunos libros de ejemplo para empezar
    Libro libroInicial;
    libroInicial.titulo = "Brevísima Historia del Tiempo";
    libroInicial.autor = "Stephen Hawking";
    libroInicial.anioPublicacion = 2005;
    miBiblioteca.agregarLibro(libroInicial);


    int opcion = 0;
    while (opcion != 8) {
        std::cout << "--- BIBLIOTECA DIGITAL KEY INSTITUTE ---" << std::endl;
        std::cout << "1. Anadir libro" << std::endl;
        std::cout << "2. Mostrar inventario" << std::endl;
        std::cout << "3. Registrar usuario" << std::endl;
        std::cout << "4. Seleccionar usuario activo" << std::endl;
        std::cout << "5. Prestar libro (usuario activo)" << std::endl;
        std::cout << "6. Devolver libro (usuario activo)" << std::endl;
        std::cout << "7. Ver prestamos del usuario activo" << std::endl;
        std::cout << "8. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        if (opcion == 1) {
            Libro nuevo;
            std::cout << "Titulo: ";
            std::getline(std::cin, nuevo.titulo);
            std::cout << "Autor: ";
            std::getline(std::cin, nuevo.autor);
            std::cout << "Año de publicacion: ";
            std::cin >> nuevo.anioPublicacion;
            std::cin.ignore();
            nuevo.estaDisponible = true;
            miBiblioteca.agregarLibro(nuevo);
        }
        else if (opcion == 2) {
            miBiblioteca.mostrarInventario();
        }
        else if (opcion == 3) {
            Usuario u;
            std::cout << "Nombre del usuario: ";
            std::getline(std::cin, u.nombre);
            std::cout << "ID del usuario (numero): ";
            std::cin >> u.id;
            std::cin.ignore();

            // evitar ID repetido
            bool existe = false;
            for (int i = 0; i < (int)usuarios.size(); i++) {
                if (usuarios[i].id == u.id) {
                    existe = true;
                    break;
                }
            }
            if (existe) {
                std::cout << "Ya existe un usuario con ese ID"<< std::endl;
            } else {
                usuarios.push_back(u);
                std::cout << "Usuario registrado: " << u.nombre << " (ID " << u.id << ")"<< std::endl;
                if (indiceUsuarioActivo == -1) {
                    indiceUsuarioActivo = (int)usuarios.size() - 1;
                    std::cout << "Usuario activo ahora: " << usuarios[indiceUsuarioActivo].nombre << std::endl;
                }
            }
        }
        else if (opcion == 4) {
            if (usuarios.empty()) {
                std::cout << "No hay usuarios registrados"<< std::endl;
            } else {
                int idsel;
                std::cout << "Ingrese ID del usuario a activar: ";
                std::cin >> idsel;
                std::cin.ignore();

                int idx = -1;
                for (int i = 0; i < (int)usuarios.size(); i++) {
                    if (usuarios[i].id == idsel) {
                        idx = i;
                        break;
                    }
                }

                if (idx == -1) {
                    std::cout << "No existe un usuario con ese ID" << std::endl;
                } else {
                    indiceUsuarioActivo = idx;
                    std::cout << "Usuario activo: " << usuarios[indiceUsuarioActivo].nombre << std::endl;
                }
            }
        }
        else if (opcion == 5) {
            if (indiceUsuarioActivo == -1) {
                std::cout << "Primero seleccione/registre un usuario activo" << std::endl;
            } else {
                std::string titulo;
                std::cout << "Titulo del libro a prestar: ";
                std::getline(std::cin, titulo);
                miBiblioteca.prestarLibro(titulo, usuarios[indiceUsuarioActivo]);
            }
        }
        else if (opcion == 6) {
            if (indiceUsuarioActivo == -1) {
                std::cout << "Primero seleccione/registre un usuario activo" << std::endl;
            } else {
                std::string titulo;
                std::cout << "Titulo del libro a devolver: ";
                std::getline(std::cin, titulo);
                miBiblioteca.devolverLibro(titulo, usuarios[indiceUsuarioActivo]);
            }
        }
        else if (opcion == 7) {
            if (indiceUsuarioActivo == -1) {
                std::cout << "No hay usuarios activos" <<std::endl;
            } else {
                usuarios[indiceUsuarioActivo].mostrarPrestamos();
            }
        }
        else if (opcion == 8) {
            std::cout << "Saliendo del programa" <<std::endl;
        }
        else {
            std::cout << "Opcion invalida" <<std::endl;
        }
    }

    return 0;
}