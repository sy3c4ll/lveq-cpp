#include "lveq.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include <GLFW/glfw3.h>

void drawLife(Life *life);

int main() {
  constexpr double RANDOM_SEED = 0,
                   INITIAL_PREDATOR_NUM = 100,
                   INITIAL_PREY_NUM = 1000,
                   INITIAL_PLANT_NUM = 1000;

  if (!glfwInit()) {
    std::cerr << "[!] Failed to initialise OpenGL" << std::endl;
    exit(EXIT_FAILURE);
  }
  GLFWwindow *window = glfwCreateWindow(world::WIDTH, world::HEIGHT, "LVEq", nullptr, nullptr);
  if (!window) {
    std::cerr << "[!] Failed to create OpenGL window" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1000, 1000, 0, -1, 1);

  srand(RANDOM_SEED);
  world::Ecosystem ecosystem;
  ecosystem.predators.reserve(INITIAL_PREDATOR_NUM);
  for (int i = 0; i < INITIAL_PREDATOR_NUM; i++)
    ecosystem.predators.emplace_back(new Predator());
  ecosystem.preys.reserve(INITIAL_PREY_NUM);
  for (int i = 0; i < INITIAL_PREY_NUM; i++)
    ecosystem.preys.emplace_back(new Prey());
  ecosystem.plants.reserve(INITIAL_PLANT_NUM);
  for (int i = 0; i < INITIAL_PLANT_NUM; i++)
    ecosystem.plants.emplace_back(new Plant());
  std::ofstream logger("data.csv");
  logger << "Time,Predators,Preys,Plants" << std::endl;
  size_t predator_count, prey_count, plant_count;
  size_t framecount = 0; long frameticks;
  glViewport(0, 0, world::WIDTH, world::HEIGHT);
  glClearColor(0, 0, 0, 1);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    ++framecount; frameticks = clock();
    predator_count = 0, prey_count = 0, plant_count = 0;
    glColor3f(1, 0, 0);
    for (Predator *predator: ecosystem.predators)
      if (predator->isAlive()) {
        predator->update(ecosystem, world::ticks() - predator->getClock());
        drawLife(predator);
        ++predator_count;
      }
    glColor3f(0, 1, 0);
    for (Prey *prey: ecosystem.preys)
      if (prey->isAlive()) {
        prey->update(ecosystem, world::ticks() - prey->getClock());
        drawLife(prey);
        ++prey_count;
      }
    glColor3f(0, 0, 1);
    for (Plant *plant: ecosystem.plants) {
      plant->update(ecosystem, world::ticks() - plant->getClock());
      if (plant->isEdible()) {
        drawLife(plant);
        ++plant_count;
      }
    }
    logger << world::days(world::ticks()) << "," << predator_count << "," << prey_count << "," << plant_count << std::endl;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      std::cout << "Frame " << framecount << "\t: " << world::days(world::ticks()) << "\tdays @ " << 1.0 / (clock() - frameticks) * CLOCKS_PER_SEC << "\t FPS"<< std::endl
                << "Predators: " << predator_count << std::endl
                << "Preys:     " << prey_count << std::endl
                << "Plants:    " << plant_count << std::endl
                << std::endl;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  logger.flush();
  logger.close();
  for (Predator *predator: ecosystem.predators)
    delete predator;
  for (Prey *prey: ecosystem.preys)
    delete prey;
  for (Plant *plant: ecosystem.plants)
    delete plant;
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

void drawLife(Life *life) {
  glPointSize(life->getSize() * 2);
  glBegin(GL_POINTS);
  glVertex2d(life->getPos().x, life->getPos().y);
  glEnd();
}
