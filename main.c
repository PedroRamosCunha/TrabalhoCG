/**
 *  Title: Trabalho 1 de Computação Gráfica - SSC0650
 * 
 *  Alunos:                                     Nº USP:
 *  Marcos Antonio Victor Arce                  10684621
 *  Pedro Ramos Cunha                           10892248
 *
 *  Compilação no linux: gcc main.c -lglfw -lGL -lGLEW -lm
 * 
*/

/**
 *      Inclusão de Bibliotecas
 * 
*/
#include <GL/glew.h>  
#define  GLFW_DLL
#define  GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> 
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

/**
 *  Definições gerais
 *  
*/

#define M_PI 3.14159265358979323846
#define TAM 0.1
#define TAM3 0.05

/**
 *  Struct de coordenadas de um ponto cartesiano em R^2.
 *  
*/
typedef struct{
    float x, y;
} coordenadas;

/**
 *  Variáveis da matriz de transformação. 
 *  t_x e t_y são para translação automática da estrela
 *  p_x e p_y são para translação do passáro
 *  s é para escala da estrela
 *  angle(n) é para rotação da estrela e da flor
 * 
*/

float t_x   =  0.0f, t_y = 0.0f;
float p_x   =  0.0f, p_y = 0.0f;
float s     =  1.0f;
float angle =  0.0f , angle2 = 0.0f;

/**
 * Subrotina para receber eventos de I/O
 *  No caso são para pegar as teclas do teclado.
 *  Para funcionar, as configurações do teclado devem estar em Pt - Brasil
 *  senão as setas não funcionam.
*/

static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){


    // Primeira figura
    if(key == 68 && p_x <  0.85) p_x += 0.01; // tecla D
    if(key == 65 && p_x > -0.85) p_x -= 0.01; // tecla A

    if(key == 87 && p_y <  0.75) p_y += 0.01; // tecla W
    if(key == 83 && p_y > -0.75) p_y -= 0.01; // tecla S

    if(key == 265 && s < 2.0f) s += 0.01; // seta para cima
    if(key == 264 && s > 0.5f) s -= 0.01; // seta para baixo   

    // Segunda figura
    if(key == 263) angle2 += 0.01; // seta da direita
    if(key == 262) angle2 -= 0.01; // seta da esquerda

}


/**
 * Subrotina para a multiplicação de matrizes
 * 
*/
void multiplyMatrix(float *a, float *b, float *res){

    for(int i = 0; i < 4; i++){
        int line = 4 * i;
        res[line + 0] = a[line + 0] * b[0] + a[line + 1] * b[4] + a[line + 2] * b[8] + a[line + 3] * b[12];
        res[line + 1] = a[line + 0] * b[1] + a[line + 1] * b[5] + a[line + 2] * b[9] + a[line + 3] * b[13];
        res[line + 2] = a[line + 0] * b[2] + a[line + 1] * b[6] + a[line + 2] * b[10] + a[line + 3] * b[14];
        res[line + 3] = a[line + 0] * b[3] + a[line + 1] * b[7] + a[line + 2] * b[11] + a[line + 3] * b[15];
    }

}
/**
 * Subrotina para traçar as coordenadas do primeiro objeto no
 * vetor de coordenadas.
 * As cordenadas do primeiro objeto vão de 0 a 17 posições do vetor.
*/
void drawFirstObject(coordenadas* vertices){
    vertices[0].x = 0.0f;
    vertices[0].y = 0.0f;

    float step = M_PI/8;
    float ang = 0.0f;

    for(int i = 1; i < 18 - 1; i++){
        if(i % 2 == 1){
            vertices[i].x = 0.6 * TAM * cos(ang);
            vertices[i].y = 0.6 * TAM * sin(ang);
        }else{
            vertices[i].x = 0.3 * TAM * cos(ang);
            vertices[i].y = 0.3 * TAM * sin(ang);
        }

        ang += step;
    }

    vertices[17].x = vertices[1].x;
    vertices[17].y = vertices[1].y;
}

void drawThirdObject(coordenadas* vertices){

    coordenadas third[] = {
         0.0f, 0.0f,
         1.0f, 3.0f,
         0.0f, 1.0f,
        -1.0f, 3.0f,
         2.0f, 0.0f,
         1.0f, 1.0f,
        -1.0f, 1.0f,
        -2.0f, 0.0f,
         2.0f, 0.0f
    };
    
    for(int i = 0; i < sizeof(third); i++){
        vertices[i + 70].x = TAM3 * third[i].x;
        vertices[i + 70].y = TAM3 * third[i].y;
    }
}
/**
 * Subrotina para traçar as coordenadas do segundo objeto no
 * vetor de coordenadas.
 * As cordenadas do segundo objeto vão de 17 a 69 posições do vetor.
*/
void drawSecondObject(coordenadas* vertices){
    float step = M_PI/6;
    float ang = 0.0f;

    for (int i = 18; i < 66; i+=4){
        float smallstep = step/7;

        vertices[i].x = 0.0f;
        vertices[i].y = 0.0f;

        vertices[i+1].x = 0.7 * TAM * cos(ang + 2 * smallstep);
        vertices[i+1].y = 0.7 * TAM * sin(ang + 2 * smallstep);

        vertices[i+2].x = 1.0 * TAM * cos(ang + 4 * smallstep);
        vertices[i+2].y = 1.0 * TAM * sin(ang + 4 * smallstep);

        vertices[i+3].x = 0.7 * TAM * cos(ang + 6 * smallstep);
        vertices[i+3].y = 0.7 * TAM * sin(ang + 6 * smallstep);    

        ang += step;
    }

        vertices[66].x = 0.002f;
        vertices[66].y = 0.0f;

        vertices[67].x = -0.002f;
        vertices[67].y = 0.0f;

        vertices[68].x = -0.002f;
        vertices[68].y = -0.3f;

        vertices[69].x = +0.002f;
        vertices[69].y = -0.3f;
}



/**
 * Main
 * Nela as chamadas das funções de inicialização das janelas e 
 * ações junto a GPU (envio das matrizes de tranformação, do vetor de coordenadas, etc)
 * 
*/



int main(void){
    
/**
 * Inicialização da janela do gflow
 *  
*/
    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(1000, 800, "Trabalho 1", NULL, NULL);
    glfwMakeContextCurrent(window);
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s", glewGetErrorString(GlewInitResult));

/**
 * Conficuração do vertex shader GLSL
 * 
*/
    char* vertex_code =
    "attribute vec2 position;\n"
    "uniform mat4 mat_transformation;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = mat_transformation*vec4(position, 0.0, 1.0);\n"
    "}\n";

/**
 * Configuração do Fragment Shader para GLSL
 * 
*/
    char* fragment_code =
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = color;\n"
    "}\n";

    /**
     * Funções de solicitação de slots da GPU para o vertex e fragment
     * e funções de compilação e teste das configurações do vertex.
     * 
    */
    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);
    glCompileShader(vertex);
    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
    
    /**
     * Tratamento do Erro de compilação do vertex
     * 
    */
    if(isCompiled == GL_FALSE){
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n",&info);
    }

    
    
    /**
     * Funções de teste e compilação do Fragment
     * 
    */
    glCompileShader(fragment);
    isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);

    /**
     * Tratamento do Erro de compilação do fragment
     * 
    */
    if(isCompiled == GL_FALSE){
        int infoLength = 512;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);
        char info[infoLength];
        glGetShaderInfoLog(fragment, infoLength, NULL, info);
        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n",&info);
    }


    /**
     *  Funçoes de linkagem com a janela.
    */
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glUseProgram(program);
    
    
    
    /**
     * Vetor de coordenadas
     * 
    */
    coordenadas vertices[79];

    // Desenhar objetos
    drawFirstObject(vertices);  // Estrela
    drawSecondObject(vertices); // Flor
    drawThirdObject(vertices);  // Passáro

    // Cria um buffer e conecta-o
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // Envia para o buffer as coordenadas
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // Localizar variável posição do programa GLSL (Vertex Shaders)
    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) 0);

    // Localizar variável cor 
    GLint loc_color = glGetUniformLocation(program, "color");

    // Gerenciar eventos do teclado
    glfwSetKeyCallback(window, key_event);

    // Exibir janela
    glfwShowWindow(window);


    float x = 0.0f, step = M_PI/900;
    int mult = 1.0;

    while (!glfwWindowShouldClose(window)){

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        // Recebendo a localização da matriz de transformação
        loc = glGetUniformLocation(program, "mat_transformation");

        float mat_aux[16];
        float mat_final[16];

        //////// PRIMEIRO OBJETO
        t_x = x;
        t_y = mult * 0.1 * sin(4*x); // Faz o caminho da senoide
        
        if(fabs(t_y) < 0.001f && fabs(x) > 0.001f){
            step *= (-1);
            mult *= (-1);
        }
            
        x += step;

        // MATRIZ DE ESCALA
        float mat_scale[16] = {
            s   , 0.0f, 0.0f, 0.0f,
            0.0f,    s, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        
        // MATRIZ DE ROTAÇÃO
        float mat_rotation[16] = {
            cos(angle), -sin(angle), 0.0f, 0.0f,
            sin(angle),  cos(angle), 0.0f, 0.0f,
            0.0f      ,  0.0f      , 1.0f, 0.0f,
            0.0f      ,  0.0f      , 0.0f, 1.0f
        };

        // MATRIZ DE TRANSLAÇÃO
        float mat_translation[16] = {
            1.0f, 0.0f, 0.0f, t_x ,
            0.0f, 1.0f, 0.0f, t_y + 0.5f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        // Multiplica as matrizes
        multiplyMatrix(mat_rotation, mat_scale, mat_aux);
        multiplyMatrix(mat_translation, mat_aux, mat_final);

        // Para deixar a estrela girando
        angle -= 0.005;

        //Enviando a matriz de transformação para essa figura
        glUniformMatrix4fv(loc, 1, GL_TRUE, mat_final);

	    //Renderizando a cor
        glUniform4f(loc_color, 254.0/255.0, 254.0/255.0, 68.0/255.0, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 18);


        //////// SEGUNDO OBJETO
        
        // Alterando a matriz de translação para o segundo objeto
        mat_translation[3] = -0.6f;
        mat_translation[7] = -0.55f;

        glUniformMatrix4fv(loc, 1, GL_TRUE, mat_translation);

        // Cabo da flor
        glUniform4f(loc_color, 0.0, 128.0/255.0, 0.0/255.0, 1.0f); // Cor verde
        glDrawArrays(GL_TRIANGLE_STRIP, 66, 4);

        // Alterando as matrizes de rotação e escala para o segundo objeto
        mat_scale[0] = 1.0f;
        mat_scale[5] = 1.0f;

        mat_rotation[0] = cos(angle2);
        mat_rotation[1] = -sin(angle2);
        mat_rotation[4] = sin(angle2);
        mat_rotation[5] = cos(angle2);        
        
        multiplyMatrix(mat_rotation, mat_scale, mat_aux);
        multiplyMatrix(mat_translation, mat_aux, mat_final);

        // enviando a matriz de transformacao para a GPU, vertex shader, variavel mat_transformation
        glUniformMatrix4fv(loc, 1, GL_TRUE, mat_final);
    
        // Cor roxa das pétalas
        glUniform4f(loc_color, 150.0/255.0, 0.0, 205.0/255.0, 1.0f);
        
        for(int j = 0; j < 12; j++)
            glDrawArrays(GL_TRIANGLE_FAN, 18 + 4*j, 4);

        //////// TERCEIRO OBJETO

        // Alterando a matriz de translação para o terceiro objeto
        mat_translation[3] = p_x;
        mat_translation[7] = p_y;        

        glUniformMatrix4fv(loc, 1, GL_TRUE, mat_translation);

	    //renderizando
        glUniform4f(loc_color, 107.0/255.0, 142.0/255.0, 35.0/255.0, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 70, 4);
        glDrawArrays(GL_TRIANGLE_STRIP, 74, 5);

        glfwSwapBuffers(window);
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
