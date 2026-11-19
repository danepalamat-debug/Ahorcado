#include <iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<filesystem>

#define Vida 7
using namespace std;

struct Jugador{
    string nombre;
    int vida{Vida};
};

vector<string> cargarPalabras();

void guardar_palabra(const string& nombre);

void guardar_jugador(const string& nombre);

int generar_num_aleatorio(int menor, int mayor);

string conseguir_palabra(const vector<string> & p, int numero_aleatorio);

char PedirCaracter();

string Crear_Extra(const string & palabra);

bool Caracter_Correcto(char n,const string & palabra);

void Juego(const string & palabra_inicial, string & palabra_aux , Jugador & J1,char n);

void estado_prisionero(int n);
bool Ganar(const string & n);


int main()
{
    srand(time(nullptr));
    bool repetir = 1;
    cout<<"\n\tEl juego que vas a jugar es el ahorcado. Eres un preso condenado a muerte por un crimen atroz que no cometiste "
          "\n\ty la unica manera de salvarte es adivinando la palabra que se inventan tus ejecutadores."<<endl;
    cout<<"\n\t*NOTA : Existe una leyenda urbana que afirma que el juego nacio en los siglos XVII o XVIII como un metodo real"
          "\n\t en el que los condenados a muerte podian salvar su vida si adivinaban una palabra de cinco letras "
          "\n\tantes de que el verdugo completara la horca."<<endl;
    cout<<"\n\t No existe ninguna evidencia historica que respalde esta historia, por lo que se considera un mito moderno."<<endl;

    Jugador J1;
    Jugador AUX;
    do{
        //Te lo dice el guardia
        cout<<"\n\t"<<endl;
        cout<<"\n\tIntroduce tu nombre tu que vas a morir : ";
        cin>>J1.nombre;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }while(cin.fail());


    //
    //Guardar los nombres de los jugadores
    //

    guardar_jugador(J1.nombre);



    //PARTIDA :
    do {
        J1.vida = Vida;

        //Se consiguen las palabras del .txt:
        vector<string>contenedor = cargarPalabras();
        //Numero maximo que sera el tamaño-1 (para no cometer un out_of_range) del contenedor que tiene todas las palabras del txt
        int maximo = contenedor.size()-1;
        //Numero aleatorio : 0- Tamaño del vector
        int num_aleatorio = generar_num_aleatorio(0,maximo);

        //Elegir entre una de las palabras guardadas en el .txt
        string palabra_secreta = conseguir_palabra(contenedor,num_aleatorio);

        string auxiliar = Crear_Extra(palabra_secreta);

        do{
            AUX.vida = J1.vida;
            char letra = PedirCaracter();
            Juego(palabra_secreta,auxiliar,J1,letra);
            if (AUX.vida != J1.vida) {
                cout<<"\n\t================="<<endl;
                estado_prisionero(J1.vida);
                cout<<"\n\t================="<<endl;
            }
            if (Ganar(auxiliar)) {
                break;
            }

        }while (J1.vida > 0);

        if (J1.vida == 0) {
            cout<<"\n\tCaes al vacio y desafortunadamente el viaje al otro mundo no es rapido."<<endl;
            cout<<"\n\tTu cuerpo entero se ha formado en el inframundo"<<endl;

        }
        else {
            cout<<"\n\tTe has salvado "<<J1.nombre<<" y has logrado escapar con vida";
            cout<<"\n\tLa palabra era : "<<palabra_secreta;
        }

        //
        //Capturar palabras extras para mejores partidas
        //
        string palabra_extra;
        int repeticion = 0;
        do {
            if (repeticion == 0) {
                cout << "\n\tAntes de terminar, introduce una nueva palabra para asi expandir el diccionario :  ";
                cin >> palabra_extra;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                cout<<"\n\tPalabra invalida, introduzca otra valida : "<<endl;
                cin >> palabra_extra;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            repeticion++;
        }while (cin.fail());

        //
        //Pasar las palabras que han sido aceptadas a minusculas
        //
        for (char& c : palabra_extra) {
            c = tolower(static_cast<unsigned char>(c));
        }
        guardar_palabra(palabra_extra);

        cout<<"\n\tQuieres volver a jugar otra partida (0-no,1-si)?"<<endl;
        cin>>repetir;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"\n\tEntrada invalida, introduzca otra"<<endl;
            cin>>repetir;
        }
    }while (repetir);

    cout << "Hello World!" << endl;
    return 0;
}


vector<string> cargarPalabras() {
    vector<string> palabras;
    ifstream archivo("palabras.txt");
    if (archivo.is_open()) {
        string palabra;
        while (getline(archivo, palabra)) {
            palabras.push_back(palabra);
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
    return palabras;
}
void guardar_palabra(const string& nombre) {
    ofstream archivo("palabras.txt", ios::app);

    if (archivo.is_open()) {
        archivo << nombre << endl;
        archivo.close();

        cout << "\n\tNombre registrado." << endl;
        cout << "\n\tMuchas gracias" << endl;
    }
    else {
        cout << "\n\tEl nombre no se ha podido guardar correctamente." << endl;
    }
}
void guardar_jugador(const string& nombre) {
    ofstream archivo("Jugadores.txt", ios::app);

    if (archivo.is_open()) {
        archivo << nombre << endl;
        archivo.close();

        cout << "\n\tNombre registrado." << endl;
        cout << "\n\tMuchas gracias" << endl;
    }
    else {
        cout << "\n\tEl nombre no se ha podido guardar correctamente." << endl;
    }
}
int generar_num_aleatorio(int menor, int mayor){
    int num = rand() % (mayor - menor + 1) + menor;
    return num;
}
string conseguir_palabra(const vector<string> & p, int numero_aleatorio) {
    //Escoger una palabra del .txt
    return p.at(numero_aleatorio);
}
char PedirCaracter() {
    char aux;

    cout<<"\n\tIntroduzca una letra : ";
    cin>>aux;
    while (cin.fail() or (aux<97 and aux>122)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"\n\tLetra invalido, introduce otra";
        cin>>aux;
    }
    return aux;
}
string Crear_Extra(const string & palabra) {
    string aux(palabra.size(), '-');
    return aux;

}
bool Caracter_Correcto(char n,const string & palabra){
    for(int i{0};i<palabra.size();i++){
        if (palabra.at(i) == n) {
            return true;
        }
    }
    return false;
}
void Juego(const string & palabra_inicial, string & palabra_aux , Jugador & J1,char n){

    if (Caracter_Correcto(n,palabra_inicial)) {
        cout<<"\n\tLa letra "<<n<<" se encontro en la posicion :";

        for(int i{0};i<palabra_inicial.size();i++){

            if (palabra_inicial.at(i) == n) {
                palabra_aux.at(i) = n;
                cout<< i+1 <<" , ";
            }
        }
        cout<<endl;

        for (char m:palabra_aux) {
            cout<<m <<" "<<endl;
        }
    }
    else {
        cout<<"\n\tEl caracter no ha sido encontrado";
        J1.vida = J1.vida -1;
    }
}
void estado_prisionero(int n) {
    switch (n){
        case 1:
            cout<<"\n\tTe estan colocando la soga. Sientes como te roza y te quita la respiracion. Ya no sientes casi ninguna parte de tu cuerpo, solo puedes susurrar"<<endl;
            cout<<"\n\tSe dibuja la otra pierna"<<endl;
            cout<<"\n\tTe queda 1 intento";
            break;

        case 2:
            cout<<"\n\tTe levantan y te colocan en la tarima. Tienes la soga justo enfrente y sientes como una de tus piernas no puede moverse."<<endl;
            cout<<"\n\tSe ha dibujado una pierna"<<endl;
            cout<<"\n\tTe quedan 2 intentos"<<endl;
            break;

        case 3:
            cout<<"\n\tYa se ha preparado la tarima y todo funciona perfectamente. Te empieza a doler una herida en el brazo derecho."<<endl;
            cout<<"\n\tSe ha dibujado el otro brazo"<<endl;
            cout<<"\n\tTe quedan 3 intentos"<<endl;
            break;

        case 4:
            cout<<"\n\tComprueban que todos los instrumentos funcionan y hasta accionan la palanca comprobando que funciona."
                  "\n\tSientes un pinchazo en el brazo izquierdo"<<endl;
            cout<<"\n\tSe ha dibujado uno de los brazos"<<endl;
            cout<<"\n\tTe quedan 4 intentos";
            break;

        case 5:
            cout<<"\n\tVan sacando la soga y se regocijan viendo tu cara de terror. Te molesta la espalda"<<endl;
            cout<<"\n\tSe ha dibujado el torso"<<endl,
            cout<<"\n\tTe quedan 4 intentos"<<endl;
            break;
        case 6:
            cout<<"\n\tSe rien y disfrutan del fallo. Sientes un dolor en la cabeza"<<endl;
            cout<<"\n\tSe dibuja la cabeza"<<endl;
            break;

        default:
            cout<<"\n\tCaes al vacio y desafortunadamente el viaje al otro mundo no es rapido."<<endl;
            cout<<"\n\tTu cuerpo entero se ha formado en el inframundo"<<endl;
            break;
    }
}

bool Ganar(const string & n){
    //Palabra descubierta
    for (char m:n) {
        if (m == '-') {
            return false;
        }
    }
    return true;
}