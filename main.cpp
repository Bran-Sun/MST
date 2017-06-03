#include "mst.h"
#include <ctime>
#include <cstdlib>
#include "generate.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


using namespace std;

const GLchar* vertexShaderSource = "#version 330 core\n"
  "layout (location = 0) in vec3 position;\n"
  "void main()\n"
  "{\n"
  "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
  "}\0";
const GLchar* fragmentShader1Source = "#version 330 core\n"
  "out vec4 color;\n"
  "void main()\n"
  "{\n"
  "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\n\0";
const GLchar* fragmentShader2Source = "#version 330 core\n"
  "out vec4 color;\n"
  "void main()\n"
  "{\n"
  "color = vec4(1.0f, 1.0f, 0.0f, 1.0f); // The color yellow \n"
  "}\n\0";


int main(int argc, char** argv)
{
  MST mst;
  MST check;
  Delaunay_triangulation_2 dt;
  vector<Point_2> vertices;
  load_vertices(vertices, "../../data/testcase1/testcase.txt");
//   random_generate(vertices);


  GLfloat Vertices[Point_Num * 18]={0.0};  //to draw the origin Delaunay_triangulation
  GLfloat min_edge[(Point_Num - 1) * 6]={0.0};  // to draw the mst
  int min_num = 0;   //the number of edges of Delaunay_triangulation
  int edge_num = 0;  //the number of edges of mst

//load vertices to MST class
  mst.load_nodes(vertices);

//generate Delaunay_triangulation
  dt.insert(vertices.begin(), vertices.end());

//load edges to class MST
  load_to_mst(dt, mst, Vertices, edge_num);
  mst.find_min_route();
  mst.print_to_verties(min_edge, min_num);

  mst.print_min_route(cout);

  //initialize the window
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow* window = glfwCreateWindow(1200, 900, "LearnOpenGL", nullptr,
                                            nullptr);
  if (window == nullptr)
  {
    cout << "Failed to create GLFW window" << endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)
  {
    cout << "Failed to initialize GLEW" << endl;
    return -1;
  }

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  //initialize shaders and programs
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); // The first fragment shader that outputs the color orange
  GLuint fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER); // The second fragment shader that outputs the color yellow
  GLuint shaderProgramOrange = glCreateProgram();
  GLuint shaderProgramYellow = glCreateProgram(); // The second shader program
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
  glCompileShader(fragmentShaderOrange);
  glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
  glCompileShader(fragmentShaderYellow);
  // Link the first program object
  glAttachShader(shaderProgramOrange, vertexShader);
  glAttachShader(shaderProgramOrange, fragmentShaderOrange);
  glLinkProgram(shaderProgramOrange);
  // Then link the second program object using a different fragment shader (but same vertex shader) this time.
  // This is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
  glAttachShader(shaderProgramYellow, vertexShader);
  glAttachShader(shaderProgramYellow, fragmentShaderYellow);
  glLinkProgram(shaderProgramYellow);

  GLuint VBOs[2], VAOs[2];
  glGenVertexArrays(2, VAOs);
  glGenBuffers(2, VBOs);

  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  glBindVertexArray(VAOs[1]);	// Note that we bind to a different VAO now
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// And a different VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(min_edge), min_edge, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0); // Because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out.
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  while(!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgramOrange);

    glBindVertexArray(VAOs[0]);
    for (int i = 0; i < edge_num; i++)
      glDrawArrays(GL_LINES, i * 2, 3);

    glUseProgram(shaderProgramYellow);
    glBindVertexArray(VAOs[1]);
    for (int i = 0; i < min_num; i++)
      glDrawArrays(GL_LINES, i * 2, 3);
    glBindVertexArray(0);

    glfwWaitEventsTimeout(0.1);
    // Swap the screen buffers
    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
/*  fout.open("output2(check).txt");

  check.load_nodes(vertices);
  check.generate_edge();
  check.find_min_route();
  check.print_min_route(fout);

  time_t t2 = clock();
  fout << "Whole time: " << (t2 - t1)/1000000.0 << endl;

  fout.close();*/


//  mst.find_k_min_route(2);
//  mst.print_k_min_route(2);
  glfwTerminate();

  return 0;
}
