#include "MainMenu.hpp"

#include <imgui-SFML.h>
#include <imgui.h>

#include "LoadGame.hpp"

MainMenu::MainMenu(std::shared_ptr<Context> &context) : context(context), backgroundSprite(_assets->GetTexture(image::backgrounds::OUTPUT)) {
  shape = sf::RectangleShape{sf::Vector2f{_window->getSize()}};
  shader.loadFromFile(fs::current_path().parent_path() / "shaders" / "backgrounds" / "stars.frag", sf::Shader::Fragment);
  shader.loadFromFile(fs::current_path().parent_path() / "shaders" / "backgrounds" / "stars.frag", sf::Shader::Fragment);
  float width = _window->getSize().x;
  float height = _window->getSize().y;
  backgroundSprite.setScale(width / backgroundSprite.getGlobalBounds().width, height / backgroundSprite.getGlobalBounds().height);
}

MainMenu::~MainMenu() {}

void MainMenu::init() {
  ImGui::SFML::Init(*_window);
}

void MainMenu::processInput() {
  sf::Event event;

  while (context->window->pollEvent(event)) {
    ImGui::SFML::ProcessEvent(event);
    if (event.type == sf::Event::Closed) {
      context->window->close();
    } else if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {  // captures user keyboard input, may be useful
                                 // in the future
        default: {
          break;
        }
      }
    } else if (event.type == sf::Event::MouseMoved) {
      mousePosition = _window->mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
    }
  }
}

void MainMenu::update() {
  ImGui::SFML::Update(*_window, deltaClock.restart());
  ImGuiIO &io = ImGui::GetIO();
  ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.7, io.DisplaySize.y * 0.7));
  ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
  ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
  ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(100, 100, 100, 255));
  ImGui::SetWindowFontScale(6);

  std::string t = "Component Combat";
  auto windowWidth = ImGui::GetWindowSize().x;
  auto textWidth = ImGui::CalcTextSize(t.c_str()).x;
  ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
  ImGui::Text(t.c_str());
  ImGui::SetWindowFontScale(2.3);
  ImGui::PopStyleColor();
  ImGui::Dummy(ImVec2(0.0f, 10.0f));
  bool startGame = ImGui::Button("Start", ImVec2(ImGui::GetWindowContentRegionMax().x - 8, 100));
  bool exit = ImGui::Button("Exit", ImVec2(ImGui::GetWindowContentRegionMax().x - 8, 100));
  ImGui::End();
  if (startGame) _states->addState(std::make_unique<LoadGame>(context));
  if (exit) _states->popCurrent();

  shader.setUniform("u_resolution", sf::Glsl::Vec2{_window->getSize()});
  shader.setUniform("u_time", shaderClock.getElapsedTime().asSeconds());
}

void MainMenu::draw() {
  _window->clear();
  // _window->draw(shape, &shader);
  sf::Sprite backgroundSprite(_assets->GetTexture(image::backgrounds::OUTPUT));
  float width = _window->getSize().x;
  float height = _window->getSize().y;
  backgroundSprite.setScale(width / backgroundSprite.getGlobalBounds().width, height / backgroundSprite.getGlobalBounds().height);
  _window->draw(backgroundSprite);
  //_window->draw(_assets->GetTexture(image::backgrounds::OUTPUT));
  ImGui::SFML::Render(*_window);
  _window->display();
}