#include "helicoptero.h"


Helicoptero::Helicoptero()
{
    giro_helice = 0;
    giro_cabeceo = 0;
    giro_alabeo = 0;
    giro_giro = 0;
    velocidad_helice = 0;
    velocidad_cabeceo = 0;
    velocidad_alabeo = 0;
    velocidad_giro = 0;
    velocidad_vertical = 0;
    heli_x = heli_y = heli_z = 0;

    r1.set(ejex, -90);
    r_helice.set(ejez, giro_helice);
    r_giro.set(ejey, giro_giro);
    r_alabeo.set(ejex, -giro_alabeo);
    r_cabeceo.set(ejez, -giro_cabeceo);
    
    helicoptero.addHijo(&posicion);
    helicoptero.addHijo(&r_giro);
    helicoptero.addHijo(&r_alabeo);
    helicoptero.addHijo(&r_cabeceo);
    helicoptero.addHijo(&r1);
    helicoptero.addHijo(&cuerpo);
    helicoptero.addHijo(&t2);
    helicoptero.addHijo(&asp);

    asp.addHijo(&r_helice);
    asp.addHijo(&col);

    asp.addHijo(&t1);
    asp.addHijo(&helice);
}

void Helicoptero::cargar(const char *ply_cuerpo, const char *ply_helice)
{
    cuerpo.cargar(ply_cuerpo);
    helice.cargar(ply_helice);

    cuerpo.calcularPuntoPivote();
    helice.setPuntoPivote(Punto3D(-0.075, 0, 4));

    t1.set(-Vector3D(helice.getPuntoPivote()));
    t2.set(Vector3D(helice.getPuntoPivote()));
}

void Helicoptero::cargar(const char *ply)
{
    cuerpo.cargar("plys/heli.ply");
    helice.cargar("plys/helices.ply");
}

float Helicoptero::calcularVelocidadAscenso() {
    // Valores predefinidos (ficticios) para la demostración
    float densidadAire = 1.225;  // Densidad del aire en kg/m^3
    float areaRotor = 25.0;     // Área del rotor en m^2
    float longitudPala = 5.0;   // Longitud de la pala del rotor en metros
    float coeficienteSustentacion = 0.8;  // Coeficiente de sustentación (ficticio)
    float pesoHelicoptero = 5000.0;       // Peso del helicóptero en Newtons (ficticio)
    float velocidadHelicoptero = 20.0;    // Velocidad del helicóptero en m/s (valor ficticio)


    float velocidadAngularRotor = velocidad_helice * M_PI/180.0;   // Velocidad angular en rad/s 

    // Calcular la fuerza de sustentación (T)
    float fuerzaSustentacion = 0.5 * densidadAire * areaRotor * longitudPala * velocidadAngularRotor*velocidadAngularRotor * coeficienteSustentacion;

    // Calcular la resistencia al avance
    float coeficienteArrastre = 0.02;  // Coeficiente de arrastre (valor ficticio, debería ser obtenido de datos reales)
    float resistenciaAvance = 0.5 * coeficienteArrastre * densidadAire * areaRotor * velocidadHelicoptero*velocidadHelicoptero;

    // Calcular la velocidad de ascenso (Vz)
    double velocidadAscenso = (fuerzaSustentacion - resistenciaAvance) / pesoHelicoptero;

    return velocidadAscenso;
}

float Helicoptero::calcularVelocidadDescenso() {
    // El tiempo que ha pasado desde el ultimo frame
    float tiempo_pasado = 1.0/60.0;  // en segundos

    // Aceleración debida a la gravedad (aproximadamente 9.8 m/s²)
    float gravedad = 9.8;  // en m/s²

    // Actualizar la velocidad vertical
    velocidad_vertical += gravedad * tiempo_pasado;

    return velocidad_vertical;
}

void Helicoptero::actualizar()
{
    //IMPORTANTE: Las animaciones estan atadas a los FPS, por lo que si se cambian los FPS, se cambia la velocidad de las animaciones
    if(controlador.getSubir()){
        if(velocidad_helice < VELOCIDAD_MAXIMA_HELICE)
            velocidad_helice += 1;
        
    }
        
    if(controlador.getBajar()){
        if(velocidad_helice > 0)
            velocidad_helice -= 1;
        
        heli_y -= calcularVelocidadDescenso()* 1.0/180.0;
    }


    if(velocidad_helice > 0)
        velocidad_helice -= velocidad_helice * rozamiento;
    else if(velocidad_helice == 0)
        heli_y -= calcularVelocidadDescenso()* 1.0/180.0;
    else if(velocidad_helice < 0)
        velocidad_helice = 0;

    heli_y += calcularVelocidadAscenso()*2;
    

    if(heli_y > 0){
        if(controlador.getGiroIzquierda()){
            giro_giro += VELOCIDAD_MAXIMA_GIRO;
            if(giro_giro > 360)
                giro_giro -= 360;
        }

        if(controlador.getGiroDerecha()){
            giro_giro -= VELOCIDAD_MAXIMA_GIRO;
            if(giro_giro < 0)
                giro_giro += 360;
        }

        if(controlador.getAlabeoIzquierda()){
            giro_alabeo += VELOCIDAD_MAXIMA_ALABEO;
            if(giro_alabeo > ANGULO_MAXIMO_ALABEO)
                giro_alabeo = ANGULO_MAXIMO_ALABEO;
        }

        if(controlador.getAlabeoDerecha()){
            giro_alabeo -= VELOCIDAD_MAXIMA_ALABEO;
            if(giro_alabeo < -ANGULO_MAXIMO_ALABEO)
                giro_alabeo = -ANGULO_MAXIMO_ALABEO;
        }

        if(controlador.getCabeceoDelante()){
            giro_cabeceo += VELOCIDAD_MAXIMA_CABECEO;
            if(giro_cabeceo > ANGULO_MAXIMO_CABECEO)
                giro_cabeceo = ANGULO_MAXIMO_CABECEO;
        }

        if(controlador.getCabeceoDetras()){
            giro_cabeceo -= VELOCIDAD_MAXIMA_CABECEO;
            if(giro_cabeceo < -ANGULO_MAXIMO_CABECEO)
                giro_cabeceo = -ANGULO_MAXIMO_CABECEO;
        }

        giro_alabeo *= 0.99;
        giro_cabeceo *= 0.99;

        heli_z += -0.01 * giro_alabeo * cos(giro_giro * M_PI/180.0) + 0.01 * giro_cabeceo * sin(-giro_giro * M_PI/180.0);
        heli_x += 0.01 * giro_cabeceo * cos(-giro_giro * M_PI/180.0) - 0.01 * giro_alabeo * sin(giro_giro * M_PI/180.0);
    }else{
        giro_alabeo *= 0.8;
        giro_cabeceo *= 0.8;

        if(giro_alabeo < 0.01 && giro_alabeo > -0.01)
            giro_alabeo = 0;

        if(giro_cabeceo < 0.01 && giro_cabeceo > -0.01)
            giro_cabeceo = 0;

        heli_y = 0;
    }
    
    
    giro_helice += velocidad_helice;
    posicion.set(Vector3D(heli_x, heli_y, heli_z));
    r_helice.set(ejez, giro_helice);
    r_giro.set(ejey, giro_giro);
    r_alabeo.set(ejex, -giro_alabeo);
    r_cabeceo.set(ejez, -giro_cabeceo);
}

void Helicoptero::draw()
{
    //actualizar();
    helicoptero.draw();
}

ControladorHelicoptero::ControladorHelicoptero(){
    estadoPorDefecto();
}

void ControladorHelicoptero::estadoPorDefecto(){
    cabeceo_delante = cabeceo_detras = false;
    alabeo_izquierda = alabeo_derecha = false;
    giro_derecha = giro_izquierda = false;
    subir = bajar = false;
}

void ControladorHelicoptero::irAlante(){
    cabeceo_delante = true;
}

void ControladorHelicoptero::irAtras(){
    cabeceo_detras = true;
}

void ControladorHelicoptero::alabeoIzquierda(){
    alabeo_izquierda = true;
}

void ControladorHelicoptero::alabeoDerecha(){
    alabeo_derecha = true;
}

void ControladorHelicoptero::giroDerecha(){
    giro_derecha = true;
}

void ControladorHelicoptero::giroIzquierda(){
    giro_izquierda = true;
}

void ControladorHelicoptero::subirHelicoptero(){
    subir = true;
}

void ControladorHelicoptero::bajarHelicoptero(){
    bajar = true;
}

void ControladorHelicoptero::actualizar(){
    estadoPorDefecto();
}