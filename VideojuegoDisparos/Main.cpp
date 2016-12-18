#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;
//-------------------------------------------------Clase Persona-------------------------------------------------//
class Persona
{
public:
	Persona();
	void cargar_persona(String ruta);
	Sprite obtener_persona();
	void posicion_persona(int x, int y);
	void cargar_estado(bool _estado);
	bool obtener_estado();
	bool obtener_reiniciar();
	float obtener_t_reinicio();
	bool atacado(float x,float y);
	void cargar_muerte(float delta);
	float obtener_muerte();
	void cargar_creacion(float delta);
	float obtener_creacion();
	void  limpiar(float delta);
private:
	Texture persona;
	Sprite  sprite_persona;
	bool estado;
	bool reiniciar;
	float reload_time;
	float dead_time;
	float create_time;
};

Persona::Persona() {
	reload_time = 0;
	dead_time = 0;
}

void Persona::cargar_persona(String ruta)
{
	persona.loadFromFile(ruta);
	sprite_persona.setTexture(persona);
}

Sprite Persona::obtener_persona()
{
	return sprite_persona;
}

void Persona::posicion_persona(int x, int y) {
	sprite_persona.setPosition(x, y);
}

void Persona::cargar_estado(bool _estado)
{
	estado = _estado;
}

bool Persona::obtener_estado()
{
	return estado;
}

bool Persona::obtener_reiniciar()
{
	return reiniciar;
}

float Persona::obtener_t_reinicio()
{
	return reiniciar;
}

bool Persona::atacado(float x, float y) {
	return sprite_persona.getGlobalBounds().contains(x,y);
}

void Persona::cargar_muerte(float delta)
{
	dead_time = delta;
}

float Persona::obtener_muerte()
{
	return dead_time;
}

void Persona::cargar_creacion(float delta)
{
	 create_time = delta;
}

float Persona::obtener_creacion()
{
	return create_time;
}

void Persona::limpiar(float delta) {

	if (delta - dead_time >= 1.1  && dead_time > 0)
	{
		reload_time = delta + 2.0;
		reiniciar = true;
	}

	if (delta - create_time >= 4.1  && create_time > 0)
	{
		reload_time = delta + 2.0;
		reiniciar = true;
	}
	

}
//-------------------------------------------------Clase Enemigo-------------------------------------------------//
class Enemigo:virtual public Persona
{
public:
	Enemigo() { shot_time = 0; clock_shot.restart(); };
	bool disparar(vector <Sprite> &v, bool &g, float delta);
private:
	float shot_time;
	Clock clock_shot;

};

bool Enemigo::disparar(vector <Sprite> &v, bool &g, float delta) {

	if (clock_shot.getElapsedTime().asSeconds() - shot_time >= 3.0 &&  clock_shot.getElapsedTime().asSeconds() - shot_time < 3.1)
	{
		if (!g) {
			if (v.size()>1) {
				v.erase(v.end() - 1);
			}
			else {
				v.erase(v.end() - 1);
				g = true;
			}
		}
		shot_time += 3;
		return true;
	}
	return false;
}
//-------------------------------------------------Clase Abertura (Maneja Ventanas del Salon)-------------------------------------------------//
class Abertura
{
public:
	void cargar_x(int _x);
	int  obtener_x();
	void cargar_y(int _y);
	int  obtener_y();
	void cargar_estado(bool _estado);
	bool obtener_estado();
private:
	int x;
	int y;
	bool estado;
};

void Abertura::cargar_x(int _x)
{
	x = _x;
}

int Abertura::obtener_x()
{
	return x;
}

void Abertura::cargar_y(int _y)
{
	y = _y;
}

int Abertura::obtener_y()
{
	return y;
}

void Abertura::cargar_estado(bool _estado)
{
	estado = _estado;
}

bool Abertura::obtener_estado()
{
	return estado;
}
//-------------------------------------------------Clase Asset (Maneja Recursos)-------------------------------------------------//
class Asset{
public:
	void cargar_fondo(String ruta);
	Sprite obtener_fondo();
	void cargar_cursor(String ruta);
	Sprite obtener_cursor();
	void posicion_cursor(int x, int y);
	void cargar_vida(String ruta);
	Sprite obtener_vida();
	void cargar_fuente(String ruta);
	void cargar_puntaje(String puntos);
	Text obtener_puntaje();
	void cargar_h1(String t1);
	Text obtener_h1();
	void cargar_h2(String t2);
	Text obtener_h2();
	
private:
	Texture fondo;
	Texture cursor;
	Texture vida;
	Font fuente;
	Text puntaje;
	Text h1;
	Text h2;
	Sprite  sprite_fondo;
	Sprite  sprite_cursor;
	Sprite  sprite_vida;

};

void Asset::cargar_fondo(String ruta)
{
	fondo.loadFromFile(ruta);
	sprite_fondo.setTexture(fondo);
}

Sprite Asset::obtener_fondo()
{
	return  sprite_fondo;
}

void Asset::cargar_cursor(String ruta)
{
	cursor.loadFromFile(ruta);
	sprite_cursor.setTexture(cursor);
}

Sprite Asset::obtener_cursor()
{
	return sprite_cursor;
}

void Asset::posicion_cursor(int x, int y) {
	sprite_cursor.setPosition(x, y);
}

void Asset::cargar_vida(String ruta)
{
	vida.loadFromFile(ruta);
	sprite_vida.setTexture(vida);
}

Sprite Asset::obtener_vida()
{
	return sprite_vida;
}

void Asset::cargar_fuente(String ruta)
{
	fuente.loadFromFile(ruta);
}

void Asset::cargar_puntaje(String puntos)
{
	puntaje.setPosition(600, 500); 
	puntaje.setFont(fuente);
	puntaje.setCharacterSize(80);
	puntaje.setFillColor(Color::Red);
	puntaje.setString(puntos);
}

Text Asset::obtener_puntaje()
{
	return puntaje;
}

void Asset::cargar_h1(String t1)
{
	h1.setPosition(180, 150);
	h1.setFont(fuente);
	h1.setCharacterSize(200);
	h1.setFillColor(Color::Red);
	h1.setString(t1);
}

Text Asset::obtener_h1()
{
	return h1;
}

void Asset::cargar_h2(String t2)
{
	h2.setPosition(150, 330);
	h2.setFont(fuente);
	h2.setCharacterSize(50);
	h2.setFillColor(Color::White);
	h2.setString(t2);
}

Text Asset::obtener_h2()
{
	return h2;
}

//-------------------------------------------------Funciones Auxiliares-------------------------------------------------//
int elegir_uno(vector <Abertura*> &v , int ocupado) {
	for (size_t i = 0; i < 5; i++)
	{
		if (v[i]->obtener_estado()) {
			v[i]->cargar_estado(false);
		}
		else
		{
			if(i != ocupado){
			v[i]->cargar_estado(true);
			return i;
			}
		}
	}
}

Clock reloj;
Time  dt;



int main()
{
	//-------------------------------------------------inicialización de ventana-------------------------------------------------//
	RenderWindow Juego(VideoMode(800, 600, 32), "Duelo de Saloon");
	Juego.setMouseCursorVisible(false);
	//-------------------------------------------------inicialización de asset-------------------------------------------//
	Asset *recursos = new Asset();
	recursos->cargar_fondo("../img/fondo.png");
	recursos->cargar_cursor("../img/cursor.png");
	recursos->cargar_vida("../img/vida.png");
	recursos->cargar_fuente("../ExtraSprinkles.ttf");
	recursos->cargar_h1("Game Over");
	recursos->cargar_h2("Presiona cualquier tecla para jugar de nuevo");
	//-------------------------------------------------declaración de variables-------------------------------------------------//
	bool gameover = false;
	int puntos = 0;
	int posicion_1 = 0; // posicion_x variables destinada a guardar futura posicion en ventana
	int posicion_2 = 0;
	Event evento;
	vector <Sprite> vidas(3,recursos->obtener_vida());
	vector <Abertura*> ventanas;
	for (int i = 6; i != 0; i--)
		ventanas.push_back(new Abertura());
	//-------------------------------------------------inicialización de aberturas-------------------------------------------------//
	ventanas[0]->cargar_x(365); ventanas[0]->cargar_y(200); ventanas[0]->cargar_estado(false); //Ventana  MID - SUPERIOR
	ventanas[1]->cargar_x(181); ventanas[1]->cargar_y(200); ventanas[1]->cargar_estado(false); //Ventana IZQ - SUPERIOR
	ventanas[2]->cargar_x(551); ventanas[2]->cargar_y(200); ventanas[2]->cargar_estado(false); //Ventana DER - SUPERIOR
	ventanas[3]->cargar_x(551); ventanas[3]->cargar_y(350); ventanas[3]->cargar_estado(false); //Ventana DER - INFERIOR
	ventanas[4]->cargar_x(181); ventanas[4]->cargar_y(350); ventanas[4]->cargar_estado(false); //Ventana IZQ - INFERIOR
	ventanas[5]->cargar_x(325); ventanas[5]->cargar_y(340); ventanas[5]->cargar_estado(false); //PUERTA
	//-------------------------------------------------inicialización de Amigos y Enemigos-------------------------------------------------//
	Enemigo *Enemigo_v = new Enemigo;  Enemigo_v->cargar_estado(true);  Enemigo_v->cargar_creacion(reloj.getElapsedTime().asSeconds());
	Enemigo *Enemigo_p = new Enemigo;  Enemigo_p->cargar_estado(true);  Enemigo_p->cargar_creacion(reloj.getElapsedTime().asSeconds());
	Persona *Amigo_v = new Persona;    Amigo_v->cargar_estado(true);    Amigo_v->cargar_creacion(reloj.getElapsedTime().asSeconds());
	Enemigo_v->cargar_persona("../img/enemigo_w/inicio.png");
	Enemigo_p->cargar_persona("../img/enemigo_d/inicio.png");
	Amigo_v->cargar_persona("../img/inocente_w/inicio.png");
	//-------------------------------------------------Definir abertura de Amigos y Enemigos de Inicio-------------------------------------------------//
	ventanas[1]->cargar_estado(true);
	ventanas[4]->cargar_estado(true);
	Amigo_v->posicion_persona(ventanas[1]->obtener_x(), ventanas[1]->obtener_y());
	Enemigo_v->posicion_persona(ventanas[4]->obtener_x(), ventanas[4]->obtener_y());
	Enemigo_p->posicion_persona(ventanas[5]->obtener_x(), ventanas[5]->obtener_y());
	//-------------------------------------------------Bucle Principal-------------------------------------------------//
	
	while (Juego.isOpen())
	{
		dt = reloj.getElapsedTime();
		recursos->cargar_puntaje(to_string(puntos*10));
		Juego.clear();
		Juego.draw(recursos->obtener_fondo());
		//-------------------------------------------------Condición de limpiar-------------------------------------------------//
		Enemigo_v->limpiar(dt.asSeconds());
		Enemigo_p->limpiar(dt.asSeconds());
		Amigo_v->limpiar(dt.asSeconds());
		//-------------------------------------------------Condición de enemigos-------------------------------------------------//
		if (Enemigo_v->obtener_reiniciar() && Enemigo_v->obtener_t_reinicio() < dt.asSeconds()) {
			delete Enemigo_v;
			cout << "NUEVO ENEMIGO DE VENTANA" << endl;
			posicion_1 = elegir_uno(ventanas, posicion_2);
			Enemigo_v = new Enemigo; Enemigo_v->cargar_estado(true); Enemigo_v->cargar_creacion(reloj.getElapsedTime().asSeconds());
			Enemigo_v->posicion_persona(ventanas[posicion_1]->obtener_x(), ventanas[posicion_1]->obtener_y());
			Enemigo_v->cargar_persona("../img/enemigo_w/inicio.png");
		}

		if (Enemigo_p->obtener_reiniciar() && Enemigo_p->obtener_t_reinicio() < dt.asSeconds() ) {
			delete Enemigo_p;
			cout << "NUEVO ENEMIGO DE PUERTA" << endl;
			Enemigo_p = new Enemigo; Enemigo_p->cargar_estado(true); Enemigo_p->cargar_creacion(reloj.getElapsedTime().asSeconds());
			Enemigo_p->posicion_persona(ventanas[5]->obtener_x(), ventanas[5]->obtener_y());
			Enemigo_p->cargar_persona("../img/enemigo_d/inicio.png");
		}

		if (Amigo_v->obtener_reiniciar() && Amigo_v->obtener_t_reinicio() < dt.asSeconds() && !gameover){
			delete 	Amigo_v;
			cout << "NUEVO AMIGO DE VENTANA" << endl;
			posicion_2 = elegir_uno(ventanas, posicion_1);
			Amigo_v = new Persona;Amigo_v->cargar_estado(true); Amigo_v->cargar_creacion(reloj.getElapsedTime().asSeconds());
			Amigo_v->cargar_persona("../img/inocente_w/inicio.png");
			Amigo_v->posicion_persona(ventanas[posicion_2]->obtener_x(), ventanas[posicion_2]->obtener_y());
		}
		//-------------------------------------------------Condición de display-------------------------------------------------//
		if(!gameover){
			if (Enemigo_v->obtener_estado()) Juego.draw(Enemigo_v->obtener_persona());
			if (Enemigo_p->obtener_estado()) Juego.draw(Enemigo_p->obtener_persona());
			if (Amigo_v->obtener_estado()) Juego.draw(Amigo_v->obtener_persona());
			Juego.draw(recursos->obtener_puntaje());
			for (int i = 0; i < vidas.size(); i++)
			{
				vidas[i].setPosition(50 * (i + 1), 540);
				Juego.draw(vidas[i]);
			}
			Juego.draw(recursos->obtener_cursor());
		}
		else {
			Juego.draw(recursos->obtener_h1());
			Juego.draw(recursos->obtener_h2());
		}
		Juego.display();
		//-------------------------------------------------Condición de disparo-------------------------------------------------//
		if (Enemigo_v->obtener_estado() && Enemigo_v->disparar(vidas, gameover, dt.asSeconds()) && !gameover) {
			Enemigo_v->cargar_persona("../img/enemigo_w/disparo.png");
		}
		if (Enemigo_p->obtener_estado() && Enemigo_p->disparar(vidas, gameover, dt.asSeconds()) && !gameover) {
			Enemigo_p->cargar_persona("../img/enemigo_d/disparo.png");
		}
		//-------------------------------------------------Bucle manejador de eventos-------------------------------------------------//
		while (Juego.pollEvent(evento)) {
			switch (evento.type) {
			case Event::Closed:
				Juego.close();
				break;
			case Event::MouseButtonPressed:
				if (Enemigo_v->atacado(Mouse::getPosition(Juego).x, Mouse::getPosition(Juego).y)) {
					puntos += 1;
					Enemigo_v->cargar_muerte(dt.asSeconds());
					Enemigo_v->cargar_persona("../img/enemigo_w/muerte.png");
				}

				if (Enemigo_p->atacado(Mouse::getPosition(Juego).x, Mouse::getPosition(Juego).y)) {
					puntos += 1;
					Enemigo_p->cargar_muerte(dt.asSeconds());
					Enemigo_p->cargar_persona("../img/enemigo_d/muerte.png");
				}

				if (Amigo_v->atacado(Mouse::getPosition(Juego).x, Mouse::getPosition(Juego).y)) {
					if(puntos>0) puntos -= 1;
					Amigo_v->cargar_muerte(dt.asSeconds());
					Amigo_v->cargar_persona("../img/inocente_w/muerte.png");
				}
				break;
			case Event::MouseMoved:
				recursos->posicion_cursor(evento.mouseMove.x, evento.mouseMove.y);
				break;
			case Event::KeyPressed:
				if (gameover){
					gameover = false;
					vidas.resize(3, recursos->obtener_vida());
					puntos = 0;
				}
				break;
			}
		}
	}
	return 0;
}