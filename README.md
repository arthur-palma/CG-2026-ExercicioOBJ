# Exercício Grau A - Computação Gráfica (Unisinos)

Este projeto consiste em uma aplicação utilizando **OpenGL moderna** para visualização e manipulação de modelos 3D em tempo real. O software permite carregar múltiplos arquivos `.obj`, organizar os modelos na cena e aplicar transformações geométricas individualmente em cada um.

## Requisitos de Sistema

* **Compilador:** Suporte a C++17 ou superior.
* **OpenGL:** Versão 3.3 ou superior.
* **Bibliotecas:** * GLFW (Gerenciamento de janelas e inputs)
  * GLAD (Carregamento de funções OpenGL)
  * GLM (Matemática para computação gráfica)

## Funcionalidades Implementadas

* **Leitura de Objetos:** Carregamento de modelos 3D a partir de arquivos `.obj`.
* **Exibição Múltipla:** Renderização de diversos objetos simultâneos na cena.
* **Seleção Cíclica:** Alternância de foco entre os objetos através de uma tecla dedicada.
* **Transformações Geométricas:**
  * Translação nos eixos X, Y e Z.
  * Rotação nos eixos X e Y.
  * Escala (Aumento e Diminuição).
* **Visualização:** Renderização do modelo sólido com sobreposição de *wireframe* (linhas de malha) para melhor percepção da geometria.
* **Responsividade:** Ajuste automático da proporção da câmera ao redimensionar a janela.

## Comandos de Interação

A aplicação utiliza o teclado para todas as interações. O objeto atualmente selecionado é destacado com cores, enquanto os demais permanecem em tons de cinza.

| Comando | Tecla | Descrição |
| :--- | :--- | :--- |
| **Seleção** | `TAB` | Alterna o foco entre os objetos da cena (cíclico). |
| **Translação X/Y** | `W`, `S`, `A`, `D` | Move o objeto selecionado para cima, baixo, esquerda e direita. |
| **Translação Z** | `Q`, `E` | Afasta ou aproxima o objeto (Eixo Z). |
| **Rotação X** | `R`, `F` | Rotaciona o objeto no eixo X. |
| **Rotação Y** | `T`, `G` | Rotaciona o objeto no eixo Y. |
| **Escala** | `Z`, `X` | Aumenta ou diminui o tamanho do objeto. |
| **Sair** | `ESC` | Fecha a aplicação. |

## Instruções de Compilação e Execução

### Estrutura de Pastas Sugerida
Para o correto funcionamento, certifique-se de que os arquivos do projeto estejam organizados em uma pasta de código-fonte (`src/`).

### Compilação (Via CMake)
1. Crie uma pasta `build` na raiz do projeto.
2. No terminal, acesse a pasta build e execute:
   ```bash
   cmake ..
   cmake --build .
