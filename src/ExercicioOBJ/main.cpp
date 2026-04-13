#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"

struct Mesh {
    GLuint VAO;
    int nVertices;
    glm::vec3 pos, rot, sca, color;
    Mesh() : pos(0.0f), rot(0.0f), sca(1.0f), color(0.7f, 0.2f, 0.2f) {}
};

std::vector<Mesh> objects;
int selectedIndex = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int loadOBJ(std::string path, GLuint &VAO) {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> temp_vertices;
    std::ifstream file(path);
    if (!file.is_open()) file.open("../src/ExercicioOBJ/" + path);
    if (!file.is_open()) return 0;

    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 2) == "v ") {
            std::istringstream s(line.substr(2));
            glm::vec3 v; s >> v.x >> v.y >> v.z;
            temp_vertices.push_back(v);
        } else if (line.substr(0, 2) == "f ") {
            std::string val;
            std::istringstream s(line.substr(2));
            while (s >> val) {
                int vIdx = std::stoi(val.substr(0, val.find('/'))) - 1;
                vertices.push_back(temp_vertices[vIdx]);
            }
        }
    }
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    return vertices.size();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS) selectedIndex = (selectedIndex + 1) % objects.size();

    float s = 0.05f; float r = 5.0f;
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        auto& o = objects[selectedIndex];
        if (key == GLFW_KEY_W) o.pos.y += s; if (key == GLFW_KEY_S) o.pos.y -= s;
        if (key == GLFW_KEY_A) o.pos.x -= s; if (key == GLFW_KEY_D) o.pos.x += s;
        if (key == GLFW_KEY_Q) o.pos.z -= s; if (key == GLFW_KEY_E) o.pos.z += s;
        if (key == GLFW_KEY_R) o.rot.x += r; if (key == GLFW_KEY_F) o.rot.x -= r;
        if (key == GLFW_KEY_T) o.rot.y += r; if (key == GLFW_KEY_G) o.rot.y -= r;
        if (key == GLFW_KEY_Z) o.sca += glm::vec3(0.05f);
        if (key == GLFW_KEY_X) o.sca -= glm::vec3(0.05f);
    }
}

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Unisinos - Comp. Grafica", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);

    Shader shader("shader.vs", "shader.fs");
    Mesh m1, m2, m3;
    
    m1.nVertices = loadOBJ("Suzanne.obj", m1.VAO); 
    m1.pos.x = -2.0f;
    
    m2.nVertices = loadOBJ("Cube.obj", m2.VAO); 
    m2.pos.x = 2.0f; 
    m2.color = glm::vec3(0.2f, 0.7f, 0.2f);
    
    m3.nVertices = loadOBJ("Nave.obj", m3.VAO);
    m3.pos = glm::vec3(0.0f, 0.0f, 0.0f);
    m3.color = glm::vec3(0.2f, 0.2f, 0.7f);

    if (m1.nVertices > 0) objects.push_back(m1);
    if (m2.nVertices > 0) objects.push_back(m2);
    if (m3.nVertices > 0) objects.push_back(m3);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
        
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        float aspectRatio = (float)width / (float)(height == 0 ? 1 : height);
        
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f));
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
        shader.setMat4("view", view); 
        shader.setMat4("projection", proj);

        for (int i = 0; i < objects.size(); i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, objects[i].pos);
            model = glm::rotate(model, glm::radians(objects[i].rot.x), glm::vec3(1,0,0));
            model = glm::rotate(model, glm::radians(objects[i].rot.y), glm::vec3(0,1,0));
            model = glm::scale(model, objects[i].sca);
            shader.setMat4("model", model);

            shader.setVec3("objectColor", (i == selectedIndex) ? objects[i].color : glm::vec3(0.4f));
            glBindVertexArray(objects[i].VAO);
            glDrawArrays(GL_TRIANGLES, 0, objects[i].nVertices);

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            shader.setVec3("objectColor", glm::vec3(1.0f));
            glDrawArrays(GL_TRIANGLES, 0, objects[i].nVertices);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        glfwSwapBuffers(window); 
        glfwPollEvents();
    }
    glfwTerminate(); 
    return 0;
}