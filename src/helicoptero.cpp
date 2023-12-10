#include "helicoptero.h"

// Constantes
const float ACELERACION_HELICE = 360 * 1000.0;
const float VELOCIDAD_MAXIMA_CABECEO = 360.0 * 1;
const float VELOCIDAD_MAXIMA_ALABEO = 360.0 * 1;
const float VELOCIDAD_MAXIMA_GIRO = 360.0 * 2;
const float VELOCIDAD_MAXIMA_HELICE = 360.0 * 850.0;
const float VELOCIDAD_AVANCE = 10.0;
const float ANGULO_MAXIMO_ALABEO = 45.0;
const float ANGULO_MAXIMO_CABECEO = 45.0;
const float ROZAMIENTO = 0.0015;

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
    tiempo_cayendo = 0;

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

void Helicoptero::cargar()
{
    cargar("plys/heli.ply", "plys/helices.ply");
}

float Helicoptero::calcularVelocidadAscenso() {
    float velocidadAngularRotor = velocidad_helice * M_PI/180.0;   // Velocidad angular en rad/s 
    float velocidadHelicoptero = velocidad_vertical;    // Velocidad del helicóptero en m/s (valor ficticio)

    // Calcular la fuerza de sustentación (T)
    float fuerzaSustentacion = 0.5 * densidadAire * areaRotor * longitudPala * velocidadAngularRotor*velocidadAngularRotor * coeficienteSustentacion;

    // Calcular la resistencia al avance
    float resistenciaAvance = 0.5 * coeficienteArrastre * densidadAire * areaRotor * velocidadHelicoptero*velocidadHelicoptero;

    // Calcular la velocidad de ascenso (Vz)
    double velocidadAscenso = (fuerzaSustentacion - resistenciaAvance) / pesoHelicoptero;

    return velocidadAscenso;
}

float Helicoptero::calcularVelocidadDescenso(double tiempoTranscurrido) {
    // Aceleración debida a la gravedad (aproximadamente 9.8 m/s²)
    float gravedad = 9.8;  // en m/s²

    // Calcular la velocidad vertical
    float velocidad = gravedad * tiempoTranscurrido;

    return velocidad;
}

void Helicoptero::actualizar()
{
    // Actualiza los relojes
    FiguraAnimada::actualizar();
    
    // Obtiene el tiempo transcurrido desde la última actualización
    double tiempoTranscurrido = getTiempoTranscurrido();

    // Si sube o baja el helicóptero, se actualiza la velocidad de las hélices
    if(controlador.getSubir()){
        if(velocidad_helice < VELOCIDAD_MAXIMA_HELICE)
            velocidad_helice += ACELERACION_HELICE * tiempoTranscurrido;
        tiempo_cayendo = 0;
    }else{
        if(tiempo_cayendo < 1000) tiempo_cayendo += tiempoTranscurrido*100;
        else tiempo_cayendo = 1000;
    }
        
    // Si sube o baja el helicóptero, se actualiza la velocidad de las hélices
    if(controlador.getBajar()){
        if(velocidad_helice > 0){
            velocidad_helice -= ACELERACION_HELICE * tiempoTranscurrido;
        }
    }

    // Se aplica el rozamiento a la velocidad de las hélices
    if(velocidad_helice > 0)
        velocidad_helice -= velocidad_helice * ROZAMIENTO;
    else if(velocidad_helice < 0)// Para no tener velocidades negativas
        velocidad_helice = 0;


    //Balance entre velocidad de ascenso y descenso
    //para hacer mas o menos controlable el helicoptero

    velocidad_vertical = calcularVelocidadAscenso() / 50.0;
    if(velocidad_vertical == 0) tiempo_cayendo = 0;
    velocidad_vertical -= calcularVelocidadDescenso(tiempo_cayendo);
    heli_y += velocidad_vertical * tiempoTranscurrido;

    // Si el helicoptero esta en el aire
    if(heli_y > 0){
        // Si el helicoptero esta en el aire, puede moverse en cualquier direccion
        if(controlador.getGiroIzquierda()){
            giro_giro += VELOCIDAD_MAXIMA_GIRO * tiempoTranscurrido;
            if(giro_giro > 360)
                giro_giro -= 360;
        }

        if(controlador.getGiroDerecha()){
            giro_giro -= VELOCIDAD_MAXIMA_GIRO * tiempoTranscurrido;
            if(giro_giro < 0)
                giro_giro += 360;
        }

        if(controlador.getAlabeoIzquierda()){
            giro_alabeo += VELOCIDAD_MAXIMA_ALABEO * tiempoTranscurrido;
            if(giro_alabeo > ANGULO_MAXIMO_ALABEO)
                giro_alabeo = ANGULO_MAXIMO_ALABEO;
        }

        if(controlador.getAlabeoDerecha()){
            giro_alabeo -= VELOCIDAD_MAXIMA_ALABEO * tiempoTranscurrido;
            if(giro_alabeo < -ANGULO_MAXIMO_ALABEO)
                giro_alabeo = -ANGULO_MAXIMO_ALABEO;
        }

        if(controlador.getCabeceoDelante()){
            giro_cabeceo += VELOCIDAD_MAXIMA_CABECEO * tiempoTranscurrido;
            if(giro_cabeceo > ANGULO_MAXIMO_CABECEO)
                giro_cabeceo = ANGULO_MAXIMO_CABECEO;
        }

        if(controlador.getCabeceoDetras()){
            giro_cabeceo -= VELOCIDAD_MAXIMA_CABECEO * tiempoTranscurrido;
            if(giro_cabeceo < -ANGULO_MAXIMO_CABECEO)
                giro_cabeceo = -ANGULO_MAXIMO_CABECEO;
        }

        //Para hacer que el helicoptero vuelva a la posicion de equilibrio
        giro_alabeo *= 0.99;
        giro_cabeceo *= 0.99;

        // Distancia recorrida en el eje xz
        float distancia_avance = VELOCIDAD_AVANCE * tiempoTranscurrido;
        // Ángulo de giro en radianes
        float giro_radianes = giro_giro * M_PI/180.0;
    
        // z += d * (gCabeceo * sin(-gGiro) - gAlabeo * cos(gGiro))
        // x += d * (gCabeceo * cos(-gGiro) - gAlabeo * sin(gGiro))
        heli_z += distancia_avance * (giro_cabeceo * sin(-giro_radianes) - giro_alabeo * cos(giro_radianes));
        heli_x += distancia_avance * (giro_cabeceo * cos(-giro_radianes) - giro_alabeo * sin(giro_radianes));
    }else{// Si el helicoptero esta en el suelo

        //Para hacer que el helicoptero vuelva a la posicion de equilibrio
        giro_alabeo *= 0.8;
        giro_cabeceo *= 0.8;

        //Para que no se quede bailando en el suelo
        if(giro_alabeo < 0.01 && giro_alabeo > -0.01)
            giro_alabeo = 0;

        if(giro_cabeceo < 0.01 && giro_cabeceo > -0.01)
            giro_cabeceo = 0;

        //Para que no se salga del suelo
        heli_y = 0;
    }
    
    // Se actualiza el giro de la hélice
    giro_helice += velocidad_helice * tiempoTranscurrido;
    if(giro_helice > 360)
        giro_helice -= 360;

    // Actualiza las rotaciones y traslaciones
    posicion.set(Vector3D(heli_x, heli_y, heli_z));
    r_helice.setAngulo(giro_helice);
    r_giro.setAngulo(giro_giro);
    r_alabeo.setAngulo(-giro_alabeo);
    r_cabeceo.setAngulo(-giro_cabeceo);

    // Actualiza el controlador
    controlador.actualizar();
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