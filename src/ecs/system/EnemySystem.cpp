#include "EnemySystem.hpp"

EnemySystem::EnemySystem(std::shared_ptr<Scene> scene, std::shared_ptr<Context> context) : scene(scene), context(context){};

EntityID EnemySystem::spawn(int variant) {
  auto enemy = scene->createEntity();
  enemies.push_back(enemy);
  BT::BehaviorTreeFactory factory;
  factory.registerNodeType<InSight>("InSight", player, enemy, scene);
  factory.registerNodeType<InRange>("InRange", player, enemy, scene);
  factory.registerNodeType<AttackPlayer>("AttackPlayer", player, enemy, scene);
  factory.registerNodeType<ApproachPlayer>("ApproachPlayer", player, enemy, scene);
  if (variant == 0) {
    scene->addComponents(enemy, std::make_shared<BodyColor>(sf::Color::Red), std::make_shared<Position>(sf::Vector2i(2, 2)),
                         std::make_shared<Name>((std::string) "Fag"), std::make_shared<Size>(40, 40), std::make_shared<Sight>(14), std::make_shared<Range>(7),
                         std::make_shared<Attack>(7),
                         std::make_shared<BehaviorTree>(std::move(factory), fs::current_path().parent_path() / "resources" / "behavior_trees" / "my_tree.xml",
                                                        BtType::LONG_RANGE));
  } else if (variant == 1) {
    scene->addComponents(enemy, std::make_shared<BodyColor>(sf::Color::Green), std::make_shared<Position>(sf::Vector2i(10, 5)),
                         std::make_shared<Name>((std::string) "Goblin"), std::make_shared<Size>(40, 40), std::make_shared<Sight>(20),
                         std::make_shared<Range>(10), std::make_shared<Attack>(3),
                         std::make_shared<BehaviorTree>(std::move(factory), fs::current_path().parent_path() / "resources" / "behavior_trees" / "my_tree.xml",
                                                        BtType::LONG_RANGE));
  }
  return enemy;
}

void EnemySystem::setPlayer(EntityID player) {
  this->player = player;
}

void EnemySystem::enemyTurn() {
  for (const auto &enemy : enemies) {
    scene->getComponent<BehaviorTree>(enemy)->tree.tickOnce();
  }
}