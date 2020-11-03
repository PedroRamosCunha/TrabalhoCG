/* para linux, instalar os pacotes libglfw3-dev mesa-common-dev libglew-dev */
/* para compilar no linux: gcc main.c -lglfw -lGL -lGLEW -lm */

/* para windows, instalar bibliotecas compiladas do glfw3 e glew no ambiente mingw */
/* para compilar no windows: gcc main.c -lglfw3dll -lglew32 -lopengl32 */


#include <GL/glew.h>  
#define  GLFW_DLL
#define  GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h> 
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#define pi 3.14
#define M_PI 3.14159265358979323846
#define TAM 0.2
 

// variaveis globais
typedef struct{
    float x, y;
} coordenadas;

float t_x   = 0.0f , t_x2   = 0.0f; 
float t_y   = 0.0f , t_y2   = 0.0f;
float s     = 1.0f , s2     = 1.0f;
float angle = 0.0f , angle2 = 0.0f;

// Funcao para processar eventos de teclado (W,A,S,D e setas)
static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
    //printf("Pressionando tecla %d\n", key);

    if(key == 68) t_x += 0.01; // tecla D
    if(key == 65) t_x -= 0.01; // tecla A

    if(key == 87) t_y += 0.01; // tecla W
    if(key == 83) t_y -= 0.01; // tecla S

    if(key == 265) s += 0.01; // seta para cima
    if(key == 264) s -= 0.01; // seta para baixo   

    if(key == 263) angle += 0.01; // seta da direita
    if(key == 262) angle -= 0.01; // seta da esquerda

    if(key == 326) t_x2 += 0.01; // tecla D
    if(key == 324) t_x2 -= 0.01; // tecla A

    if(key == 328) t_y2 += 0.01; // tecla W
    if(key == 322) t_y2 -= 0.01; // tecla S

    if(key == 323) s2 += 0.01; // seta para cima
    if(key == 321) s2 -= 0.01; // seta para baixo   

    if(key == 327) angle2 += 0.01; // seta da direita
    if(key == 329) angle2 -= 0.01; // seta da esquerda

}

void multiplyMatrix(float *a, float *b, float *res){

    for(int i = 0; i < 4; i++){
        int line = 4 * i;
        res[line + 0] = a[line + 0] * b[0] + a[line + 1] * b[4] + a[line + 2] * b[8] + a[line + 3] * b[12];
        res[line + 1] = a[line + 0] * b[1] + a[line + 1] * b[5] + a[line + 2] * b[9] + a[line + 3] * b[13];
        res[line + 2] = a[line + 0] * b[2] + a[line + 1] * b[6] + a[line + 2] * b[10] + a[line + 3] * b[14];
        res[line + 3] = a[line + 0] * b[3] + a[line + 1] * b[7] + a[line + 2] * b[11] + a[line + 3] * b[15];
    }

}

 
int main(void){
 
    unsigned flag=1;    
    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(800, 800, "Trabalho 1", NULL, NULL);
    glfwMakeContextCurrent(window);
    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s", glewGetErrorString(GlewInitResult));


    // GLSL para Vertex Shader
    char* vertex_code =
    "attribute vec2 position;\n"
    "uniform mat4 mat_transformation;\n"
    "void main()\n"
    "{\n"
    "    gl_Position = mat_transformation*vec4(position, 0.0, 1.0);\n"
    "}\n";

    // GLSL para Fragment Shader
    char* fragment_code =
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

    // Requisitando slot para a GPU para nossos programas Vertex e Fragment Shaders
    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    // Associando nosso código-fonte GLSL aos slots solicitados
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

    // Compilando o Vertex Shader e verificando erros
    glCompileShader(vertex);

    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n",&info);

    }

    

    // Compilando o Fragment Shader e verificando erros
    glCompileShader(fragment);

    isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(fragment, infoLength, NULL, info);

        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n",&info);

    }

    // Associando os programas compilado ao programa principal
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Linkagem do programa e definindo como default
    glLinkProgram(program);
    glUseProgram(program);
    
     
    //Object 1 
    coordenadas vertices[73];

    vertices[0].x = 0.0f;
    vertices[0].y = 0.0f;

    float step = M_PI/8;
    float ang = 0.0f;

    for(int i = 1; i < 18 - 1; i++){
        if(i % 2 == 1){
            vertices[i].x = TAM * cos(ang);
            vertices[i].y = TAM * sin(ang);
        }else{
            vertices[i].x = 0.5 * TAM * cos(ang);
            vertices[i].y = 0.5 * TAM * sin(ang);
        }

        ang += step;
    }

    vertices[17].x = vertices[1].x;
    vertices[17].y = vertices[1].y;


    srand(time(NULL));
    //Object 2
    for (int i = 18; i < 36; i++)
    {
        if(flag)
        {
            vertices[i].x = 0.0000f;
            vertices[i].y = 0.0000f;
            flag = 0;
        }
        else
        {
        vertices[i].x = 0.0001*(rand()%5000);
        vertices[i].y = 0.0001*(rand()%5000);
        flag++;
        }
    }
    vertices[35].x = vertices[18].x;
    vertices[35].y = vertices[18].y;

    step = M_PI/6;
    angle = 0.0f;

    for (int i = 37; i < sizeof(vertices); i+=3){
        float smallstep = step/5;
        vertices[i].x = 0.8 * TAM * cos(angle + 2 * smallstep);
        vertices[i].y = 0.8 * TAM * sin(angle + 2 * smallstep);

        vertices[i+1].x = 1.0 * TAM * cos(angle + 3 * smallstep);
        vertices[i+1].y = 1.0 * TAM * sin(angle + 3 * smallstep);

        vertices[i+2].x = 0.8 * TAM * cos(angle + 4 * smallstep);
        vertices[i+2].y = 0.8 * TAM * sin(angle + 4 * smallstep);    

        angle += step;
    }

    vertices[36] = vertices[72];

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // Abaixo, nós enviamos todo o conteúdo da variável vertices.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // Associando variáveis do programa GLSL (Vertex Shaders) com nossos dados
    GLint loc = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) 0); // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml
 

    // Associando nossa janela com eventos de teclado
    glfwSetKeyCallback(window, key_event); // teclado

    // Exibindo nossa janela
    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(6.0, 1.0, 3.0, 1.0);

        float mat_aux[16];
        float mat_final[16];

        float mat_scale[16] = {
            s   , 0.0f, 0.0f, 0.0f,
            0.0f,    s, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        
        float mat_rotation[16] = {
            cos(angle), -sin(angle), 0.0f, 0.0f,
            sin(angle),  cos(angle), 0.0f, 0.0f,
            0.0f      ,  0.0f      , 1.0f, 0.0f,
            0.0f      ,  0.0f      , 0.0f, 1.0f
        };

        // criando a matriz de translacao
        float mat_translation[16] = {
            1.0f, 0.0f, 0.0f, t_x - 0.2f,
            0.0f, 1.0f, 0.0f, t_y ,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
        
        multiplyMatrix(mat_rotation, mat_scale, mat_aux);
        multiplyMatrix(mat_translation, mat_aux, mat_final);


        // enviando a matriz de transformacao para a GPU, vertex shader, variavel mat_transformation
        loc = glGetUniformLocation(program, "mat_transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, mat_final);

	    //renderizando
        glDrawArrays(GL_TRIANGLE_FAN, 0, 18);
    
        mat_scale[0] = s2;
        mat_scale[5] = s2;

        mat_rotation[0] = cos(angle2);
        mat_rotation[1] = -sin(angle2);
        mat_rotation[4] = sin(angle2);
        mat_rotation[5] = cos(angle2);

        mat_translation[3] = t_x2 + 0.2f;
        mat_translation[7] = t_y2;
        
        multiplyMatrix(mat_rotation, mat_scale, mat_aux);
        multiplyMatrix(mat_translation, mat_aux, mat_final);

        // enviando a matriz de transformacao para a GPU, vertex shader, variavel mat_transformation
        loc = glGetUniformLocation(program, "mat_transformation");
        glUniformMatrix4fv(loc, 1, GL_TRUE, mat_final);
    
	 //renderizando
        //glDrawArrays(GL_TRIANGLE_STRIP, 18, 18);

        for(int j = 0; j < 12; j++){
            glDrawArrays(GL_TRIANGLE_STRIP, 37 + 3*j, 3);
        }

        glfwSwapBuffers(window);
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
